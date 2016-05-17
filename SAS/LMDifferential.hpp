//
//  LMDifferential.hpp
//  SAS
//
//  Created by Ryan Aikman on 5/16/16.
//  Copyright © 2016 Gain Hagenau. All rights reserved.
//

#ifndef LMDifferential_hpp
#define LMDifferential_hpp

#include <stdio.h>
#include "GridMaps.hpp"

#endif /* LMDifferential_hpp */

class LMDifferential {
public:
    LMDifferential(int f) {
        flag = f;
    }
    
    int GetHeuristic(MapState state);
private:
    int flag;
};
