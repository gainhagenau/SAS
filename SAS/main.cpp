//
//  main.cpp
//  Homework1
//
//  Created by Gain Hagenau and Ryan Aikman on 3/28/16.
//  This is on GitHub

#include <iostream>
#include <vector>
#include "GridEnvironment.hpp"
#include "NEnvironment.hpp"
#include "BFS.hpp"
#include "DFID.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    //Test
    //Creating Grid based environment
    GridEnvironment grid(10);
    
    //Creating N-ary environment
    NEnvironment nary(2);
    
    //Creating BFS objects
    BFS<GridState, GridAction, GridEnvironment> bfsg;
    BFS<NState, int, NEnvironment> bfsn;
    
    //Creating IDFS objects
    DFID<GridState, GridAction, GridEnvironment> dfidg;
    DFID<NState, int, NEnvironment> dfidn;
    
    
    
    //BFS on Grid based environment
    GridState start; start.x = 0; start.y = 0;
    GridState goal; goal.x = 8; goal.y = 9;
    
    bool found = bfsg.GetPath(grid, start, goal);
    cout << "BFS on Grid based environment";
    cout << "\n";
    cout << found;
    cout << "\n";
    cout << bfsg.GetNodesExpanded();
    cout << "\n";
    cout << "\n";
    
    //BFS on N-ary environment
    NState start_n; start_n.num = 0;
    NState goal_n; goal_n.num = 120;
    
    found = bfsn.GetPath(nary, start_n, goal_n);
    cout << "BFS on N-ary environment";
    cout << "\n";
    cout << found;
    cout << "\n";
    cout << bfsn.GetNodesExpanded();
    cout << "\n";
    cout << "\n";
    
    //IDFD on Grid based environment
    found = dfidg.GetPath(grid, start, goal);
    cout << "IDFD on Grid based environment";
    cout << "\n";
    cout << found;
    cout << "\n";
    cout << dfidg.GetNodesExpanded();
    cout << "\n";
    cout << "\n";
    
    //IDFD on N-ary environment
    found = dfidn.GetPath(nary, start_n, goal_n);
    cout << "IDFD on N-ary environment";
    cout << "\n";
    cout << found;
    cout << "\n";
    cout << dfidn.GetNodesExpanded();
    cout << "\n";
    cout << "\n";
    
    
    
    return 0;
}
