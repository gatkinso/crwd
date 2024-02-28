#include "Container.h"
#include <iostream>

using namespace std;

namespace ff {

void Container::Dump() {
    scoped_lock<mutex> lock(values_mtx_);
    cout << "Dumping container" << endl;

    uint i = 0;

    for(const auto& val: values_) {
        cout << val << endl;
        i++;
    }

    cout << "Dumped " << i << " values" << endl;

    values_.clear();
}

void Container::Add(const string& val) {
    scoped_lock<mutex> lock(values_mtx_);
    values_.emplace(val);  //exceptions!
}

void Container::Clear() {
    scoped_lock<mutex> lock(values_mtx_);
    cout << "Clearing container" << endl;

    values_.clear(); 
}

} // namespace
