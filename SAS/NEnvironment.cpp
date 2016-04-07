/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  NEnvironment.cpp
//  Homework1
//
//  Created by Gain Hagenau and Ryan Aikman on 3/29/16.
//

#include "NEnvironment.hpp"

//Return avalible actions from that state
void NEnvironment::GetActions(NState &s, vector<int> &actions){
    actions.clear(); //clear the current actions
    for (int i = 0; i < branching; i++){
        actions.push_back(i);
    }
}

//apply an action to a state
void NEnvironment::ApplyAction(NState &s, int a){
    s.num = (s.num * branching) + a + 1; //gets the next child for that action. assumes the root is 0
}

//undo an action on a state
void NEnvironment::UndoAction(NState &s, int a){
    s.num = (s.num - 1 - a) / branching; //since it is an int it will take the floor of the value
}

//Returns true if the states are the same
bool NEnvironment::CompareStates(NState &a, NState &b){
    if (a.num == b.num) {
        return true;
    }
    return false;
}