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
        gcost = 0; //g cost at start is 0
        hcost = GetHeuristic(start); //calculates the h cost from starting state
        int bound = fCost(start); //max f cost allowed at current level of search
        bool solution = false;
        while (!solution) {
            nextBound = -1;
            solution = cost_limit_dfs(bound, start, goal); //run search with limited bound
            bound = nextBound; //increase the search depth
        }
    }
    
    
    bool cost_limited_dfs(int limit, state &s, state &goal) {
        if (hcost == 0 && s == goal){
            return true;
        }
        if (fCost() > limit) {
            if (hcost != -1 && hcost < nextBound){
                hcost = nextBound;
            }
            return false;
        }
        
        for (int i = 0; i < actions.size(); i++) {
            nodesExpanded++;
            e.ApplyAction(s, action[i]);
            gcost++;
            previousH = hcost;
            hcost = GetHeuristic(s);
            bool found = cost_limit_dfs(limit, s, goal);
            if (found){
                return true;
            }
            e.UndoAction(s, action[i]);
            gcost--;
            hcost = previousH;
        }
        return false;
    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return GetNodesExpanded;
    }
    
private:
    int nodesExpanded;
    int nextBound;
    int gcost;
    int hcost;
    int previousH;
    int fCost() {
        return hcost + gcost; //g + h
    }
};

#endif /* IDA_hpp */
