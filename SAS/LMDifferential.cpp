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

}

//finds the furthest state from the state passed in
MapState LMDifferential::FindFurthest(MapState p){
    vector<MapState> closed;
    queue<MapState> open;
    vector<MapAction> actions;
    open.push(p);
    while (!open.empty()){
        MapState current = 
        
        
        
    }
    MapState final;
    final.x = 1;
    final.y = 2;
    return final;
}