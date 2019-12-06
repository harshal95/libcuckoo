//
// Created by Harshal on 12/5/19.
//


#include <iostream>
#include <string>
#include <thread>
#include <libcuckoo/cuckoohash_map.hh>
#include <chrono>
#include <random>

void insertIntoTable(cuckoohash_map<int, std::string>& Table, int start, int count) {
    for(int i = start; i < start + count; i++) {
        Table.insert(i, "hello");
    }
}
void do_reads(cuckoohash_map<int, std::string> &Table) {

    for(int i = 0; i < 100000; i++) {
        std::string out;

        if(!Table.find(i, out)) {
            std::cout << "Error!!" << std::endl;
        }
    }
    //std::cout << "Exiting do_reads()" << std::endl;
}
void do_reserve(cuckoohash_map<int, std::string> &Table) {
    Table.reserve(4048576);
}
int main() {

    cuckoohash_map<int, std::string> Table;
    int c = 0;
    std::vector<std::thread> threads;
    insertIntoTable(std::ref(Table), 0, 262144);
    auto start = std::chrono::high_resolution_clock::now();
    threads.emplace_back(do_reserve, std::ref(Table));
    //threads.emplace_back(insertIntoTable, std::ref(Table), 0, 4048576);
    threads.emplace_back(do_reads, std::ref(Table));
    for(int i = 0; i < 2; i++) {
        threads[i].join();
    }

    //insertIntoTable(Table, 0, 5048560);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Duration: " << duration.count() << " millisecs" << std::endl;
//    std::cout <<"Table's hash power " << Table.hashpower() << std::endl;
//    std::cout <<"Insertion done" << std::endl;
//    bool res = Table.reserve(4048576);
//    std::cout << "Result of reserve: " << res << std::endl;
//    insertIntoTable(Table, 0, 5048560);



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
