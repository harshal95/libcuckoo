//
// Created by Harshal on 11/20/19.
//

#include <iostream>
#include <string>
#include <thread>
#include <libcuckoo/cuckoohash_map.hh>
#include <chrono>
#include <random>

const size_t read_thread_num = 8;
const size_t write_thread_num = 1;
const size_t total_inserts = 200000;
const size_t total_reads = 1000000;
typedef uint32_t KeyType;

void do_reads(cuckoohash_map<int, std::string> &Table) {
    //std::cout << "Entering do_reads()" << std::endl;

    for(int i = 0; i < total_reads; i++) {
        std::string out;
        for(int j = 0; j < 3; j++) {
/*            if(!Table.find(i, out)) {
                std::cout << "Find returned false for key " << i << " !!" << std::endl;
            }*/
            Table.find(i, out);
        }
    }
    //std::cout << "Exiting do_reads()" << std::endl;
}

void do_inserts(cuckoohash_map<int, std::string> &Table) {
//    std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
//    std::uniform_int_distribution<KeyType> dist(
//            std::numeric_limits<KeyType>::min(), std::numeric_limits<KeyType>::max());
//    auto updatefn = [](std::string &val) { val = "hi"; };
    for (size_t i = 0; i < total_inserts; i++) {
        //KeyType num = dist(gen);

        // If the number is already in the table, it will increment
        // its count by one. Otherwise it will insert a new entry in
        // the table with count one.
        //Table.upsert(i, updatefn, 1);
        Table.insert(i, "hello");
    }
}

int main() {
    cuckoohash_map<int, std::string> Table;
//
//    for (int i = 0; i < 100; i++) {
//        Table.insert(i, "hello");
//    }
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
    for (size_t i = 0; i < write_thread_num; i++) {
        threads.emplace_back(do_inserts, std::ref(Table));
    }

    for (size_t i = 0; i < read_thread_num; i++) {
        threads.emplace_back(do_reads, std::ref(Table));
    }

    for (size_t i = 0; i < read_thread_num + write_thread_num; i++) {
        threads[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Multiple Reader, Single Writer duration: " << duration.count() << " millisecs" << std::endl;
}