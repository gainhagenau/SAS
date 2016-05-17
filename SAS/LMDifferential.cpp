//
//  LMDifferential.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/16/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "LMDifferential.hpp"
#include <Queue>

LMDifferential::LMDifferential(GridMaps &m, bool f) {
    map() = m;
    furthest = f;
}

//returns the heuristic
int LMDifferential::GetHeuristic(MapState state){
    if (furthest) {
        
    } else {
        
    }
}

//populate the pivot array based on the pivot passed in
void LMDifferential::BuildPivot(vector<int> &pivotArray, MapState p){
    //set to size of index
    pivotArray.clear();
    pivotArray.resize(map().getSize());
    
    AStar<MapState, MapAction, GridMaps, GridMaps> AStar;
    //for every valid index run A* and find distance from that state to pivot state
    for (int i = 0; i < pivotArray.size(); i++) {
        MapState m = map().getMapState(i);
        if (map().isValid(m.x, m.y)) {
            GridMaps grid(map().getMapState(i));
            if (AStar.GetPath(grid, p, m, grid)) {
                pivotArray.push_back(AStar.getCostOfPreviousSolution());
            }
        }
    }
}

//finds the furthest state from the state passed in
MapState LMDifferential::FindFurthest(MapState p){
    vector<MapState> closed;
    queue<MapState> open;
    vector<MapAction> actions;
    MapState final;
    open.push(p);
    while (!open.empty()){
        bool createdNew = false;
        MapState current = open.front(); open.pop(); //get next state
        map().GetActions(current, actions);
        for (int i = 0; i < actions.size(); i++){
            map().ApplyAction(current, actions[i]);
            bool duplicate = false; //check for duplicates
            for (int j = 0; j < closed.size(); j++){
                if (closed[j] == current){
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate){ //add new node to the open list
                open.push(current);
                createdNew = true;
            }
            map().UndoAction(current, actions[i]); //undo action
        }
        if (!createdNew && open.empty()){
            final = current;
        }
    }
    return final;
}
