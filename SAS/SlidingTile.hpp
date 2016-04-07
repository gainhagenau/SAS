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
#include <vector>

using namespace std;

enum TileAction {UP, DOWN, LEFT, RIGHT};

typedef int TileState[16];

class SlidingTile {
public:
    SlidingTile(){};
    ~SlidingTile(){};
    void GetActions(TileState &nodeID, vector<TileAction> &actions);
    void ApplyAction(TileState &s, TileAction a);
    void UndoAction(TileState &s, TileAction a);
    void cost_limited_dfs(int limit, TileState &s);
private:
    int empty;
    void updateEmpty(TileState &s);
};

#endif /* SlidingTile_hpp */
