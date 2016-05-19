//
//  LMDifferential.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/16/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "LMDifferential.hpp"
#include <Queue>
#include <math.h>

LMDifferential::LMDifferential(GridMaps *m, bool f, int numPivots) {
    cout << "Constructing an LMD...\n";
    map = m;
    furthest = f;
    distanceLists.resize(numPivots);
    pivotList.resize(numPivots);
    if (furthest){ //Furthest
        cout << "Calculating " << numPivots << " Furthest Pivots..." << endl;
        pivotList[0] = map->getRandomState(1)[0];
        BuildPivot(distanceLists[0], pivotList[0]);
        cout << "1" << endl;
        for (int i = 1; i < numPivots; i++) {
            MapState nextPivot = FindFurthest(i - 1); //finds what the next pivot should be for indes i
            pivotList[i] = nextPivot;
            BuildPivot(distanceLists[i], pivotList[i]); //builds the distances
        }
    } else { //All Random
        cout << "Calculating " << numPivots << " Random Pivots...    " << endl;
        pivotList = map->getRandomState(numPivots);
        for (int i = 0; i < numPivots; i++) {
            BuildPivot(distanceLists[i], pivotList[i]); //builds the distances
        }
    }
    cout << "Complete\n";
}

//returns the heuristic
int LMDifferential::GetHeuristic(MapState state){
    int heuristic = -1;
    if (!distanceLists.empty()){
        MapState goal = map->getGoal(); //gets the goal from the map
        vector<int> distances = distanceLists[0]; //sets the first one
        float x = pow(distances[map->getIndex(state.x, state.y)], 2.0);
        float y = pow(distances[map->getIndex(goal.x, goal.y)], 2.0);
        heuristic = (int)sqrt(x + y);
        
        for (int i = 0; i < distanceLists.size(); i++){ //gets the max of all the rest of the remaining pivot heuristics
            distances = distanceLists[i];
            x = pow(distances[map->getIndex(state.x, state.y)], 2.0);
            y = pow(distances[map->getIndex(goal.x, goal.y)], 2.0);
            int h = (int)sqrt(x + y);
            if (h > heuristic){
                heuristic = h;
            }
        }
    }
    //take max of octile and LMDifferential
    int h = map->GetHeuristic(state);
    if (h > heuristic) {
        heuristic = h;
    }
    return heuristic;
}

//populate the pivot array based on the pivot passed in
void LMDifferential::BuildPivot(vector<int> &pivotArray, MapState p){
    cout << "Starting build on pivot: " << p.x << "," << p.y << endl;
    //set to size of index
    pivotArray.resize(map->getSize());
    
    AStar<MapState, MapAction, GridMaps, GridMaps> AStar;
    //for every valid index run A* and find distance from that state to pivot state
    for (int i = 0; i < pivotArray.size(); i++) {
        MapState m = map->getMapState(i);
        if (map->isValid(m.x, m.y) && map->isValid(p.x, p.y)) {
            cout << "Finding Cost from: " << m.x << "," << m.y <<endl;
            if (AStar.GetPath(*map, m, p, *map)) { //map passed twice for stright line heuristic
                cout << "One Calculated!" << endl;
                pivotArray[i] = AStar.getCostOfPreviousSolution();
            }
        } else {
        }
    }
}

//finds the furthest state from all of the states lower and including the index passes in the pivotList
MapState LMDifferential::FindFurthest(int index){
    vector<MapState> closed;
    vector<MSG> open;
    vector<MapAction> actions;
    MapState lastCreated;
    for (int i = index; i >= 0; i--){ //Add all created indexes to the open list
        MSG p;
        p.g = 0;
        p.m = pivotList[i];
        open.push_back(p);
    }
    
    while (!open.empty()){
        int next = 0;
        for (int i = 1; i < closed.size(); i++ ){ //find the next best on open
            if (open[i].g < open[next].g){
                next = i;
            }
        }
        MapState current = open[next].m; //sets the next map state
        int currentG = open[next].g;
        closed.push_back(current);
        open.erase(open.begin() + next); //moving from open to closed now
        lastCreated = current;
        
        map->GetActions(current, actions); //get actions
        for (int i = 0; i < actions.size(); i++){
            map->ApplyAction(current, actions[i]);
            bool duplicate = false; //check for duplicates
            for (int j = 0; j < closed.size(); j++){
                if (closed[j] == current){
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate){ //add new node to the open list
                MSG msg; msg.m = current; msg.g = currentG + 1; //Creates new MSG
                open.push_back(msg);
            }
            map->UndoAction(current, actions[i]); //undo action
        }
    }
    return lastCreated;
}
