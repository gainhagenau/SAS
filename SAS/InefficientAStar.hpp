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
    
    /*
     while the open list is not empty
     find the node with the least f on the open list, call it "q"
     pop q off the open list
     generate q's 8 successors and set their parents to q
     for each successor
    	if successor is the goal, stop the search
     successor.g = q.g + distance between successor and q
     successor.h = distance from goal to successor
     successor.f = successor.g + successor.h
     
     if a node with the same position as successor is in the OPEN list \
     which has a lower f than successor, skip this successor
     if a node with the same position as successor is in the CLOSED list \
     which has a lower f than successor, skip this successor
     otherwise, add the node to the open list
     end
     push q on the closed list
     end
     */
    bool GetPath(environment &e, state &start, state &goal, heuristic &h) {
        vector<action> actions;
        while (stillOpen()) {
            node q = list[findBest()];
            e.GetActions(q.state, actions); //populates actions with the current avalible actions
            
        }
    }
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return nodesExpanded;
    }
private:
    uint64_t nodesExpanded; // nodes expanded
    
    struct node {
        int gCost, hCost;
        bool open;
        state s;
    };
    vector<node> list;    // open/closed list
    
    void addElement(node n) {  //push back the action
        int i = checkDuplicates(s, list);  //check for duplicates before adding
        if (i >= 0) {    // if there is a duplicate at index i, replace
            list[i] = n;
        } else {    // no duplicates, just push back
            list.push_back(n);
        }
    }
    
    int checkDuplicates(node n) {
        for (int i = 0; i < n.state.size(); i++) {  // go through array, if a match is found return that index
            if (n.state == list[i].state) {
                return i;
            }
        }
        return -1;  // no duplicate
    }
    void removeBest() {
        int index = -1;
        int f = list[0].gCost + list[0].hCost;
        for (int i = 1; i < list.size(); i++) {
            if (list[i].open && f > list[i].gCost + list[i].hCost) {
                f = list[i].gCost + list[i].hCost;
                index = i;
            }
            
        }
        list.erase(i);
    }
    
    bool stillOpen() {  //determine if there are still elements on the list that are open
        for (int i = 0; i < list.size(); i++) {
            if (list[i].open == true) {
                return true;
            }
        }
        return false;
    }
    
    int findBest() {   //find node with best f cost
        int index = -1;
        int f = list[0].gCost + list[0].hCost;
        for (int i = 1; i < list.size(); i++) {
            if (list[i].open && f > list[i].gCost + list[i].hCost) {
                f = list[i].gCost + list[i].hCost;
                index = i;
            }
        }
        return index;
    }
}
#endif /* InefficientAStar_hpp */
