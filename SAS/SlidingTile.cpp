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

void SlidingTile::GetActions(TileState &nodeID, vector<TileAction> &actions) {
    /* 0   1   2   3
       4   5   6   7
       8   9   10  11
       12  13  14  15
     */
    actions.clear();
    if (nodeID.state[empty] != 0) {
        updateEmpty(nodeID);
    }
    if (empty > 3) {
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
    if (s.state[empty] != 0) {
        updateEmpty(s);
    }
    if (a == UP) {
        s.state[empty] = s.state[empty - 4];
        s.state[empty - 4] = 0;
        empty = empty - 4;
    } else if (a == DOWN) {
        s.state[empty] = s.state[empty + 4];
        s.state[empty + 4] = 0;
        empty = empty + 4;
    } else if (a == LEFT) {
        s.state[empty] = s.state[empty - 1];
        s.state[empty - 1] = 0;
        empty = empty -1;
    } else if (a == RIGHT) {
        s.state[empty] = s.state[empty + 1];
        s.state[empty + 1] = 0;
        empty = empty + 1;
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

void SlidingTile::updateEmpty(TileState &s) {
    for (int i = 0; i < 16; i++) {
        if (s.state[i] == 0) {
            empty = i;
            return;
        }
    }
}

TileAction SlidingTile::InvertAction(TileAction a) {
    switch (a) // invert action
    {
        case UP: return DOWN; break;
        case DOWN: return UP; break;
        case LEFT: return RIGHT; break;
        case RIGHT: return LEFT; break;
        case NONE: return NONE; break;
    }
}
