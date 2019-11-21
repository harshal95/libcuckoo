//
// Created by Harshal on 11/20/19.
//
#include <iostream>
#include <string>
#include <thread>
#include <libcuckoo/cuckoohash_map.hh>
#include <chrono>
#include <random>

const size_t thread_num = 8;
const size_t total_inserts = 10000000;
const size_t total_reads = 10000000;
typedef uint32_t KeyType;
//typedef cuckoohash_map<KeyType, std::string> Table;
//void do_inserts(Table &freq_map) {
//    std::mt19937_64 gen(
//            std::chrono::system_clock::now().time_since_epoch().count());
//    std::uniform_int_distribution<KeyType> dist(
//            std::numeric_limits<KeyType>::min(), std::numeric_limits<KeyType>::max());
//    auto updatefn = [](size_t &num) { ++num; };
//    for (size_t i = 0; i < total_inserts / thread_num; i++) {
//        KeyType num = dist(gen);
//        // If the number is already in the table, it will increment
//        // its count by one. Otherwise it will insert a new entry in
//        // the table with count one.
//        freq_map.upsert(num, updatefn, 1);
//    }
//}

void do_reads(cuckoohash_map<int, std::string> &Table) {
    //std::cout << "Entering do_reads()" << std::endl;
    for(int i = 0; i < 100; i++) {
        std::string out;
        for(int j = 0; j < total_reads / thread_num; j++) {
            if(!Table.find(i, out)) {
                std::cout << "Error!!";
            }
        }
    }
    //std::cout << "Exiting do_reads()" << std::endl;
}

void do_inserts(cuckoohash_map<int, std::string> &Table) {
    std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<KeyType> dist(
            std::numeric_limits<KeyType>::min(), std::numeric_limits<KeyType>::max());
    auto updatefn = [](std::string &val) { val = "hello"; };
    for (size_t i = 0; i < total_inserts / thread_num; i++) {
        KeyType num = dist(gen);
        // If the number is already in the table, it will increment
        // its count by one. Otherwise it will insert a new entry in
        // the table with count one.
        Table.upsert(num, updatefn, 1);
    }
}

int main() {
    cuckoohash_map<int, std::string> Table;

    for (int i = 0; i < 100; i++) {
        Table.insert(i, "hello");
    }
//
//    for (int i = 0; i < 101; i++) {
//        std::string out;
//
//        if (Table.find(i, out)) {
//            std::cout << i << "  " << out << std::endl;
//        } else {
//            std::cout << i << "  NOT FOUND" << std::endl;
//        }
//    }


    auto start = std::chrono::high_resolution_clock::now();
    // Run the reads in thread_num threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < thread_num; i++) {
        threads.emplace_back(do_reads, std::ref(Table));
    }
    for (size_t i = 0; i < thread_num; i++) {
        threads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Read duration: " << duration.count() << " secs" << std::endl;
}

