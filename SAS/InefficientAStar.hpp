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
        state s;
        action parentAction;
    };
    vector<node> open;    // open/closed list
    vector<node> closed;
    
    // adds an element to the open list
    void addElement(node n) {
        int i = checkDuplicates(n, open);  //check for duplicates before adding
        if (i >= 0) {    // if there is a duplicate at index i, replace
            if ((open[i].gCost + open[i].hCost) > (n.gCost + n.hCost)){ //if the new generation of the node has a lower f cost it is replaced
                open[i] = n;
                return;
            }
        } else {    //check the closed list
            i = checkDuplicates(n, closed);
            if (i >= 0) {    // if there is a duplicate at index i, replace
                if ((closed[i].gCost + closed[i].hCost) > (n.gCost + n.hCost)){ //moves node back to open if better duplicate generated
                    open.push_back(n);
                    closed.erase(closed.begin() + i);
                    return;
                }
            }
        }
        open.push_back(n);
    }
    
    // check if there are any duplicates on the open list
    int checkDuplicates(node n, vector<node> &list) {
        for (int i = 0; i < list.size(); i++) {  // go through array, if a match is found return that index
            if (n.s == list[i].s) {
                return i;
            }
        }
        return -1;  // no duplicate
    }
    
    // find the index of node with the best f cost
    node findBest() {
        int index = -1;
        int f = -1;
        for (int i = 0; i < open.size(); i++) {
            if (f > (open[i].gCost + open[i].hCost) || f == -1) {
                f = open[i].gCost + open[i].hCost;
                index = i;
            }
        }
        //moves the best to closed and then returns it
        node toReturn = open[index];
        closed.push_back(open[index]);
        open.erase(open.begin() + index);
        return toReturn;
    }
    
    // Node constructor
    node MakeNode(state &s, int currentG, heuristic &h, action p){
        node newNode;
        newNode.s = s;
        newNode.gCost = currentG;
        newNode.hCost = h.GetHeuristic(s);
        newNode.parentAction = p;
        return newNode;
    }
    
    // helper function to see if you have reached the goal state
    bool checkGoal(node &n, state &g){
        if (n.s == g){
            return true;
        }
        return false;
    }
    
    // move node from the open to the closed list and then delete off the open list
    void pop(int index) {
        //closed.push_back(open[index]);
        open.erase(open.begin() + index);
    }
    
};

/*******************************************************************
 ************************** Algorithm ******************************
 *******************************************************************/
template <typename state, typename action, typename environment, typename heuristic>
bool InefficientAStar<state, action, environment, heuristic>::GetPath(environment &e, state &start, state &goal, heuristic &h){
    nodesExpanded = 0;
    
    node current = MakeNode(start, 0, h, static_cast<action>(1));
    addElement(current);
    
    vector<action> moves;
    
    while(!open.empty()) {  //when no open nodes, exit
        current = findBest();
        e.GetActions(current.s, moves); //update moves
        nodesExpanded++;
        int isFirst = 1;
        //first because no parent
        if (isFirst == 1) {
            for (int i = 0; i < moves.size(); i++) {
                state temp = current.s;
                e.ApplyAction(temp, moves[i]); //apply action
                node generated = MakeNode(temp, current.gCost + 1, h, moves[i]); //new node
                if (checkGoal(generated, goal)){
                    return true;  //Goal Found
                }
                addElement(generated);
            }
            isFirst = 0;
        }
        
        for (int i = 0; i < moves.size(); i++){
            if (moves[i] != e.InvertAction(current.parentAction)){ //parent pruning
                state temp = current.s;
                e.ApplyAction(temp, moves[i]); //apply action
                node generated = MakeNode(temp, current.gCost + 1, h, moves[i]); //new node
                if (checkGoal(generated, goal)){
                    return true;  //Goal Found
                }
                addElement(generated);
            }
        }
    }
    return false; //no solution found
}


#endif /* InefficientAStar_hpp */