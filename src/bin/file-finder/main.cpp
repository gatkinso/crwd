#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <functional>
#include "Container.h"
#include <condition_variable> 

using namespace std;
using namespace ff;
using namespace std::filesystem;
using namespace std::chrono_literals;

vector<string> parameters;
string tgtDir;
Container container;
atomic_bool userRunning = false;
unique_ptr<thread> userThread;
vector<unique_ptr<thread> > worker_pool;
condition_variable cvDump; 
mutex dumpMtx;

void dumpThreadFcn() {
    unique_lock<mutex> lock(dumpMtx); 

    while(userRunning.load()) {
        cvDump.wait_for(lock, 10s);
    
        if(userRunning.load())
            container.Dump();
    }
}

void userThreadFcn() {
    static int i = 0;
    userRunning.store(true);
    while(userRunning.load()) {
        char cmd {};
        cin >> cmd;

        switch(cmd) {
            case 'd':
            case 'D':
                container.Dump();
                break;
            case 'q':
            case 'Q':
                userRunning.store(false);
                cvDump.notify_all();
                break;
            default:
                cout << "Unknown command! " << cmd << endl;
        }
    }
}

void workerThreadFcn(const string tgt, const string sstr) {
    userRunning.store(true);
    
    int i = 0;
    while(userRunning.load()) {
        for (const auto & entry : recursive_directory_iterator(tgt)) {
            const auto &path = entry.path().string();
            const auto iter = std::search(path.begin(), path.end(), boyer_moore_searcher(sstr.begin(), sstr.end()));
            if(iter != path.end()) {
                container.Add(path);
            }
            if(false == userRunning.load())
                break;
        }
        // In production I'd use something less hacky,
        // but this is my third coding challenge this week, sorry.
        if (userRunning.load()) this_thread::sleep_for(1s);
    }
}

void showHelp() {
    cout << "The application takes the directory to search as the first command line argument, followed by one or more substrings (literals, not wildcards) to search for." << endl;
    cout << "file-finder <dir> <substring1>[<substring2> [<substring3>]...]" << endl;
    cout << "For example: file-finder tmp aaa bbb ccc" << endl << endl;
    cout << "Hitting the q or Q  key will quit.  Hitting the q or Q key will dump contents of search." << endl;
    cout << "Search results will display periodically." << endl;
}

bool parseCLA(int argc, char* argv[]) {
    if(argc <= 2) {
        showHelp();
        return false;
    }

    copy(argv + 2, argv + argc, back_inserter(parameters));
    tgtDir = argv[1];

    if(!exists(tgtDir)) {
        cout << tgtDir << " Does not exist!  Exiting!" << endl;  
        return false;
    }

    cout << "file-finder searching: " << tgtDir << endl;

    return true;
}

int main(int argc, char* argv[]) {
    cout << "file-finder starting" << endl;
    cout << "Geoffrey Atkinson geoffrey.j.atkinson@gmail.com" << endl;

    if(false == parseCLA(argc, argv)) {
        return 1;
    }

    auto ut = make_unique<thread>(userThreadFcn);
    auto dt = make_unique<thread>(dumpThreadFcn);

    for(auto param : parameters) {
        auto wt = make_unique<thread>(&workerThreadFcn, tgtDir, param);
        worker_pool.push_back(std::move(wt));
    }

    //
    // Should one generic pool be manageing all this?  Yes.
    //
    for(auto& thd : worker_pool) {
       if(thd->joinable())
          thd->join();
    }

    if(dt && dt->joinable()) {
        dt->join();
    }

    if(ut && ut->joinable()) {
        ut->join();
    }

    cout << "file-finder exiting" << endl;

    return 0;
}
