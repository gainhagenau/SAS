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
    for (long i = 15; i >= 0; i--) {
        nextRank = (rank % factorial(i));
        digit = (rank / factorial(i));
        toReturn.state[j++] = digit;
        rank = nextRank;
    }
    unRadix(toReturn);
    return toReturn;
}

long PDB::factorial(long n) {
    long factorial = 1;
    if (n <= 16 ) {
        switch (n) {
            case 0:
                return 1;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 6;
            case 4:
                return 24;
            case 5:
                return 120;
            case 6:
                return 720;
            case 7:
                return 5040;
            case 8:
                return 40320;
            case 9:
                return 362880;
            case 10:
                return 3628800;
            case 11:
                return 39916800;
            case 12:
                return 479001600;
            case 13:
                return 6227020800;
            case 14:
                return 87178291200;
            case 15:
                return 1307674368000;
            case 16:
                return 20922789890000;
        }
    } else {
        factorial = 1;
        while (n != 0) {
            factorial *= n--;
        }
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
