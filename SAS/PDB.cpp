//
//  PDB.cpp
//  SAS
//
//  Created by Ryan Aikman on 4/13/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "PDB.hpp"

//Takes a vector of vectors that will be built into pattern databases for the silding tile puzzel
// m = include the manhattan distance in the calculation of heuristic or not
PDB::PDB(vector<vector<int>> p, bool m){
    patterns = p;
    manhattan = m;

    for (int i = 0; i < patterns.size(); i++){
        buildPDB(patterns[i]);
    }
}

PDB::~PDB(){
    for (int i = 0; i < db.size(); i++){
        delete[] db[i];
    }
}

//constructs the pattern database array and then pushes it to the back of the db vector
void PDB::buildPDB(vector<int> pattern) {
    
    cout << "Building Pattern DB for pattern: ";
    for (int i = 0; i < pattern.size(); i++){
        cout << pattern[i] << "  ";
    }
    cout << endl;
    
    long size = factorial(16) / factorial(16 - pattern.size());
    
    int *array = new int[size]; //creates array and sets all values to -1
    for (long long i = 0; i < size; i++){
        array[i] = -1;
    }
    
    //build and place the starting state of the pattern DB in the array
    TileState state = buildPatternState(pattern);
    long index = rank(state, pattern);
    array[index] = 0;
    
    /*
     Does a BFS of the state space. The open states will be states with values equal to the current depth.
     The closed list contains all states with depths between 0 and the current depth. Unseen states will
     have a reserved depth of -1.
     */
    bool done = false;
    int depth = 0;
    vector<TileAction> actions;
    TileState child;
    SlidingTile st;
    long total = 1;
    while (!done){
        done = true;
        int n = 0;
        for (long i = 0; i < size; i++){
            if (array[i] == depth){ //expand node
                state = unrank(i, pattern); //get state
                st.GetActions(state, actions);
                for (int j = 0; j < actions.size(); j++){ //apply actions
                    child = state;
                    st.ApplyAction(child, actions[j]);
                    index = rank(child, pattern);
                    if (array[index] == -1){
                        done = false; //not done, another node to expand at next depth
                        array[index] = depth + 1; //add node at the next depth
                        n++;
                    }
                }
            }
        }
        total += n;
        //cout << "Depth: " << depth << "   New: " << n << "     Completed: " << total << " of " << size << endl;
        depth++;
    }
    
    //cout << "\n\n\n";
    
    //add the populated pattern DB to the vector of DBs
    db.push_back(array);
}

//builds a starting state for a pattern database
//blank tiles will be represented as -1
TileState PDB::buildPatternState(vector<int> pattern){
    TileState ts;
    for (int i = 0; i < 16; i++){
        if (std::find(pattern.begin(), pattern.end(), i) != pattern.end()){
            ts.state[i] = i;
        }
        else{
            ts.state[i] = -1;
        }
    }
    return ts;
}

//gets the heuristic for the
int PDB::GetHeuristic(TileState state) {
    int heuristic = 0;
    for (int i = 0; i < db.size(); i++){
        long r = rank(state, patterns[i]);
        if ((db[i])[r] > heuristic){
            heuristic = (db[i])[r];
        }
    }
    if (manhattan){
        int mh = man.GetHeuristic(state);
        if (mh > heuristic){
            heuristic = mh;
        }
    }
    return heuristic;
}



long PDB::rank(TileState s, vector<int> pattern) {
    vector<int> locations(pattern.size());  //hold the locations of tiles to be ranked
    
    // load an array with the locations of the tiles in the pattern
    for (int i = 0; i < 16; i++) {
        if (s.state[i] != -1) {
            for (int j = 0; j < pattern.size(); j++) {
                if (pattern[j] == s.state[i]) {
                    locations[j] = i;
                }
            }
        }
    }
    
    long long toReturn = 0; //ranked number that will get returned
    int numLeft = 16;   //top of the fraction when calculating factorial
    int possibilities = 16 - (int)pattern.size();   //bottom of the fraction when calculating factorial
    
    //compute lexicographical ranking of locations of pattern tiles
    for (int i = 0; i < pattern.size(); i++) {
        toReturn += locations[i] * (factorial(numLeft-1)/factorial(possibilities));
        numLeft--;
        // decrement the values that are less than the current val
        for (int j = i; j < pattern.size(); j++) {
            if (locations[j] > locations[i]) {
                locations[j]--;
            }
        }
    }
    
    return toReturn;
}

TileState PDB::unrank(long long rank, vector<int> pattern) {
    vector<int> digit(pattern.size());
    
    // unrank locations of the pattern tiles
    int numLeft = 17 - (int)pattern.size();
    
    for (int i = (int)pattern.size() - 1; i >= 0; i--) {    //starting at last tile, move forward
        digit[i] = rank % numLeft;
        rank /= numLeft;
        numLeft++;
        for (int j = i+1; j < pattern.size(); j++) {    //if farther digit >, increment
            if (digit[j] >= digit[i]) {
                digit[j]++;
            }
        }
    }
    
    TileState toReturn; // return puzzle
    //load return puzzle with all -1 (stars)
    for (int i = 0; i < 16; i++) {
        toReturn.state[i] = -1;
    }
    //load the values in return that were in the pattern
    for (int i = 0; i < pattern.size(); i++) {
        toReturn.state[digit[i]] = pattern[i];
    }
    return toReturn;
}

long long PDB::factorial(long n) {
    long long factorial = 1;
    if (n <= 16 ) {
        switch (n) {    //store the first 16 for quick reference
            case 0:
                return 1;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 6;
            case 4:
                return 24;
            case 5:
                return 120;
            case 6:
                return 720;
            case 7:
                return 5040;
            case 8:
                return 40320;
            case 9:
                return 362880;
            case 10:
                return 3628800;
            case 11:
                return 39916800;
            case 12:
                return 479001600;
            case 13:
                return 6227020800;
            case 14:
                return 87178291200;
            case 15:
                return 1307674368000;
            case 16:
                return 20922789890000;
        }
    } else {    //if not within the stored values, calculate
        factorial = 1;
        while (n != 0) {    //take n, multiply by what is there and decrement n until it = 0
            factorial *= n--;
        }
    }
    return factorial;
}