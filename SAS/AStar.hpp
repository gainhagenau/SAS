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
#include <unordered_map>
#include <map>
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
        state s;
        action parentAction;
    };
    
    typedef unordered_map<node,int> nodeMap;
    
    nodeMap open;    // open map
    typename nodeMap::hasher fn = open.hash_function();

    
    vector<node> closed;    //closed list
    
    /* Add element to open list
     * check for duplicates first. If index just replace if better f cost in new node
     * else just push onto open list
     */
    void addElement(node n) {

    }
    
    // check to see if there is a duplicate on the open list. Return -1 if no duplicate
    int checkDuplicates(node n) {

    }
    
    // return the index of the node with the best f cost
    int findBest() {
       
    }
    
    // node constructor
    node MakeNode(state &s, int currentG, heuristic &h, action p){
        node newNode;
        newNode.s = s;
        newNode.gCost = currentG;
        newNode.hCost = h.GetHeuristic(s);
        newNode.parentAction = p;
        return newNode;
    }
    
    // helper function to return the node at a certain index
    node getNode(int index){

    }
    
    // helper function to check to see if the goal has been reached
    bool checkGoal(node &n, state &g){
        if (n.s == g){
            return true;
        }
        return false;
    }
    
    // move node from open to closed list, delete from open list
    void pop(int index) {

    }
    
};

/*******************************************************************
 ************************** Algorithm ******************************
 *******************************************************************/
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
