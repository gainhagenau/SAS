//
//  GridEnvironment.cpp
//  Homework1
//
//  Created by Gain Hagenau and Ryan Aikman on 3/28/16.
//

#include "GridEnvironment.hpp"

using namespace std;

GridEnvironment::GridEnvironment(int s){
    size = s;
}

void GridEnvironment::GetActions(GridState &s, vector<GridAction> &actions){
    actions.clear();
    if (s.x < size - 1) { //up
        actions.push_back(up);
    }
    if (s.y < size - 1){ //right
        actions.push_back(right);
    }
}

void GridEnvironment::ApplyAction(GridState &s, GridAction a){
    if (a == up && s.x < size - 1){ //up
        s.x++;
    }
    if (a == right && s.y < size - 1){ //right
        s.y++;
    }
}

void GridEnvironment::UndoAction(GridState &s, GridAction a){
    if (a == up && s.x != 0){ //up --> down
        s.x--;
    }
    if (a == right && s.y != 0){ //right --> left
        s.y--;
    }
}

bool GridEnvironment::CompareStates(GridState &a, GridState &b){
    if (a.x == b.x && a.y == b.y){
        return true;
    }
    return false;
}