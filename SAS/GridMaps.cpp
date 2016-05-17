//
//  GridMaps.cpp
//  SAS
//
//  Created by Ryan Aikman on 5/4/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "GridMaps.hpp"

//lak303d: 194(h) x 194(w)
//orz301s: 180(h) x 120(w)

GridMaps::GridMaps(MapState g) {
    goal.x = g.x;
    goal.y = g.y;
    ifstream file;
    file.open("/Users/Ryan/Documents/Junior/Spring/Single Agent Search/GitHub/SAS/SAS/orz301d.map", ios::in);
    
    // lak303d map
    //mapW = mapH = 194;
    
    // orz301s map
    mapW = 120;
    mapH = 180;
    
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

int GridMaps::getIndex(int x, int y) {
    int index = x + (y * mapW);
    return index;
}

MapState GridMaps::getMapState(int index) {
    int x;
    int y;
    MapState toReturn;
    
    for (int i = 0; i < index; i++) {
        if (i == mapW) {
            y++;
            x = 0;
        } else {
            x++;
        }
    }
    toReturn.x = x;
    toReturn.y = y;
    return toReturn;
}

int GridMaps::GetHeuristic(MapState m) {
    // x = x distance to goal
    // y = y distance to goal
    
    int x = abs(goal.x - m.x);
    int y = abs(goal.y - m.y);
    return (max(x, y) + (sqrt(2)-1)*min(x, y));
    
}

void GridMaps::GetActions(MapState &nodeID, vector<MapAction> &actions) {
    int index = getIndex(nodeID.x, nodeID.y);
    actions.clear();
    
    //UP
    if (map[index - mapW] == true) {
        actions.push_back(NORTH);
    }
    //DOWN
    if (map[index + mapW] == true) {
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
    if ((find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end()) && map[index - (mapW - 1)] == true) {
        actions.push_back(NORTHEAST);
    }
    //UPLEFT
    if ((find(actions.begin(), actions.end(), WEST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end()) && map[index - (mapW + 1)] == true) {
        actions.push_back(NORTHWEST);
    }
    //DOWNRIGHT
    if ((find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), SOUTH) != actions.end()) && map[index + (mapW + 1)] == true) {
        actions.push_back(SOUTHEAST);
    }
    //DOWNLEFT
    if ((find(actions.begin(), actions.end(), SOUTH) != actions.end()) && (find(actions.begin(), actions.end(), WEST) != actions.end()) && map[index + (mapW - 1)] == true) {
        actions.push_back(SOUTHWEST);
    }
}

void GridMaps::ApplyAction(MapState &s, MapAction a) {
    if (a == NORTH) {
        s.y++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTH) {
        s.y--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == WEST) {
        s.x--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == EAST) {
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHEAST) {
        s.y++;
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHWEST) {
        s.y++;
        s.x--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHEAST) {
        s.y--;
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHWEST) {
        s.y--;
        s.x--;
        //cout << s.x << ", " << s.y << endl;
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
        ApplyAction(s, SOUTHWEST);
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
    }
}

string GridMaps::getString(MapState &m){
    string str;
    str += m.x;
    str += m.y;
    return str;
}

bool GridMaps::isValid(int x, int y) {
    if (map[getIndex(x, y)]) {
        return true;
    }
    return false;
}

MapState GridMaps::getRandomState() {
    int randomX, randomY;
    MapState toReturn;
    
    randomX = rand() % mapW;
    randomY = rand() % mapH;
    
    while(!isValid(randomX, randomY)) {
        randomX = rand() % mapW;
        randomY = rand() % mapH;
    }
    toReturn.x = randomX;
    toReturn.y = randomY;
    return toReturn;
}

int GridMaps::getSize(){
    return map.size();
}