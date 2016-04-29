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
        int gCost, hCost;
        bool open;
        state s;
        action parentAction;
    };
    vector<node> list;    // open/closed list
    
    void addElement(node n) {  //push back the action
        int i = checkDuplicates(s, list);  //check for duplicates before adding
        if (i >= 0) {    // if there is a duplicate at index i, replace
            if (list[i].gCost + list[i].hCost > n.gCost + n.hCost){ //if the new generation of the node has a lower f cost it is replaced
                list[i] = n;
            }
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
    
    
    int findBest() {   //find node with best f cost
        int index = -1;
        int f = -1;
        for (int i = 1; i < list.size(); i++) {
            if (list[i].open && f > list[i].gCost + list[i].hCost || f == -1) {
                f = list[i].gCost + list[i].hCost;
                index = i;
            }
        }
        if (index >= 0){
            list[index].open = false;
        }
        return index;
    }
    
    node MakeNode(state &s, int currentG, heuristic &h, action p){
        node newNode;
        newNode.state = s;
        newNode.gCost = currentG;
        newNode.hCost = h.GetHeuristic(s);
        newNode.open = true;
        newNode.parentAction = p;
        return newNode;
    }
    
    node getNode(int index){
        return list[index];
    }
    
    bool checkGoal(node &n, state &g){
        if (n.state == g){
            return true;
        }
        return false;
    }
    
    
}


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
bool GetPath(environment &e, state &start, state &goal, heuristic &h){
    nodesExpanded = 0;
    
    node current = MakeNode(s, 0, h, null);
    addElement(current);
    
    int nextToExpand = findBest();
    vector<action> moves;
    
    while(nextToExpand >= 0){ //when no open nodes this will be -1 and exit
        current = getNode(nextToExpand);
        e.GetActions(current.state, moves); //update moves
        for (int i = 0; i < moves.size; i++){
            if (moves[i] == e.InvertAction(current.parentAction)){ //parent pruning
                nodesExpanded++;
                state temp = current.state;
                node generated = MakeNode(e.ApplyAction(temp, moves[i]), current.gCost + 1, h, moves[i]); //new node
                if (checkGoal(generated, goal)){
                    return true;  //Goal Found
                }
                addElement(generated);
            }
        }
        nextToExpand = findBest();
    }
    return false; //no solution found
}




#endif /* InefficientAStar_hpp */
