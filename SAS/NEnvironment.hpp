//
//  NEnvironment.hpp
//  Homework1
//
//  Created by Gain Hagenau and Ryan Aikman on 3/29/16.
//

#ifndef NEnvironment_hpp
#define NEnvironment_hpp

#include <stdio.h>
#include <vector>

using namespace std;

struct NState {
    int num;
};

class NEnvironment {
public:
    
    NEnvironment(int b){branching = b;};
    
    ~NEnvironment(){};
    
    //Return avalible actions from that state
    void GetActions(NState &s, vector<int> &actions);
    
    //apply an action to a state
    void ApplyAction(NState &s, int a);
    
    //undo an action on a state
    void UndoAction(NState &s, int a);
    
    //Returns true if the states are the same
    bool CompareStates(NState &a, NState &b);
    
private:
    int branching;
    
};

#endif /* NEnvironment_hpp */
