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
    
    int getCostOfPreviousSolution(){
        return costOfSolution;
    }
    
private:
    uint64_t nodesExpanded; // nodes expanded
    int costOfSolution;
    
    struct node {
        int gCost, hCost;
        state s;
        action parentAction;
    };
    
    unordered_map<string, node> openTable;
    unordered_map<string, node> closedTable;
    bool isFirst = true;

    /* Add element to open list
     * check for duplicates first. If index just replace if better f cost in new node
     * else just push onto open list
     */
    void addElement(node n, environment &e) {
        if (!checkDuplicates(n, e)){ //if no duplicate found
            openTable.insert(std::make_pair(e.getString(n.s), n));
        }
    }
    
    // check to see if there is a duplicate on the open list.
    //If there is then it evaluates the best, returns true if a duplicate was found
    //also checks closed list to potentially re add a node to open
    bool checkDuplicates(node n, environment &e) {
        //checking open list
        auto check = openTable.find(e.getString(n.s));
        if(check != openTable.end()) {
            //found duplicate
            if ((check->second.gCost + check->second.hCost) > (n.gCost + n.hCost)){ //should be replaced
                check->second = n;
                return true;
            }
        }
        //checking closed list for potential update
        check = closedTable.find(e.getString(n.s));
        if(check != closedTable.end()) {
            //found duplicate
            if ((check->second.gCost + check->second.hCost) > (n.gCost + n.hCost)){ //should be updated and added to open
                openTable.insert(std::make_pair(e.getString(n.s), n));
                closedTable.erase(check);
                return true;
            }
        }
        return false;
    }
    
    // return the index of the node with the best f cost
    node findBest(environment &e) {
        node best;
        bool first = true;
        for ( auto i = openTable.begin(); i != openTable.end(); i++ ){
            if (first){
                best = i->second;
                first = false;
            } else if ((best.gCost + best.hCost) > (i->second.gCost + i->second.hCost)){ //new best
                best = i->second;
            }
        }
        //moves best to closed and returns
        openTable.erase(e.getString(best.s));
        closedTable.insert(std::make_pair(e.getString(best.s), best));
        return best;
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
    
    // helper function to check to see if the goal has been reached
    bool checkGoal(node &n, state &g){
        if (n.s == g){
            return true;
        }
        return false;
    }
    
    bool isEmpty(){
        return openTable.empty();
    }
    
    void clear(){
        openTable.clear();
        closedTable.clear();
    }
};
/*******************************************************************
 ************************** Algorithm ******************************
 *******************************************************************/
template <typename state, typename action, typename environment, typename heuristic>
bool AStar<state, action, environment, heuristic>::GetPath(environment &e, state &start, state &goal, heuristic &h){
    
    if (start == goal){
        costOfSolution = 0;
        return true;
    }
    
    
    clear(); // clears data strucutres
    bool isFirst = true;
    
    nodesExpanded = 0;
    
    node current = MakeNode(start, 0, h, static_cast<action>(1));
    addElement(current, e);
    
    vector<action> moves;
    
    while(!isEmpty()) {  //when no open nodes, exit
        current = findBest(e);
        e.GetActions(current.s, moves); //update moves
        nodesExpanded++;
        //No parent pruning
        if(isFirst) {
            for (int i = 0; i < moves.size(); i++) {
                state temp = current.s;
                e.ApplyAction(temp, moves[i]); //apply action
                node generated = MakeNode(temp, current.gCost + 1, h, moves[i]); //new node
                if (checkGoal(generated, goal)){
                    costOfSolution = generated.gCost;
                    return true;  //Goal Found
                }
                addElement(generated, e);
            }
            isFirst = false;
        } else {
            for (int i = 0; i < moves.size(); i++){
                if (moves[i] != e.InvertAction(current.parentAction)){ //parent pruning
                    state temp = current.s;
                    e.ApplyAction(temp, moves[i]); //apply action
                    node generated = MakeNode(temp, current.gCost + 1, h, moves[i]); //new node
                    if (checkGoal(generated, goal)){
                        costOfSolution = generated.gCost;
                        return true;  //Goal Found
                    }
                    addElement(generated, e);
                }
            }
        }
    }
    return false; //no solution found
}



#endif /* AStar_hpp */
