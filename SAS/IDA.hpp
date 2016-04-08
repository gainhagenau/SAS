//
//  IDA.hpp
//  SAS
//
//  Created by Ryan Aikman on 4/7/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef IDA_hpp
#define IDA_hpp

#include <stdio.h>

using namespace std;

template <typename state, typename action, typename environment>
class IDA {
public:
    
    /*
     bound <- f-cost(start)
     while(!solution)
        nextboud = -1
     cost_limit_dfs(bound)
     */
    /*
     cost_limited_dfs(limit, state)
        if f-cost(state) > limit
            return
        if state = goal
            for each action a in state
                apply a to state
                cost_limited_dfs
                undo a from state
     */
    IDA(){};
    ~IDA(){};
    
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal) {
        
    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return GetNodesExpanded;
    }
    
    void cost_limited_dfs(int limit, TileState &s) {
        
    }
private:
    int nodesExpanded;
};

#endif /* IDA_hpp */
