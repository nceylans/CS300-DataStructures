//
//  HashTable.h
//  cs300 hw3
//
//  Created by nehir ceylan on 4/20/26.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

enum EntryType { ACTIVE, EMPTY, DELETED };

struct HashEntry {
    std::vector<int> data;
    EntryType info;

    HashEntry() : info(EMPTY) {}
};

class HashTable {
public:
    HashTable(int size = 25);

    bool insert(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos);
    bool find(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos);
    bool remove(const std::vector<int>& qrData, int& hashVal, int& probes, int& pos);

private:
    std::vector<HashEntry> array;
    int currentSize;

    int hashFunction(const std::vector<int>& qrData) const;
};

#endif

