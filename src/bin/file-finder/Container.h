#pragma once

#include <string>
#include <set>
#include <thread>
#include <mutex>

using namespace std;

namespace ff {

    class Container {
    public:
        Container() = default;
        ~Container() = default;
        
        void Dump();
        void Add(const string& val);
        void Clear();

    private:
        mutex values_mtx_;
        set<string> values_;
    };

} //namespace ff