//
//  PDB.hpp
//  SAS
//
//  Created by Ryan Aikman on 4/13/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef PDB_hpp
#define PDB_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "SlidingTile.hpp"
#include <vector>


class PDB {
public:
    PDB(vector<vector<int>> patterns);
    ~PDB();
    int GetHeuristic(TileState state);
private:
    void buildPDB(vector<int> pattern);
    long long rank(TileState state, vector<int> pattern);
    TileState unrank(long long rank, vector<int> pattern);
    long long factorial(long n);
    TileState buildPatternState(vector<int> pattern);
    
    vector<int*> db; //database arrays
};


#endif /* PDB_hpp */
