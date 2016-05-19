//
//  LMDifferential.hpp
//  SAS
//
//  Created by Ryan Aikman on 5/16/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef LMDifferential_hpp
#define LMDifferential_hpp

#include <stdio.h>
#include "GridMaps.hpp"
#include "AStar.hpp"

#endif /* LMDifferential_hpp */

struct MSG{ //MapState with g cost
    MapState m;
    int g;
};


class LMDifferential {
public:
    LMDifferential(GridMaps *m, bool f, int numPivots);
    
    //returns the heuristic
    int GetHeuristic(MapState state);
    
    //populate the pivot array based on the pivot passed in
    void BuildPivot(vector<int> &pivotArray, MapState p);
    
    //finds the furthest state from the state passed in
    MapState FindFurthest(int index);
        
private:
    GridMaps *map;
    bool furthest;
    vector<vector<int>> distanceLists;
    vector<MapState> pivotList;
};
