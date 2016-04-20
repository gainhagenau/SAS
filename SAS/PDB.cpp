//
//  PDB.cpp
//  SAS
//
//  Created by Ryan Aikman on 4/13/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#include "PDB.hpp"

//Takes a vector of vectors that will be built into pattern databases for the silding tile puzzel
PDB::PDB(vector<vector<int>> patterns){
    /*
    for (int i = 0; i < patterns.size(); i++){
        buildPDB(patterns[i]);
    }
     */
}

//constructs the pattern database array and then pushes it to the back of the db vector
void PDB::buildPDB(vector<int> pattern) {
    
    long size = factorial(16) / factorial(16 - pattern.size());
    
    int *array = new int[size]; //creates array and sets all values to -1
    for (int i = 0; i < size; i++){
        array[i] = -1;
    }
    
    //build and place the starting state of the pattern DB in the array
    TileState state = buildPatternState(pattern);
    int index = rank(state, pattern);
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
    while (!done){
        done = true;
        for (int i = 0; i < size; i++){
            if (array[i] == depth){ //expand node
                state = unrank(i, pattern); //get state
                st.GetActions(state, actions);
                for (int j = 0; j < actions.size(); j++){ //apply actions
                    st.ApplyAction(child, actions[j]);
                    index = rank(child, pattern);
                    if (array[index] == -1){
                        done = false; //not done, another node to expand at next depth
                        array[index] = depth + 1; //add node at the next depth
                    }
                }
            }
        }
        depth++;
    }
    
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
    return 0;
}


int PDB::rank(TileState state, vector<int> pattern) {
    //create permutation of the pattern
    int loc[pattern.size()];
    for (int i = 0; i < 16; i++) {
        if (state.state[i] != -1) {
            for (int j = 0; j < pattern.size(); j++) {
                if (pattern[j] == state.state[i]) {
                    loc[j] = i;
                }
            }
        }
    }
    
    //radix the permutation
    for (int i = 0; i < pattern.size(); i++) {  //compare each digit to every digit that follows it
        for (int j = (i+1); j < pattern.size(); j++) {
            if (loc[j] >= loc[i]) {   //if one of the following digits is greater than the current
                loc[j]--;  //decrement
            }
        }
    }
    
    //rank the radix notation to return an int
    int toReturn = 0;
    for (int i = 0; i < pattern.size(); i++) {  //starting at first tile and moving towards last
        toReturn += (loc[i] * factorial(i));
    }
    return toReturn;
}

TileState PDB::unrank(int rank, vector<int> pattern) {
    int nextRank;
    int digit;
    int loc[pattern.size()];
    int j = 0;
    for (long i = (pattern.size() - 1); i >= 0; i--) {    //starting at the last tile, moving to the first
        nextRank = (rank % factorial(i));
        digit = (rank / factorial(i));
        loc[j++] = digit;
        rank = nextRank;
    }
    
    //un-radix
    for (int i = 0; i < pattern.size(); i++) {  //compare each digit to every digit that follows it
        for (int j = (i+1); j < pattern.size(); j++) {
            if (loc[j] >= loc[i]) {   //if one of the following digits is greater than the current
                loc[j]++;  //increment
            }
        }
    }
    
    //un-permutate
    TileState toReturn;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < pattern.size(); j++) {  //Repopulate the tile state
            if (loc[j] == i) {  //if the index i = the value in loc add it. Else add -1
                toReturn.state[i] = loc[j];
            } else {
                toReturn.state[i] = -1;
            }
        }
    }
    
    return toReturn;
}

long PDB::factorial(long n) {
    long factorial = 1;
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

/*void PDB::unRadix(TileState &in) {  //convert an array back to regular notation
    for (int i = 0; i < 16; i++) {  //compare each digit to every digit that follows it
        for (int j = (i+1); j < 16; j++) {
            if (in.state[j] >= in.state[i]) {   //if one of the following digits is greater than the current
                in.state[j]++;  //increment
            }
        }
    }
 
 }
 
 void PDB::radix(vector<int> &in) {    //get the mixed radix form of a number
    for (int i = 0; i < in.size(); i++) {  //compare each digit to every digit that follows it
        for (int j = (i+1); j < in.size(); j++) {
            if (in[j] >= in[i]) {   //if one of the following digits is greater than the current
                in[j]--;  //decrement
            }
        }
    }
 }*/
