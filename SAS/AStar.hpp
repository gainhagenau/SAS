//
//  AStar.hpp
//  SAS
//
//  Created by Ryan Aikman on 5/3/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef AStar_hpp
#define AStar_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

template <typename state, typename action, typename environment, typename heuristic>
class AStar {
public:
    AStar(){};
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
        //bool open;
        state s;
        action parentAction;
    };
    vector<node> open;    // open/closed list
    vector<node> closed;
    
    void addElement(node n) {  //push back the action
        int i = checkDuplicates(n);  //check for duplicates before adding
        if (i >= 0) {    // if there is a duplicate at index i, replace
            if ((open[i].gCost + open[i].hCost) > (n.gCost + n.hCost)){ //if the new generation of the node has a lower f cost it is replaced
                open[i] = n;
            }
        } else {    // no duplicates, just push back
            open.push_back(n);
        }
    }
    
    int checkDuplicates(node n) {
        for (int i = 0; i < open.size(); i++) {  // go through array, if a match is found return that index
            if (n.s == open[i].s) {
                return i;
            }
        }
        return -1;  // no duplicate
    }
    
    
    int findBest() {   //find node with best f cost
        int index = -1;
        int f = -1;
        for (int i = 0; i < open.size(); i++) {
            if (f > (open[i].gCost + open[i].hCost) || f == -1) {
                f = open[i].gCost + open[i].hCost;
                index = i;
            }
        }

        return index;
    }
    
    node MakeNode(state &s, int currentG, heuristic &h, action p){
        node newNode;
        newNode.s = s;
        newNode.gCost = currentG;
        newNode.hCost = h.GetHeuristic(s);
        newNode.parentAction = p;
        return newNode;
    }
    
    node getNode(int index){
        return open[index];
    }
    
    bool checkGoal(node &n, state &g){
        if (n.s == g){
            return true;
        }
        return false;
    }
    
    void pop(int index) {   //move node from open to closed list, delete from open list
        closed.push_back(open[index]);
        open.erase(open.begin() + index);
    }
    
};

template <typename state, typename action, typename environment, typename heuristic>
bool AStar<state, action, environment, heuristic>::GetPath(environment &e, state &start, state &goal, heuristic &h){
    nodesExpanded = 0;
    
    node current = MakeNode(start, 0, h, NONE);
    addElement(current);

    int nextToExpand = findBest();
    vector<action> moves;
    
    while(!open.empty()) {  //when no open nodes, exit
        current = getNode(nextToExpand);
        e.GetActions(current.s, moves); //update moves
        for (int i = 0; i < moves.size(); i++){
            if (moves[i] != e.InvertAction(current.parentAction)){ //parent pruning
                nodesExpanded++;
                state temp = current.s;
                e.ApplyAction(temp, moves[i]); //apply action
                node generated = MakeNode(temp, current.gCost + 1, h, moves[i]); //new node
                if (checkGoal(generated, goal)){
                    return true;  //Goal Found
                }
                addElement(generated);
            }
        }
        pop(nextToExpand);
        nextToExpand = findBest();
    }
    return false; //no solution found
}

#endif /* AStar_hpp */
