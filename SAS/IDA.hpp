/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
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

template <typename state, typename action, typename environment, typename heuristic>
class IDA {
public:
    IDA(){};
    ~IDA(){};
    
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal, heuristic &h) {
        gcost = 0; //g cost at start is 0
        hcost = h.GetHeuristic(start); //calculates the h cost from starting state
        int bound = fCost(); //max f cost allowed at current level of search
        bool solution = false;
        while (!solution) {
            nextBound = -1;
            solution = cost_limited_dfs(bound, start, goal, e, h); //run search with limited bound
            bound = nextBound; //increase the search depth
            for (int i = 0; i < 16; i++) {
                cout << start.state[i] << ", ";
            }
            cout << endl;
        }
        return true;
    }
    
    //depth first search with limited f cost
    bool cost_limited_dfs(int limit, state &s, state &goal, environment &e, heuristic &h) {
        if (hcost == 0 && s == goal){ //goal found
            return true;
        }
        if (fCost() > limit) { //f cost too high, check for nextBound
            if (hcost != -1 && hcost < nextBound){
                hcost = nextBound;
            }
            return false;
        }
        
        for (int i = 0; i < actions.size(); i++) { //run through actions
            nodesExpanded++;
            e.ApplyAction(s, actions[i]); //apply action and change asociated g and h costs
            gcost++;
            previousH = hcost;
            hcost = h.GetHeuristic(s);
            bool found = cost_limited_dfs(limit, s, goal, e, h); //run search on new state
            if (found){
                return true;
            }
            e.UndoAction(s, actions[i]); //undo actions
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
    vector<action> actions;
    int fCost() {
        return hcost + gcost; //g + h
    }
};

#endif /* IDA_hpp */
