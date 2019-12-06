//
// Created by Harshal on 12/4/19.
//

#include <iostream>
#include <string>
#include <thread>
#include <libcuckoo/cuckoohash_map.hh>
#include <chrono>
#include <random>

void insertIntoTable(cuckoohash_map<int, std::string> Table, int start, int count) {
    for(int i = start; i < start + count; i++) {
        Table.insert(i, "hello");
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    cuckoohash_map<int, std::string> Table;
    int c = 0;
//    insertIntoTable(Table, 0, 262144);
//    std::cout <<"Table's hash power " << Table.hashpower() << std::endl;
//    std::cout <<"Insertion done" << std::endl;
    bool res = Table.reserve(4048576);
    std::cout << "Result of reserve: " << res << std::endl;
    insertIntoTable(Table, 0, 5048560);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Duration: " << duration.count() << " secs" << std::endl;


//    std::cout <<"Table's hash power " << Table.hashpower() << std::endl;

//
//    insertIntoTable(Table, 262145, 262145);

    //std::cout << "Bucket count is :" << Table.hashpower() << std::endl;
//
//    while(1) {
//        bool result = Table.insert(c, "hello");
//        c++;
//        std::cout << c << std::endl;
//        if(c == 264145) {//262145
//            std::cout << "result : " << result << std::endl;
//            break;
//        }
//    }
//    std::cout << "Failed insertions on newMap: " << Table.getFailedCountOnNewMap() << std::endl;
//    std::cout << "Successful insertions on newMap: " << Table.getSucceededCountOnNewMap() << std::endl;

}