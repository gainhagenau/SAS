/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/
//  NEnvironment.hpp
//  Homework1
//


#ifndef NEnvironment_hpp
#define NEnvironment_hpp

#include <stdio.h>
#include <vector>

using namespace std;

struct NState {
    int num;
    
    bool operator==(const NState &s) const{
        return (s.num == num);
    }
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
    
private:
    int branching;
    
};

#endif /* NEnvironment_hpp */
