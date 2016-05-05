//
//  GridMaps.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/4/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "GridMaps.hpp"

GridMaps::GridMaps(int sX, int sY, int gX, int gY) {
    startX = sX;
    startY = sY;
    goalX = gX;
    goalY = gY;
    
    ifstream file;
    file.open("/Users/Ryan/Documents/Junior/Spring/Single Agent Search/GitHub/SAS/SAS/orz301d.map", ios::in);
    
    char c;
    while (!file.eof()) {
        file.get(c);
        if (c == '.' && c != '\n') {
            map.push_back(true);
        } else if (c != '\n') {
            map.push_back(false);
        }
    }
}

bool GridMaps::isValidPosition(int x, int y) {
    int index = x + (y * 120);
    return map[index];
}

int GridMaps::getIndex(int x, int y) {
    int index = x + (y * 120);
    return index;
}

int GridMaps::GetHeuristic(MapState m) {
    // x = x distance to goal
    // y = y distance to goal
    int x = abs(goalX - m.x);
    int y = abs(goalY - m.y);
    return (max(x, y) + (sqrt(2)-1)*min(x, y));
}

void GridMaps::GetActions(MapState &nodeID, vector<MapAction> &actions) {
    int index = getIndex(nodeID.x, nodeID.y);
    actions.clear();

    //UP
    if (index - 120 > 0 && map[index] == true) {
        actions.push_back(UP);
    }
    //DOWN
    if (index + 120 < 3600 && map[index] == true) {
        actions.push_back(DOWN);
    }
    //LEFT
    if (((index + 1) % 120) != 0 && map[index] == true) {
        actions.push_back(LEFT);
    }
    //RIGHT
    if ((index % 120) != 0 && map[index] == true) {
        actions.push_back(RIGHT);
    }
    //UPRIGHT
    if ((find(actions.begin(), actions.end(), RIGHT) != actions.end()) && (find(actions.begin(), actions.end(), UP) != actions.end())) {
        actions.push_back(UPRIGHT);
    }
    //UPLEFT
    if ((find(actions.begin(), actions.end(), LEFT) != actions.end()) && (find(actions.begin(), actions.end(), UP) != actions.end())) {
        actions.push_back(UPLEFT);
    }
    //DOWNRIGHT
    if ((find(actions.begin(), actions.end(), RIGHT) != actions.end()) && (find(actions.begin(), actions.end(), DOWN) != actions.end())) {
        actions.push_back(DOWNRIGHT);
    }
    //DOWNLEFT
    if ((find(actions.begin(), actions.end(), DOWN) != actions.end()) && (find(actions.begin(), actions.end(), LEFT) != actions.end())) {
        actions.push_back(DOWNLEFT);
    }
}

void GridMaps::ApplyAction(MapState &s, MapAction a) {
    int index = getIndex(s.x, s.y);
    if (a == UP) {
        map[index];
    } else if (a == DOWN) {
        
    } else if (a == LEFT) {
        
    } else if (a == RIGHT) {
        
    } else if (a == UPRIGHT) {
        
    } else if (a == UPLEFT) {
        
    } else if (a == DOWNRIGHT) {
        
    } else if (a == DOWNLEFT) {
        
    } else {
        cout << "ERROR: Invalid move" << endl;
    }
}

void GridMaps::UndoAction(MapState &s, MapAction a) {
    if (a == UP) {
        ApplyAction(s, DOWN);
    } else if (a == DOWN) {
        ApplyAction(s, UP);
    } else if (a == LEFT) {
        ApplyAction(s, RIGHT);
    } else if (a == RIGHT) {
        ApplyAction(s, LEFT);
    }
}

