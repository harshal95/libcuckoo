//
// Created by Harshal on 12/4/19.
//

#include <iostream>
#include <string>
#include <thread>
#include <libcuckoo/cuckoohash_map.hh>
#include <chrono>
#include <random>

int main() {
    cuckoohash_map<int, std::string> Table;
    int c = 0;
    while(1) {
        Table.insert(c, "hello");
        c++;
        std::cout << c << std::endl;
        if(c == 262145)
            break;
    }
}