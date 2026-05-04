//
//  Source.cpp
//  cs300 hw3
//
//  Created by nehir ceylan on 4/20/26.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "HashTable.h"

int rowToDecimal(const std::string& row) {
    int val = 0;
    for (char c : row)
        val = (val << 1) + (c - '0');
    return val;
}

std::vector<int> readQR(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> encoded;

    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return {};
    }

    std::string line;
    while (getline(file, line)) {
        encoded.push_back(rowToDecimal(line));
    }
    return encoded;
}

void printVector(const std::vector<int>& v) {
    std::cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        std::cout << v[i];
        if (i != (int)v.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    int numFiles;
    std::cout << "Enter number of authorized QR files to load: ";
    std::cin >> numFiles;

    HashTable ht(25);

    for (int i = 1; i <= numFiles; i++) {
        std::string filename = "./QR/qr" + std::to_string(i) + ".txt";
        std::cout << "\nProcessing " << filename << std::endl;

        std::vector<int> qrData = readQR(filename);
        if (qrData.empty()) continue;

        int hashVal, probes, pos;
        ht.insert(qrData, hashVal, probes, pos);

        std::cout << "INSERT -> ";
        printVector(qrData);
        std::cout << " | hash=" << hashVal
                  << " probes=" << probes
                  << " pos=" << pos << std::endl;
    }

    int selector;
    while (true) {
        std::cout << "\nSelect operation:\n"
                  << "1 -> Find QR\n"
                  << "2 -> Remove QR\n"
                  << "3 -> Terminate\n"
                  << "\n";


        std::cout << "Enter selector: ";
        std::cin >> selector;

        if (selector == 3) {
            std::cout << "Terminating program." << std::endl;
            break;
        }

        std::string filename;
        std::cout << "Enter QR filename: ";
        std::cin >> filename;

        std::vector<int> qrData = readQR(filename);
        if (qrData.empty()) continue;

        std::cout << "Row Encoding: ";
        printVector(qrData);
        std::cout << std::endl;

        int hashVal, probes, pos;

        if (selector == 1) {
            bool found = ht.find(qrData, hashVal, probes, pos);
            std::cout << "Found -> ";
            printVector(qrData);
            std::cout << " | hash=" << hashVal
                      << " probes=" << probes
                      << " pos=" << pos;
            if (found)
                std::cout << " | Authorization Granted\n";
            else
                std::cout << " | Authorization Denied\n";
        }
        else if (selector == 2) {
            bool removed = ht.remove(qrData, hashVal, probes, pos);
            std::cout << "REMOVE -> ";
            printVector(qrData);
            std::cout << " | hash =" << hashVal
                      << " probes =" << probes
                      << " pos =" << pos;
            if (removed)
                std::cout << " | QR removed from the system.\n";
            else
                std::cout << " | QR not found.\n";
        }
    }

    return 0;
}
