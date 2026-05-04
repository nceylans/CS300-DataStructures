//
//  Source.cpp
//  cs300 hw2
//
//  Created by nehir ceylan on 4/2/26.
//
#include <iostream>
#include <fstream>
#include <string>
#include "Quadtree.h"

using namespace std;

int main() {
    Quadtree my_tree;
    
    ifstream dr_file("drivers.txt");
    int bound_x, bound_y;
    
    if (!(dr_file >> bound_x >> bound_y)) {
        return 0;
    }

    string d_id;
    int d_x, d_y;
    while (dr_file >> d_id >> d_x >> d_y) {
        my_tree.insert(d_id, d_x, d_y);
    }
    dr_file.close();

    ifstream my_file("operations.txt");
    string command;
    
    while (my_file >> command) {
        if (command == "PRINT") {
            my_tree.print();
        }
        else if (command == "ADD") {
            my_file >> d_id >> d_x >> d_y;
            my_tree.insert(d_id, d_x, d_y);
        }
        else if (command == "REMOVE") {
            my_file >> d_id;
            my_tree.remove(d_id);
        }
        else if (command == "REQUEST") {
            int radius;
            my_file >> d_x >> d_y >> radius;
            my_tree.request(d_x, d_y, radius);
        }
        else if (command == "NEAREST") {
            my_file >> d_x >> d_y;
            my_tree.nearest(d_x, d_y);
        }
    }
    
    my_file.close();
    return 0;
}

