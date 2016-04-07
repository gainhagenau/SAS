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

SlidingTile::SlidingTile() {
    int c = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            puzzle[j][i] = c++;
        }
    }
}

bool SlidingTile::isValid(moves m) {
    for (int i = 0; i < 4; i++) {
        if (puzzle[0][i] == 0 && m == LEFT) {
            return false;
        } else if (puzzle[i][0] == 0 && m == UP) {
            return false;
        } else if (puzzle[i][3] == 0 && m == DOWN) {
            return false;
        } else if (puzzle[3][i] == 0 && m == RIGHT) {
            return false;
        }
    }
    return true;
}

bool SlidingTile::applyMove(moves m) {
    int x, y;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (puzzle[j][i] == 0) {
                x = j;
                y = i;
            }
        }
    }
    int temp;
    if (isValid(m)) {
        if (m == RIGHT) {
            temp = puzzle[x][y];
            puzzle[x][y] = puzzle[x+1][y];
            puzzle[x+1][y] = temp;
            return true;
        } else if (m == LEFT) {
            temp = puzzle[x][y];
            puzzle[x][y] = puzzle[x-1][y];
            puzzle[x-1][y] = temp;
            return true;
        } else if (m == UP) {
            temp = puzzle[x][y];
            puzzle[x][y] = puzzle[x][y+1];
            puzzle[x][y+1] = temp;
            return true;
        } else if (m == DOWN) {
            temp = puzzle[x][y];
            puzzle[x][y] = puzzle[x][y-1];
            puzzle[x][y-1] = temp;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool SlidingTile::isSolved() {
    int c = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(puzzle[j][i] != c++) {
                return false;
            }
        }
    }
    return true;
}