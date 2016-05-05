//
//  GridMaps.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/4/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "GridMaps.hpp"

GridMaps::GridMaps(int gX, int gY) {
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
    if (map[index - 120] == true) {
        actions.push_back(NORTH);
    }
    //DOWN
    if (map[index + 120] == true) {
        actions.push_back(SOUTH);
    }
    //LEFT
    if (map[index - 1] == true) {
        actions.push_back(WEST);
    }
    //RIGHT
    if (map[index + 1] == true) {
        actions.push_back(EAST);
    }
    //UPRIGHT
    if ((find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end())) {
        actions.push_back(NORTHEAST);
    }
    //UPLEFT
    if ((find(actions.begin(), actions.end(), WEST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end())) {
        actions.push_back(NORTHWEST);
    }
    //DOWNRIGHT
    if ((find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), SOUTH) != actions.end())) {
        actions.push_back(SOUTHEAST);
    }
    //DOWNLEFT
    if ((find(actions.begin(), actions.end(), SOUTH) != actions.end()) && (find(actions.begin(), actions.end(), WEST) != actions.end())) {
        actions.push_back(SOUTHWEST);
    }
}

void GridMaps::ApplyAction(MapState &s, MapAction a) {
    if (a == NORTH) {
        s.y++;
        cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTH) {
        s.y--;
        cout << s.x << ", " << s.y << endl;
    } else if (a == WEST) {
        s.x--;
        cout << s.x << ", " << s.y << endl;
    } else if (a == EAST) {
        s.x++;
        cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHEAST) {
        s.y++;
        s.x++;
        cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHWEST) {
        s.y++;
        s.x--;
        cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHEAST) {
        s.y--;
        s.x++;
        cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHWEST) {
        s.y--;
        s.x--;
        cout << s.x << ", " << s.y << endl;
    } else {
        cout << "ERROR: Invalid move" << endl;
    }
}

void GridMaps::UndoAction(MapState &s, MapAction a) {
    if (a == NORTH) {
        ApplyAction(s, SOUTH);
    } else if (a == SOUTH) {
        ApplyAction(s, NORTH);
    } else if (a == WEST) {
        ApplyAction(s, EAST);
    } else if (a == EAST) {
        ApplyAction(s, WEST);
    } else if (a == NORTHEAST) {
        ApplyAction(s, SOUTHEAST);
    } else if (a == NORTHWEST) {
        ApplyAction(s, SOUTHEAST);
    } else if (a == SOUTHEAST) {
        ApplyAction(s, NORTHWEST);
    } else if (a == SOUTHWEST) {
        ApplyAction(s, NORTHEAST);
    }
}

MapAction GridMaps::InvertAction(MapAction a) {
    switch (a) // invert action
    {
        case NORTH: return SOUTH; break;
        case SOUTH: return NORTH; break;
        case WEST: return EAST; break;
        case EAST: return WEST; break;
        case NORTHEAST: return SOUTHWEST; break;
        case NORTHWEST: return SOUTHEAST; break;
        case SOUTHWEST: return NORTHEAST; break;
        case SOUTHEAST: return NORTHWEST; break;
        case NA: return NA; break;
    }
}


