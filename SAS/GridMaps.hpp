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
};

//8 way movement
enum MapAction {UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT};

class GridMaps {
public:
    GridMaps(int sX, int sY, int gX, int gY);
    
    // check if the starting position and ending position are valid on the map
    bool isValidPosition(int x, int y);
    
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
private:
    vector<bool> map;   //map to load from file
    int startX, startY, goalX, goalY;
};


#endif /* GridMaps_hpp */
