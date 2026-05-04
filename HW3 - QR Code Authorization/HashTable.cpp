//
//  HashTable.cpp
//  cs300 hw3
//
//  Created by nehir ceylan on 4/20/26.
//
#include "HashTable.h"
#include <iostream>

HashTable::HashTable(int size) : array(size), currentSize(size) {}

int HashTable::hashFunction(const std::vector<int>& qrData) const {
    int hashVal = 0;
    int prime = 31;
    for (int r : qrData) {
        hashVal = (hashVal * prime + r) % currentSize;
    }
    return hashVal;
}

bool HashTable::insert(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos) {
    hashVal = hashFunction(qrData);
    pos = hashVal;
    probes = 1; 

    while (array[pos].info == ACTIVE) {
        pos = (pos + 1) % currentSize;
        probes++;
        if (probes > currentSize) return false;
    }

    array[pos].data = qrData;
    array[pos].info = ACTIVE;
    return true;
}

bool HashTable::find(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos) {
    hashVal = hashFunction(qrData);
    pos = hashVal;
    probes = 1;

    while (array[pos].info != EMPTY) {
        if (array[pos].info == ACTIVE && array[pos].data == qrData)
            return true;

        pos = (pos + 1) % currentSize;
        probes++;

        if (probes > currentSize) break;
    }

    pos = -1;
    return false;
}

bool HashTable::remove(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos) {
    if (find(qrData, hashVal, probes, pos)) {
        array[pos].info = DELETED;
        return true;
    }
    return false;
}
