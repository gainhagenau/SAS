/**
 Single Agent Search
 University of Denver
 4/2016
 Authored by Gain Hagenau and Ryan Aikman
 **/

//  main.cpp


#include <iostream>
#include <vector>
#include "GridEnvironment.hpp"
#include "NEnvironment.hpp"
#include "BFS.hpp"
#include "DFID.hpp"
#include "IDA.hpp"
#include "SlidingTile.hpp"
#include "STmanhattan.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    
    SlidingTile tile;   //sliding tile object
    STmanhattan h;
    IDA<TileState, TileAction, SlidingTile, STmanhattan> idast;  //ida on sliding tile
    TileState start = {14, 1, 9, 6, 4, 8, 12, 5, 7, 2, 3, 0, 10, 11, 13, 15};
    TileState goal = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    /*
    14 1  9  6
    4  8  12 5
    7  2  3  0
    10 11 13 15
    
    up = 0
    down = 1
    left = 2
    right = 3
     */
    cout << "IDA* on Sliding Tile Puzzle\nStart State: ";
    for (int i = 0; i < 16; i++) {
        cout << start.state[i] << ", ";
    }
    cout << "\n";
    bool found = idast.GetPath(tile, start, goal, h);
    cout << "\nFound: " << found << "\nEnd State:   ";
    for (int i = 0; i < 16; i++) {
        cout << start.state[i] << ", ";
    }
    cout << "\n\nNodes Expanded: " << idast.GetNodesExpanded() << endl;
    
    /*
     0   1   2   3
     4   5   6   7
     8   9   10  11
     12  13  14  15
     */
    
    
    
    /* HOMEWORK 1
     
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
     
     HOMEWORK 1 END */
    
    
    return 0;
}
