//
//  PDB.cpp
//  SAS
//
//  Created by Ryan Aikman on 4/13/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "PDB.hpp"

int GetHeuristic(TileState state) {
    return 0;
}

void buildPDB() {
    
}

int rank(TileState state) {
    return 0;
}

TileState PDB::unrank(int rank) {
    int nextRank;
    int digit;
    TileState toReturn;
    int j = 0;
    for (int i = 14; i >= 0; i--) {
        nextRank = (rank % factorial(i));
        digit = (rank / factorial(i));
        toReturn.state[j++] = digit;
        rank = nextRank;
    }
    unRadix(toReturn);
    return toReturn;
}

int PDB::factorial(int n) {
    int factorial = 1;
    while (n != 0) {
        factorial *= n--;
    }
    return factorial;
}

void PDB::unRadix(TileState &in) {
    for (int i = 0; i < 4; i++) {
        for (int j = (i+1); j < 4; j++) {
            if (in.state[j] >= in.state[i]) {
                in.state[j]++;
            }
        }
    }

}