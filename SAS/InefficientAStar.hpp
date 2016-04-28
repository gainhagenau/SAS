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
    vector<action> list;    // open/closed list
    uint64_t nodesExpanded; //nodes expanded
    
    void addElement(action a, vector<action> &v) {  //push back the action
        v.push_back(a);
    }
    bool checkDuplicates(vector<action> &v) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                if (j != i && v[i] == v[j]) {
                    return true;
                }
            }
        }
        return false;
    }
    void updateCost(action &a);
    void removeBest(vector<action> &v);
}
#endif /* InefficientAStar_hpp */
