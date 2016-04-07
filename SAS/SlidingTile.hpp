//
//  SlidingTile.hpp
//  HW2
//
//  Created by Ryan Aikman and Gain Hagenau on 4/2/16.
//

#ifndef SlidingTile_hpp
#define SlidingTile_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

enum TileAction {UP, DOWN, LEFT, RIGHT};

typedef int TileState[16];

class SlidingTile {
public:
    SlidingTile(TileState &nodeID);
    ~SlidingTile(){};
    void GetActions(TileState &nodeID, vector<TileAction> &actions);
    void ApplyAction(TileState &s, TileAction a);
    void UndoAction(TileState &s, TileAction a);
private:
    int empty;

};

#endif /* SlidingTile_hpp */
