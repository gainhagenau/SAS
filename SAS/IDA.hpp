//
//  IDA.hpp
//  SAS
//
//  Created by Ryan Aikman on 4/7/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef IDA_hpp
#define IDA_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
#include "STmanhattan.hpp"

using namespace std;

template <typename state, typename action, typename environment>
class IDA {
public:
    /*
     bound <- f-cost(start)
     while(!solution)
        nextbound = -1
     cost_limit_dfs(bound)
     */
    /*
     cost_limited_dfs(limit, state)
        if f-cost(state) > limit
            return
        if state = goal
            for each action a in state
                apply a to state
                cost_limited_dfs
                undo a from state
     */
    IDA(){};
    ~IDA(){};
    
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal) {
        int bound = fCost(start);
        int nextBound; //???
        while (start != goal) {
            nextBound = -1;
            cost_limit_dfs(bound, start, goal);
        }
    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return GetNodesExpanded;
    }
    
    void cost_limited_dfs(int limit, state &s, state &goal) {
        nodesExpanded++;
        if (fCost(s) > limit) {
            return;
        }
        if (s == goal) {
            for (int i = 0; i < actions.size(); i++) {
                e.ApplyAction(s, action[i]);
                cost_limit_dfs(limit, s, goal);
                e.UndoAction(s, action[i]);
            }
        }
    }
private:
    int nodesExpanded;
    int fCost(state &s) {
        return hCost(s) + gCost(s); //g + h
    }
    
    int hCost (state &s) { //heuristic cost
        return GetHeuristic(s);
    }
    
    int gCost(state &s) { //current distance traveled
        return nodesExpanded;
    }
};

#endif /* IDA_hpp */
