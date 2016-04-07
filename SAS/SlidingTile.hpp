/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  SlidingTile.hpp
//  HW2
//


#ifndef SlidingTile_hpp
#define SlidingTile_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

enum moves {UP, DOWN, LEFT, RIGHT};

class SlidingTile {
public:
    int puzzle[4][4];
    SlidingTile();
    ~SlidingTile(){}
    bool isValid(moves m);
    bool applyMove(moves m);
    bool isSolved();
};

#endif /* SlidingTile_hpp */
