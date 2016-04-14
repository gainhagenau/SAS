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
#include "SlidingTile.hpp"

class PDB {
public:
    PDB(){};
    int GetHeuristic(TileState state);
//private:
    void buildPDB();
    int rank(TileState state);
    TileState unrank(int rank);
    int factorial(int n);
    void unRadix(TileState &in);
};


#endif /* PDB_hpp */
