/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  BFS.hpp
//  Homework1
//


#ifndef BFS_hpp
#define BFS_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

template <typename state, typename action, typename environment>
class BFS{
public:
    BFS(){};
    ~BFS(){};
    
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal){
        nodesExpanded = 0; //reset nodesExpanded for the new search
        
        if (start == goal) { //checking if start is the goal state
            return true;
        }
        
        queue<state> q; //FOFI Queue
        q.push(start);
        state current;
        vector<action> actions;
        
        //run search
        while(!q.empty()) {
            state newState = q.front(); //get next node from queue
            q.pop();
            if (newState == goal) { //check for goal state
                return true;
            }
            
            e.GetActions(current, actions); //populates actions with the current avalible actions
            nodesExpanded++; //increment nodes expanded
            
            for (int i = 0; i < actions.size(); i++){ //execute actions and check children
                e.ApplyAction(newState, actions[i]); //execute action creating new state
                q.push(newState); //add the new state to the queue
                e.UndoAction(newState, actions[i]); //undo the action it just did
            }
        }
        return false; //no solution found
    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded(){return nodesExpanded;}
    
private:
    uint64_t nodesExpanded;
};

#endif /* BFS_hpp */
