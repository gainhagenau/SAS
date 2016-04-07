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
    IDA(){};
    ~IDA(){};
    // GetPath returns if the goal was found
    bool GetPath(environment &e, state &start, state &goal) {
        
    }
    
    // Returns the total nodes expanded by the last GetPath call.
    uint64_t GetNodesExpanded() {
        return GetNodesExpanded;
    }
private:
    int nodesExpanded;
};

#endif /* IDA_hpp */
