//
//  Quadtree.cpp
//  cs300 hw2
//
//  Created by nehir ceylan on 4/2/26.
//
#include "Quadtree.h"

Quadtree::Quadtree() : root(NULL) {}

void Quadtree::insert(string id, int x, int y) {
    root = insert(root, id, x, y);
}

Node* Quadtree::insert(Node* ptr, string id, int x, int y) {
    if (ptr == NULL) {
        return new Node(id, x, y);
    }
    
    if (x >= ptr->x) {
        if (y < ptr->y) {
            ptr->SE = insert(ptr->SE, id, x, y);
        }
        
        else {
            ptr->NE = insert(ptr->NE, id, x, y);
        }


    } else {
        if (y < ptr->y){
            ptr->SW = insert(ptr->SW, id, x, y);
        }
        
        else {
            ptr->NW = insert(ptr->NW, id, x, y);
        }
    }
    return ptr;
}

void Quadtree::pretty_print(Node* ptr) {
    if (ptr != NULL) {
        cout << ptr->id << endl;
        pretty_print(ptr->SE);
        pretty_print(ptr->SW);
        pretty_print(ptr->NE);
        pretty_print(ptr->NW);
    }
}

void Quadtree::print() {
    cout << "Tree:" << endl;
    if (root == NULL) cout << "<Empty>" << endl;
    else pretty_print(root);
}

void Quadtree::collect(Node* ptr, vector<Node*>& nodes) {
    if (ptr == NULL) return;
    nodes.push_back(new Node(ptr->id, ptr->x, ptr->y));
    collect(ptr->SE, nodes); collect(ptr->SW, nodes);
    collect(ptr->NE, nodes); collect(ptr->NW, nodes);
    delete ptr;
}

bool Quadtree::recursive_remove(Node*& ptr, string targetId, vector<Node*>& toAdd) {
    if (ptr == NULL) {
        return false;
    }

    if (ptr->id == targetId) {
        collect(ptr->SE, toAdd); collect(ptr->SW, toAdd);
        collect(ptr->NE, toAdd); collect(ptr->NW, toAdd);
        delete ptr;
        ptr = NULL;
        return true;
    }
    
    return recursive_remove(ptr->SE, targetId, toAdd) ||
           recursive_remove(ptr->SW, targetId, toAdd) ||
           recursive_remove(ptr->NE, targetId, toAdd) ||
           recursive_remove(ptr->NW, targetId, toAdd);
}

void Quadtree::remove(string id) {
    vector<Node*> toAdd;
    recursive_remove(root, id, toAdd);
    for (int i = 0; i < toAdd.size(); i++) {
        insert(toAdd[i]->id, toAdd[i]->x, toAdd[i]->y);
        delete toAdd[i];
    }
}

void Quadtree::request(int x, int y, int r) {
    vector<string> inRange, visited;
    rangeSearch(root, x, y, r, inRange, visited, -100000, -100000, 100000, 100000);
    cout << "InRange: ";
    if (inRange.empty()){
        cout << "<None>";
    }
    
    else {
        for (int i = 0; i < inRange.size(); i++)
            cout << inRange[i] << (i == inRange.size() - 1 ? "" : ",");
    }
    cout << endl << "Visited: ";
    for (int i = 0; i < visited.size(); i++)
        cout << visited[i] << (i == visited.size() - 1 ? "" : ",");
    cout << endl;
}

void Quadtree::rangeSearch(Node* ptr, int target_x, int target_y, int r, vector<string>& inRange, vector<string>& visited, int x_min, int y_min, int x_max, int y_max) {
    if (ptr == NULL) return;
    if (minDistToQuad(target_x, target_y, x_min, y_min, x_max, y_max) > (double)r) return;

    visited.push_back(ptr->id);
    if (dist(ptr->x, ptr->y, target_x, target_y) <= (double)r) inRange.push_back(ptr->id);

    rangeSearch(ptr->SE, target_x, target_y, r, inRange, visited, ptr->x, y_min, x_max, ptr->y);
    rangeSearch(ptr->SW, target_x, target_y, r, inRange, visited, x_min, y_min, ptr->x, ptr->y);
    rangeSearch(ptr->NE, target_x, target_y, r, inRange, visited, ptr->x, ptr->y, x_max, y_max);
    rangeSearch(ptr->NW, target_x, target_y, r, inRange, visited, x_min, ptr->y, ptr->x, y_max);
}

void Quadtree::nearest(int x, int y) {
    Node* best = NULL; double minDist = 1e9; vector<string> visited;
    findNearest(root, x, y, best, minDist, visited, -100000, -100000, 100000, 100000);
    if (best) cout << "Nearest: " << best->id << endl;
    cout << "Visited: ";
    for (int i = 0; i < visited.size(); i++)
        cout << visited[i] << (i == visited.size() - 1 ? "" : ",");
    cout << endl;
}

void Quadtree::findNearest(Node* ptr, int target_x, int target_y, Node*& best, double& minDist, vector<string>& visited, int x_min, int y_min, int x_max, int y_max) {
    if (ptr == NULL) return;
    if (minDistToQuad(target_x, target_y, x_min, y_min, x_max, y_max) > minDist) return;

    visited.push_back(ptr->id);
    double d = dist(ptr->x, ptr->y, target_x, target_y);
    if (d < minDist) { minDist = d; best = ptr; }

    findNearest(ptr->SE, target_x, target_y, best, minDist, visited, ptr->x, y_min, x_max, ptr->y);
    findNearest(ptr->SW, target_x, target_y, best, minDist, visited, x_min, y_min, ptr->x, ptr->y);
    findNearest(ptr->NE, target_x, target_y, best, minDist, visited, ptr->x, ptr->y, x_max, y_max);
    findNearest(ptr->NW, target_x, target_y, best, minDist, visited, x_min, ptr->y, ptr->x, y_max);
}

double Quadtree::minDistToQuad(int target_x, int target_y, int qMinX, int qMinY, int qMaxX, int qMaxY) {
    int dx = max({qMinX - target_x, 0, target_x - qMaxX});
    int dy = max({qMinY - target_y, 0, target_y - qMaxY});
    return sqrt(dx*dx + dy*dy);
}

double Quadtree::dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
