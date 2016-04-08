/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  STmanhattan.cpp
//  SAS
//
//  Created by Gain Hagenau on 4/6/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "STmanhattan.hpp"

using namespace std;

//Assumes goal state:
/* 
 0   1   2   3
 4   5   6   7
 8   9   10  11
 12  13  14  15
 */

//Returns Manhattan
int STmanhattan::GetHeuristic(TileState state){
    int ManDist = 0;
    for (int i = 1; i < 16; i++) { //distance of empty slot not included
        int x;
        for (x = 0; x < 16; x++){ //get current position of i value
            if (i == state.state[x]){
                break;
            }
        }
        //vertical difference
        int irow = i / 4;
        int xrow = x / 4;
        ManDist += abs(irow - xrow);
        
        //horizontal differnece
        int icol = i % 4;
        int xcol = x % 4;
        ManDist += abs(icol - xcol);
    }
    
    return ManDist;
}