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

/*template <typename state, typename action, typename environment, typename heuristic>
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
        }
        return true;
    }
    
    //depth first search with limited f cost
    bool cost_limited_dfs(int limit, state &s, state &goal, environment &e, heuristic &h) {        
        if (hcost == 0 && s == goal){ //goal found
            return true;
        }
        if (fCost() > limit) { //f cost too high, check for nextBound
            if (nextBound == -1 || fCost() < nextBound){
                nextBound = fCost();
            }
            return false;
        }
        
        vector<action> actions;
        e.GetActions(s, actions);
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
        return nodesExpanded;
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
    action lastAction;
};
*/
//#endif /* IDA_hpp */

template <typename state, typename action, typename environment, typename heuristic>
class IDA
{
public:
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal, heuristic &h);
    
    void GetSolution(std::vector<action> &s) { s = solution; }
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded();
private:
    bool BoundedDFS(environment &e, state &s, heuristic &h, int depth);
    uint64_t nodesExpanded;
    int currentBound;
    int nextBound;
    std::vector<action> actionHistory;
    std::vector<std::vector<action>> moveArrays;
    std::vector<action> solution;
    state g;
};


template <typename state, typename action, typename environment, typename heuristic>
bool IDA<state, action, environment, heuristic>::GetPath(environment &e, state &start, state &goal, heuristic &h)
{
    nodesExpanded = 0;
    g = goal;
    currentBound = h.GetHeuristic(start);
    nextBound = -1;
    while (true)
    {
        if (moveArrays.size() <= currentBound)
            moveArrays.resize(currentBound+1);
        //std::cout << "Bound: " << currentBound;
        //std::cout << "; " << nodesExpanded << " nodes expanded thus far\n";
        if (BoundedDFS(e, start, h, 0))
            return true;
        currentBound = nextBound;
        nextBound = -1;
    }
}

template <typename state, typename action, typename environment, typename heuristic>
bool IDA<state, action, environment, heuristic>::BoundedDFS(environment &e, state &s, heuristic &h, int depth)
{
    int f = depth+h.GetHeuristic(s);
    if (f > currentBound)
    {
        if (nextBound == -1)
            nextBound = f;
        else if (f < nextBound)
            nextBound = f;
        return false;
    }
    if (s == g)
    {
        solution = actionHistory;
        return true;
    }
    
    
    std::vector<action> &moves = moveArrays[depth];
    e.GetActions(s, moves);
    nodesExpanded++;
    for (auto a : moves)
    {
        if (actionHistory.size() > 0 && actionHistory.back() == e.InvertAction(a))
            continue;
        e.ApplyAction(s, a);
        actionHistory.push_back(a);
        bool result = BoundedDFS(e, s, h, depth+1);
        actionHistory.pop_back();
        e.UndoAction(s, a);
        if (result == true)
        {
            return true;
        }
    }
    return false;
}

template <typename state, typename action, typename environment, typename heuristic>
uint64_t IDA<state, action, environment, heuristic>::GetNodesExpanded()
{
    return nodesExpanded;
}


#endif /* IDAStar_h */

