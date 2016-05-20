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

GridMaps::GridMaps(MapState g, string mapfile, int w, int h) {
    goal.x = g.x;
    goal.y = g.y;
    ifstream file;
    file.open(mapfile, ios::in);
    
    mapW = w;
    mapH = h; //194
    
    char c;
    while (!file.eof()) {
        file.get(c);
        if (c == '.' && c != '\n') {
            map.push_back(true);
        } else if (c != '\n') {
            map.push_back(false);
        }
    }
    if (map.size() != mapW * mapH){
        cout << "ERROR: something when wrong reading in the map." << endl;
        cout << "Map size: " << map.size() << " should be: " << mapW * mapH << endl;
    }
}

int GridMaps::getIndex(int x, int y) {
    int index = x + (y * mapW);
    return index;
}

MapState GridMaps::getMapState(int index) {
    MapState toReturn;
    toReturn.x = index % mapW;
    toReturn.y = index / mapW;
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
    if (getMapState(index).y > 0 && map[index - mapW] == true) {
        actions.push_back(NORTH);
    }
    //DOWN
    if (getMapState(index).y < mapH - 1 && map[index + mapW] == true) {
        actions.push_back(SOUTH);
    }
    //LEFT
    if (getMapState(index).x > 0 && map[index - 1] == true) {
        actions.push_back(WEST);
    }
    //RIGHT
    if (getMapState(index).x < mapW - 1 && map[index + 1] == true) {
        actions.push_back(EAST);
    }
    //UPRIGHT
    if (getMapState(index).y > 0 && getMapState(index).x < mapW - 1 && (find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end()) && map[index - (mapW - 1)] == true) {
        actions.push_back(NORTHEAST);
    }
    //UPLEFT
    if (getMapState(index).y > 0 && getMapState(index).x > 0 &&(find(actions.begin(), actions.end(), WEST) != actions.end()) && (find(actions.begin(), actions.end(), NORTH) != actions.end()) && map[index - (mapW + 1)] == true) {
        actions.push_back(NORTHWEST);
    }
    //DOWNRIGHT
    if (getMapState(index).y < mapH - 1 && getMapState(index).x < mapW - 1 && (find(actions.begin(), actions.end(), EAST) != actions.end()) && (find(actions.begin(), actions.end(), SOUTH) != actions.end()) && map[index + (mapW + 1)] == true) {
        actions.push_back(SOUTHEAST);
    }
    //DOWNLEFT
    if (getMapState(index).y < mapH - 1 && getMapState(index).x > 0 && (find(actions.begin(), actions.end(), SOUTH) != actions.end()) && (find(actions.begin(), actions.end(), WEST) != actions.end()) && map[index + (mapW - 1)] == true) {
        actions.push_back(SOUTHWEST);
    }
}

void GridMaps::ApplyAction(MapState &s, MapAction a) {
    if (a == NORTH) {
        s.y--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTH) {
        s.y++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == WEST) {
        s.x--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == EAST) {
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHEAST) {
        s.y--;
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == NORTHWEST) {
        s.y--;
        s.x--;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHEAST) {
        s.y++;
        s.x++;
        //cout << s.x << ", " << s.y << endl;
    } else if (a == SOUTHWEST) {
        s.y++;
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

vector<MapState> GridMaps::getRandomState(int num) {
    int randomX = 0;
    int randomY = 0;
    vector<MapState> toReturn;
    MapState temp;
    srand (7);
    for (int i = 0; i < num; i++) {
        randomX = rand() % mapW;
        randomY = rand() % mapH;
        while(!isValid(randomX, randomY)) {
            randomX = rand() % mapW;
            randomY = rand() % mapH;
        } //at this point the values should be both random and valid
        temp.x = randomX;
        temp.y = randomY;
        if (!(find(toReturn.begin(), toReturn.end(), temp) != toReturn.end())) {
            toReturn.push_back(temp);
        } else {
            i--;
        }
        
    }
    return toReturn;
}

int GridMaps::getSize(){
    return (int)map.size();
}

MapState GridMaps::getGoal(){
    return goal;
}