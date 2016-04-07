/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  SlidingTile.cpp
//  HW2
//


#include "SlidingTile.hpp"

SlidingTile::SlidingTile(TileState &nodeID) {
    int c = 0;
    for (int i = 0; i < 16; i++) {
        nodeID[i] = c++;    //load array
    }
    empty = 0;  //empty tile
}
void SlidingTile::GetActions(TileState &nodeID, vector<TileAction> &actions) {
    /* 0   1   2   3
       4   5   6   7
       8   9   10  11
       12  13  14  15
     */
    if (empty <= 3) {
        actions.push_back(UP);
    }
    if (empty != 3 && empty != 7 && empty != 11 && empty != 15) {
        actions.push_back(RIGHT);
    }
    if (empty != 0 && empty != 4 && empty != 8 && empty != 12) {
        actions.push_back(LEFT);
    }
    if (empty <= 11) {
        actions.push_back(DOWN);
    }
}

void SlidingTile::ApplyAction(TileState &s, TileAction a) {
    if (a == UP) {
        int temp = s[empty];
        s[empty] = s[empty - 4];
        s[empty - 4] = temp;
    } else if (a == DOWN) {
        int temp = s[empty];
        s[empty] = s[empty + 4];
        s[empty + 4] = temp;
    } else if (a == LEFT) {
        int temp = s[empty];
        s[empty] = s[empty - 1];
        s[empty - 1] = temp;
    } else if (a == RIGHT) {
        int temp = s[empty];
        s[empty] = s[empty + 1];
        s[empty + 1] = temp;
    }
}
void SlidingTile::UndoAction(TileState &s, TileAction a) {
    if (a == UP) {
        ApplyAction(s, DOWN);
    } else if (a == DOWN) {
        ApplyAction(s, UP);
    } else if (a == LEFT) {
        ApplyAction(s, RIGHT);
    } else if (RIGHT) {
        ApplyAction(s, LEFT);
    }
}