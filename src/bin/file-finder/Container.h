#pragma once

#include <string>
#include <set>
#include <thread>

using namespace std;

namespace ff {

    class Container {
    public:
        Container() = default;
        ~Container();

        void Dump();
        void Add(const string& val);
        void Clear();

    private:
        mutex values_mtx_;
        set<string> values_;
    };

} //namespace ff