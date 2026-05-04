//
//  Quadtree.h
//  cs300 hw2
//
//  Created by nehir ceylan on 4/2/26.
//
#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    string id;
    int x;
    int y;
    Node *SE;
    Node *SW;
    Node *NE;
    Node *NW;
    Node(string i, int x_coord, int y_coord)
        : id(i), x(x_coord), y(y_coord), SE(NULL), SW(NULL), NE(NULL), NW(NULL) {}
};

class Quadtree {
public:
    Quadtree();
    void insert(string id, int x, int y);
    void remove(string id);
    void print();
    void request(int x, int y, int r);
    void nearest(int x, int y);

private:
    Node* root;
    void pretty_print(Node* ptr);
    
    Node* insert(Node* ptr, string id, int x, int y);
    
    void collect(Node* ptr, vector<Node*>& nodes);
    
    bool recursive_remove(Node*& ptr, string targetId, vector<Node*>& toAdd);
    
    void rangeSearch(Node* ptr, int target_x, int target_y, int r, vector<string>& inRange, vector<string>& visited, int x_min, int y_min, int x_max, int y_max);
    
    void findNearest(Node* ptr, int target_x, int target_y, Node*& bestNode, double& minDist, vector<string>& visited, int x_min, int y_min, int x_max, int y_max);
    
    double dist(int x1, int y1, int x2, int y2);
    
    double minDistToQuad(int target_x, int target_y, int qMinX, int qMinY, int qMaxX, int qMaxY);
    
};

#endif
