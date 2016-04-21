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
    int GetHeuristic(TileState state);
    vector<int*> db; //database arrays
    long long rank(TileState state, vector<int> pattern);
//private:
    void buildPDB(vector<int> pattern);
    
    TileState unrank(long long rank, vector<int> pattern);
    long long factorial(long n);
    //void unRadix(TileState &in);
    //void radix(vector<int> &in);
    TileState buildPatternState(vector<int> pattern);
    
    
};


#endif /* PDB_hpp */
