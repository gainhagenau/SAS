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

enum TileAction {UP, DOWN, LEFT, RIGHT, NONE};


struct TileState{
    
    int state[16];
    
    bool operator==(const TileState &s) const{
        for (int i = 0; i < 16; i++){
            if (s.state[i] != state[i]){
                return false;
            }
        }
        return true;
    }

};


class SlidingTile {
public:
    SlidingTile(){};
    ~SlidingTile(){};
    void GetActions(TileState &nodeID, vector<TileAction> &actions);
    void ApplyAction(TileState &s, TileAction a);
    void UndoAction(TileState &s, TileAction a);
    TileAction InvertAction(TileAction a);
private:
    int empty = 0;
    void updateEmpty(TileState &s);
};

#endif /* SlidingTile_hpp */
