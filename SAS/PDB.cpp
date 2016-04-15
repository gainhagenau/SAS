//
//  PDB.cpp
//  SAS
//
//  Created by Ryan Aikman on 4/13/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "PDB.hpp"

int PDB::GetHeuristic(TileState state) {
    return 0;
}

void PDB::buildPDB() {
    
}

int PDB::rank(TileState state) {
    radix(state);
    int toReturn = 0;
    for (int i = 0; i < 16; i++) {
        toReturn += (state.state[i] * factorial(i));
    }
    return toReturn;
}

TileState PDB::unrank(int rank) {
    int nextRank;
    int digit;
    TileState toReturn;
    int j = 0;
    for (int i = 15; i >= 0; i--) {
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
    for (int i = 0; i < 16; i++) {
        for (int j = (i+1); j < 16; j++) {
            if (in.state[j] >= in.state[i]) {
                in.state[j]++;
            }
        }
    }

}

void PDB::radix(TileState &in) {
    for (int i = 0; i < 16; i++) {
        for (int j = (i+1); j < 16; j++) {
            if (in.state[j] >= in.state[i]) {
                in.state[j]--;
            }
        }
    }
}
