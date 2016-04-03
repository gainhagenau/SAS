//
//  GridEnvironment.hpp
//  Homework1
//
//  Created by Gain Hagenau and Ryan Aikman on 3/28/16.
//

#ifndef GridEnvironment_hpp
#define GridEnvironment_hpp


#include <stdio.h>
#include <vector>

using namespace std;

//represents a single grid state with an x and y coordinate
struct GridState{
    int x;
    int y;
};

enum GridAction {up, right};

class GridEnvironment {
public:
    
    //constructor takes the size of the grid, creating a square grid environment
    GridEnvironment(int s);
    
    ~GridEnvironment(){};
    
    //This function takes a state and populates the actions vector with the possible actions from that state
    void GetActions(GridState &nodeID, vector<GridAction> &actions);
    
    //This function takes a state and applies an action to it that is also passed; changing the state to its new form
    void ApplyAction(GridState &s, GridAction a);
    
    //This function un-does an action on a state
    void UndoAction(GridState &s, GridAction a);
    
    //Returns true if the states are the same
    bool CompareStates(GridState &a, GridState &b);
    
private:
    int size; //size of grid
    
};

#endif /* GridEnvironment_hpp */
