//
//  InefficientAStar.hpp
//  SAS
//
//  Created by Ryan Aikman on 4/26/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef InefficientAStar_hpp
#define InefficientAStar_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

template <typename state, typename action, typename environment, typename heuristic>
class InefficientAStar {
public:
    InefficientAStar(){};
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal, heuristic &h);
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return nodesExpanded;
    }
private:
    uint64_t nodesExpanded; // nodes expanded
    
    struct node {
        int gCost;
        int hCost;
        bool open;
        state s;
    };
    vector<node> list;    // open/closed list
    
    void addElement(node n) {  //push back the action
        int i = checkDuplicates(s, list);  //check for duplicates before adding
        if (i >= 0) {    // if there is a duplicate at index i, replace
            v[i] = n;
        } else {    // no duplicates, just push back
            v.push_back(n);
        }
    }
    
    int checkDuplicates(node n) {
        for (int i = 0; i < n.state.size(); i++) {// go through array, if a match is found return that index
            if (n.state == list[i].state) {
                return i;
            }
        }
        return -1;  // no duplicate
    }
    void removeBest() {
        int index = -1;
        int f = 0;
        for (int i = 0; i < list.size(); i==) {
            if (list[i].open && f > list[i].gCost + list[i].hCost) {
                f = list[i].gCost + list[i].hCost;
                index = i;
            }
            
        }
        list.erase(i);
    }
}
#endif /* InefficientAStar_hpp */