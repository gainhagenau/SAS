//
//  GridMaps.hpp
//  SAS
//
//  Created by Ryan Aikman on 5/4/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef GridMaps_hpp
#define GridMaps_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>    
#include <algorithm>
#include <math.h>
#include <string.h>
#include <fstream>

using namespace std;

//represents the current state in the search
struct MapState {
    int x, y;
    
    bool operator==(const MapState &s) const{
        return (s.x == x && s.y == y);
    }
};

//8 way movement
enum MapAction {NORTH, SOUTH, EAST, WEST, NORTHWEST, NORTHEAST, SOUTHEAST, SOUTHWEST};

class GridMaps {
public:
    GridMaps(MapState g);
    
    //translate x, y coordinates into index in map
    int getIndex(int x, int y);

    //Returns octile distance heuristic
    int GetHeuristic(MapState m);
    
    //This function takes a state and populates the actions vector with the possible actions from that state
    void GetActions(MapState &nodeID, vector<MapAction> &actions);
    
    //This function takes a state and applies an action to it that is also passed; changing the state to its new form
    void ApplyAction(MapState &s, MapAction a);
    
    //This function un-does an action on a state
    void UndoAction(MapState &s, MapAction a);
    
    MapAction InvertAction(MapAction a);
    
    string getString(MapState &m);
    
private:
    vector<bool> map;   //map to load from file
    MapState goal;
    int mapW, mapH; //save the size of the map to allow for easier map changes
};


#endif /* GridMaps_hpp */
