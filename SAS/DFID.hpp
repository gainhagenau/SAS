/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  DFIS.hpp
//  Homework1
//


#ifndef DFID_hpp
#define DFID_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename state, typename action, typename environment>
class DFID{
    public:
    DFID(){};
    ~DFID(){};
    
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal){
        nodesExpanded = 0;
        int maxDepth = 0;
        bool found = false;
        while (!found) { //continue going deeper until a solution is found
            found = DLS(e, goal, start, maxDepth); //run a Depth Limited Search starting at the root
            maxDepth++; //increase the depth the DLS goes
        }
        if (found) {
            return true;
        }
        return false;
    }
    
    bool DLS(environment &e, state &goal, state &node, int depth){
        if (depth == 0 && node == goal) {
            return true;
        }
        else if (depth > 0){
            vector<action> actions;
            e.GetActions(node, actions);
            nodesExpanded++; //another node has been expanded
            for(int i = 0; i < actions.size(); i++){
                e.ApplyAction(node, actions[i]); //get the next child node
                bool found = DLS(e, goal, node, depth-1); //run DLS on the new node with one less depth
                if (found) {
                    return true; //if goal found return true
                }
                else{
                    e.UndoAction(node, actions[i]); //if not goal undo action
                }
            }
        }
        return false;

    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded(){return nodesExpanded;}
    
    
    
    private:
    uint64_t nodesExpanded;
};




#endif /* DFID_hpp */
