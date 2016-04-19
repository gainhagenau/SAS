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
#include "vector"


class PDB {
public:
    PDB(vector<vector<int>> patterns);
    int GetHeuristic(TileState state);
    vector<int*> db; //database arrays
private:
    void buildPDB(vector<int> pattern);
    int rank(TileState state);
    TileState unrank(int rank);
    long factorial(long n);
    void unRadix(TileState &in);
    void radix(TileState &in);
    TileState buildPatternState(vector<int> pattern);
    
    
};


#endif /* PDB_hpp */
