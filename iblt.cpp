//
// Created by shubham on 6/30/20.
//

#include <iostream>
#include <vector>
#include <math.h>
#include "fnv.h"

using namespace std;

class IBLTCell{
public:
    int count, keySum, valueSum;

    IBLTCell() {
        count = 0;
        keySum = 0;
        valueSum = 0;
    }
};
/**
 * Basic IBLT implementation
 * Features:
 * for simple cases of single key value pairs, and no extraneous deletions
 * 1. insert(x, y)
 * 2. remove(x, y)
 * 3. get(x)
 * 4. listEntries()
 */
class IBLT {
private:
    uint8_t hashFunctions;
    vector<IBLTCell> store;
public:
    IBLT() = default;

    bool create(size_t size) {
        hashFunctions = 5;
        store.empty();
        store.resize(size);
        return true;
    }

    /**
     * insert key value pair into IBLT
     * @param key
     * @param value
     * @return
     */
    bool insert(int key, int value) {
        for (int i = 0; i < hashFunctions; i++) {
            uint16_t pos = getIHash(key, i) % store.size();
            store[pos].count += 1;
            store[pos].keySum += key;
            store[pos].valueSum += value;
        }
        return true;
    }

    /**
     * remove key value pair from IBLT
     * @param key
     * @param value
     * @return
     */
    bool remove(int key, int value) {
        for (int i = 0; i < hashFunctions; i++) {
            uint16_t pos = getIHash(key, i) % store.size();
            store[pos].count -= 1;
            store[pos].keySum -= key;
            store[pos].valueSum -= value;
        }
        return false;
    }

    /**
     * get value for respective key
     * @param key
     * @return
     */
    int get(int key) {
        // TODO: iterate over only unique hash values (pos from hash values)
        for (int i = 0; i < hashFunctions; i++) {
            uint16_t pos = getIHash(key, i) % store.size();
            auto cell = store[pos];
            if(cell.count == 0) {
                // must return null or error
                return 0;
            } else if (cell.count == 1 ) {
                if(cell.keySum == key) {
                    return cell.valueSum;
                } else {
                    // must return null or error
                    return 0;
                }
            }
        }
        // must return null or error
        return 0;
    }

    /**
     * TODO: implement
     * @return
     */
    vector<pair<int, int>> listEntries() {
        pair<int, int> p = make_pair(10, 1);
        vector<pair<int, int>> res{p};
        return res;
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
};

int main() {

    IBLT lookupTable;
    lookupTable.create(100);
    lookupTable.insert(1, 19);
    lookupTable.insert(2, 33);
    cout<<"get from table: " << lookupTable.get(1) << endl;
    cout<<"get from table: " << lookupTable.get(2) << endl;

    cout<<"IBLT\n";

    return 0;
}