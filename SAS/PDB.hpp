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

#include "SlidingTile.hpp"

#include <stdio.h>
#include <cmath>

class PDB {
public:
    PDB(){};
    ~PDB(){};
    int GetHeuristic(TileState state);
private:
    int rank(TileState state);
    TileState unrank(int n);
    void buildPDB();
};


#endif /* PDB_hpp */
