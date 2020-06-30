//
// Created by shubham on 6/26/20.
//
#include <iostream>
#include <vector>
#include "fnv.h"
#include <math.h>

using namespace std;

/**
 * Basic bloom filter that supports creation from a vector
 * and checks if an element exists
 *
 * Questions?
 * 1. How many hash functions? --- k
 *    Optimal number of hash functions: k = (m/n) * ln2
 *
 *    Ref: https://willwhim.wpengine.com/2011/09/03/producing-n-hash-functions-by-hashing-only-once/
 *
 *
 * 2. How to choose size of store? --- m
 *    Larger the filter(m), the better
 *    Optimal number of bits per element:
 *        m/n ~= -1.44 log2(er), where er = desired false positive probability
 *
 *    For er = 0.0001 (0.01%)
 *    m/n ~= 20
 *      k ~= 14
 *
 *
 * What we know is input list size --- n
 *
 * References: https://en.wikipedia.org/wiki/Bloom_filter
 */
class BloomFilter {
private:
    vector<bool> store;
    uint8_t hashFunctions;

public:

    BloomFilter() = default;

    bool create(const vector<int> &inputList) {

        try {
            // filterSize (m) affects false positivity rate
            // Question: how to decide m?
            size_t filterSize = inputList.size() * 10;
            store.assign(filterSize, false);

            hashFunctions = 4;

            for (const auto &it: inputList) {
                // set corresponding bits to true
                for (int i = 0; i < hashFunctions; i++) {
                    uint16_t pos = getIHash(it, i) % store.size();
                    store[pos] = true;
                }
                // just print value, hash, and pos for debugging
//                cout << "it: " << it << ", hash: " << valHash << ", up: " << upHash << ", down: " << downHash
//                     << ", pos1: " << pos1 << ", pos2: " << pos2 << endl;
            }

            return true;

        } catch (exception &e) {
            cout << "Exception while creating bloomFilter: " << e.what();
            return false;
        }
    }

    /**
     * check if input exists in the filter
     * @param input - the key to check
     * @return false if the key dosent exist, if true, key may or may not exist
     */
    bool exists(int input) {
        for (int i = 0; i < hashFunctions; i++) {
            uint16_t pos = getIHash(input, i) % store.size();
            // debug
            cout << "input: " << input << ", pos: " << pos << endl;
            if (!store[pos]) return false;
        }
        return true;
    }

    /**
     *
     * @param key - the key to hash
     * @param i - get the ith hash
     * @return the ith hash
     */
    uint16_t getIHash(uint32_t key, int i) {
        uint32_t valHash = FNV::fnv1a((uint32_t) key);
        uint32_t mask = pow(2, 16) - 1;

        // when assigning 32 bit to 16 bit, only the bottom half is kept
        uint16_t upHash = (valHash >> 16) & mask;
        uint16_t downHash = (valHash & mask);

        return upHash + (i * downHash);
    }


    /**
     *
     * @return size of elements stored in the bloom filter
     */
    size_t getsize() {
        return sizeof(BloomFilter) + (sizeof(bool) * store.size());
    }

};

int main() {

    vector<int> list(200);
    for (int i = 0; i < 200; i++) {
        list[i] = i;
    }
//    cout << "Input list: ";
//    for (const auto &it: list) {
//        cout << it << " ";
//    }
    cout << endl;
    BloomFilter f;
    f.create(list);
    cout << endl << "Does 6 exist: ? " << f.exists(6) << endl;
    cout << endl << "Does 199 exist: ? " << f.exists(199) << endl;
    cout << endl << "Does 299 exist: ? " << f.exists(299) << endl;
    cout << endl << "Does 3000 exist: ? " << f.exists(3000) << endl;


    cout << "Bloom Filter\n";
    cout << "bf size: " << f.getsize() << endl << "list size: "
         << sizeof(std::vector<int>) + (sizeof(int) * list.size())
         << endl << "bf class size: " << sizeof(BloomFilter) << endl;

    cout << "Bool size: " << sizeof(bool) << ", char size: " << sizeof(char) << ", uint16_t: " << sizeof(uint16_t)
         << ", uint32_t: " << sizeof(uint32_t) << endl;

    return 0;
}