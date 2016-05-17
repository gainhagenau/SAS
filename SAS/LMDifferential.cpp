//
//  LMDifferential.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/16/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "LMDifferential.hpp"

int GetHeuristic(MapState state) {
    
    // DIFFERENTIAL RANDOM
    if (
    int randomX, randomY;
    randomX = rand() % mapW;
    randomY = rand() % mapH;
    
    while(!isValid(randomX, randomY)) {
        randomX = rand() % mapW;
        randomY = rand() % mapH;
    }
}
//DIFFERENTIAL FARTHEST