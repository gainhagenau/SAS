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
#include "PDB.hpp"
#include "InefficientAStar.hpp"
#include "AStar.hpp"
#include "GridMaps.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    /*struct node {
        int gCost, hCost;
        TileState s;
        TileAction parentAction;
    };
    
    typedef std::unordered_map<node,int> nodeMap;
    
    nodeMap open;    // open map
    //nodeMap::hasher fn = open.hash_function();
*/

    
    /*vector<int> pattern1;
    pattern1.push_back(0);
    pattern1.push_back(1);
    pattern1.push_back(4);
    pattern1.push_back(5);

    vector<int> pattern2;
    pattern2.push_back(0);
    pattern2.push_back(2);
    pattern2.push_back(3);
    pattern2.push_back(6);
    pattern2.push_back(7);
    
    vector<int> pattern3;
    pattern3.push_back(0);
    pattern3.push_back(8);
    pattern3.push_back(9);
    pattern3.push_back(12);
    pattern3.push_back(13);
    
    vector<int> pattern4;
    pattern4.push_back(0);
    pattern4.push_back(10);
    pattern4.push_back(11);
    pattern4.push_back(14);
    pattern4.push_back(15);
    
    vector<int> pattern5;
    pattern5.push_back(0);
    pattern5.push_back(1);
    pattern5.push_back(2);
    pattern5.push_back(3);
    pattern5.push_back(4);
    pattern5.push_back(5);
    pattern5.push_back(6);
    pattern5.push_back(7);


    vector<vector<int>> p;
    p.push_back(pattern1);
    p.push_back(pattern2);
    p.push_back(pattern3);
    p.push_back(pattern4);
    //p.push_back(pattern5);
    PDB pdb = PDB(p, true);*/
    
    //TileState t = {14, 1, 9, 6, 4, 8, 12, 5, 7, 2, 3, 0, 10, 11, 13, 15};
    TileState t = {1, 2, 3, 7, 4, 5, 6, 11, 8, 0, 9, 10, 12, 13, 14, 15};
    //TileState t = {1, 2, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    SlidingTile tile;   //sliding tile object
    STmanhattan man;
    
    //InefficientAStar<TileState, TileAction, SlidingTile, STmanhattan> a;
    InefficientAStar<TileState, TileAction, SlidingTile, STmanhattan> a;
    
    
    //IDA<TileState, TileAction, SlidingTile, STmanhattan> idast;  //ida on sliding tile
    TileState goal = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    cout << "A* on Sliding Tile Puzzle\n\n";
    for (int s = 0; s < 16; s++) {
        cout << t.state[s] << ", ";
    }
    cout << "\n";
    const clock_t begin_time = clock();
    cout << a.GetPath(tile, t, goal, man) << "\n";
    std::cout << "Time Elapsed: " << (float( clock () - begin_time ) /  CLOCKS_PER_SEC) / 60 << " minutes";
    cout << "\nNodes Expanded: " << a.GetNodesExpanded() << "\n" << endl;
    

    InefficientAStar<MapState, MapAction, GridMaps, GridMaps> a;
    MapState start, goal;
    start.x = 1;
    start.y = 121;
    goal.x = 20;
    goal.y = 121;
    GridMaps grid;
    cout << "Inneficient A* on Grid Map" << endl;
    const clock_t begin_time = clock();
    cout << a.GetPath(grid, start, goal, grid) << "\n";
    std::cout << "Time Elapsed: " << (float( clock () - begin_time ) /  CLOCKS_PER_SEC) / 60 << " minutes";
    cout << "\nNodes Expanded: " << a.GetNodesExpanded() << "\n" << endl;

    /*int instances[100][16] =
    {{14, 13, 15, 7, 11, 12, 9, 5, 6, 0, 2, 1, 4, 8, 10, 3},
        {13, 5, 4, 10, 9, 12, 8, 14, 2, 3, 7, 1, 0, 15, 11, 6},
        {14, 7, 8, 2, 13, 11, 10, 4, 9, 12, 5, 0, 3, 6, 1, 15},
        {5, 12, 10, 7, 15, 11, 14, 0, 8, 2, 1, 13, 3, 4, 9, 6},
        {4, 7, 14, 13, 10, 3, 9, 12, 11, 5, 6, 15, 1, 2, 8, 0},
        {14, 7, 1, 9, 12, 3, 6, 15, 8, 11, 2, 5, 10, 0, 4, 13},
        {2, 11, 15, 5, 13, 4, 6, 7, 12, 8, 10, 1, 9, 3, 14, 0},
        {12, 11, 15, 3, 8, 0, 4, 2, 6, 13, 9, 5, 14, 1, 10, 7},
        {3, 14, 9, 11, 5, 4, 8, 2, 13, 12, 6, 7, 10, 1, 15, 0},
        {13, 11, 8, 9, 0, 15, 7, 10, 4, 3, 6, 14, 5, 12, 2, 1},
        {5, 9, 13, 14, 6, 3, 7, 12, 10, 8, 4, 0, 15, 2, 11, 1},
        {14, 1, 9, 6, 4, 8, 12, 5, 7, 2, 3, 0, 10, 11, 13, 15},
        {3, 6, 5, 2, 10, 0, 15, 14, 1, 4, 13, 12, 9, 8, 11, 7},
        {7, 6, 8, 1, 11, 5, 14, 10, 3, 4, 9, 13, 15, 2, 0, 12},
        {13, 11, 4, 12, 1, 8, 9, 15, 6, 5, 14, 2, 7, 3, 10, 0},
        {1, 3, 2, 5, 10, 9, 15, 6, 8, 14, 13, 11, 12, 4, 7, 0},
        {15, 14, 0, 4, 11, 1, 6, 13, 7, 5, 8, 9, 3, 2, 10, 12},
        {6, 0, 14, 12, 1, 15, 9, 10, 11, 4, 7, 2, 8, 3, 5, 13},
        {7, 11, 8, 3, 14, 0, 6, 15, 1, 4, 13, 9, 5, 12, 2, 10},
        {6, 12, 11, 3, 13, 7, 9, 15, 2, 14, 8, 10, 4, 1, 5, 0},
        {12, 8, 14, 6, 11, 4, 7, 0, 5, 1, 10, 15, 3, 13, 9, 2},
        {14, 3, 9, 1, 15, 8, 4, 5, 11, 7, 10, 13, 0, 2, 12, 6},
        {10, 9, 3, 11, 0, 13, 2, 14, 5, 6, 4, 7, 8, 15, 1, 12},
        {7, 3, 14, 13, 4, 1, 10, 8, 5, 12, 9, 11, 2, 15, 6, 0},
        {11, 4, 2, 7, 1, 0, 10, 15, 6, 9, 14, 8, 3, 13, 5, 12},
        {5, 7, 3, 12, 15, 13, 14, 8, 0, 10, 9, 6, 1, 4, 2, 11},
        {14, 1, 8, 15, 2, 6, 0, 3, 9, 12, 10, 13, 4, 7, 5, 11},
        {13, 14, 6, 12, 4, 5, 1, 0, 9, 3, 10, 2, 15, 11, 8, 7},
        {9, 8, 0, 2, 15, 1, 4, 14, 3, 10, 7, 5, 11, 13, 6, 12},
        {12, 15, 2, 6, 1, 14, 4, 8, 5, 3, 7, 0, 10, 13, 9, 11},
        {12, 8, 15, 13, 1, 0, 5, 4, 6, 3, 2, 11, 9, 7, 14, 10},
        {14, 10, 9, 4, 13, 6, 5, 8, 2, 12, 7, 0, 1, 3, 11, 15},
        {14, 3, 5, 15, 11, 6, 13, 9, 0, 10, 2, 12, 4, 1, 7, 8},
        {6, 11, 7, 8, 13, 2, 5, 4, 1, 10, 3, 9, 14, 0, 12, 15},
        {1, 6, 12, 14, 3, 2, 15, 8, 4, 5, 13, 9, 0, 7, 11, 10},
        {12, 6, 0, 4, 7, 3, 15, 1, 13, 9, 8, 11, 2, 14, 5, 10},
        {8, 1, 7, 12, 11, 0, 10, 5, 9, 15, 6, 13, 14, 2, 3, 4},
        {7, 15, 8, 2, 13, 6, 3, 12, 11, 0, 4, 10, 9, 5, 1, 14},
        {9, 0, 4, 10, 1, 14, 15, 3, 12, 6, 5, 7, 11, 13, 8, 2},
        {11, 5, 1, 14, 4, 12, 10, 0, 2, 7, 13, 3, 9, 15, 6, 8},
        {8, 13, 10, 9, 11, 3, 15, 6, 0, 1, 2, 14, 12, 5, 4, 7},
        {4, 5, 7, 2, 9, 14, 12, 13, 0, 3, 6, 11, 8, 1, 15, 10},
        {11, 15, 14, 13, 1, 9, 10, 4, 3, 6, 2, 12, 7, 5, 8, 0},
        {12, 9, 0, 6, 8, 3, 5, 14, 2, 4, 11, 7, 10, 1, 15, 13},
        {3, 14, 9, 7, 12, 15, 0, 4, 1, 8, 5, 6, 11, 10, 2, 13},
        {8, 4, 6, 1, 14, 12, 2, 15, 13, 10, 9, 5, 3, 7, 0, 11},
        {6, 10, 1, 14, 15, 8, 3, 5, 13, 0, 2, 7, 4, 9, 11, 12},
        {8, 11, 4, 6, 7, 3, 10, 9, 2, 12, 15, 13, 0, 1, 5, 14},
        {10, 0, 2, 4, 5, 1, 6, 12, 11, 13, 9, 7, 15, 3, 14, 8},
        {12, 5, 13, 11, 2, 10, 0, 9, 7, 8, 4, 3, 14, 6, 15, 1},
        {10, 2, 8, 4, 15, 0, 1, 14, 11, 13, 3, 6, 9, 7, 5, 12},
        {10, 8, 0, 12, 3, 7, 6, 2, 1, 14, 4, 11, 15, 13, 9, 5},
        {14, 9, 12, 13, 15, 4, 8, 10, 0, 2, 1, 7, 3, 11, 5, 6},
        {12, 11, 0, 8, 10, 2, 13, 15, 5, 4, 7, 3, 6, 9, 14, 1},
        {13, 8, 14, 3, 9, 1, 0, 7, 15, 5, 4, 10, 12, 2, 6, 11},
        {3, 15, 2, 5, 11, 6, 4, 7, 12, 9, 1, 0, 13, 14, 10, 8},
        {5, 11, 6, 9, 4, 13, 12, 0, 8, 2, 15, 10, 1, 7, 3, 14},
        {5, 0, 15, 8, 4, 6, 1, 14, 10, 11, 3, 9, 7, 12, 2, 13},
        {15, 14, 6, 7, 10, 1, 0, 11, 12, 8, 4, 9, 2, 5, 13, 3},
        {11, 14, 13, 1, 2, 3, 12, 4, 15, 7, 9, 5, 10, 6, 8, 0},
        {6, 13, 3, 2, 11, 9, 5, 10, 1, 7, 12, 14, 8, 4, 0, 15},
        {4, 6, 12, 0, 14, 2, 9, 13, 11, 8, 3, 15, 7, 10, 1, 5},
        {8, 10, 9, 11, 14, 1, 7, 15, 13, 4, 0, 12, 6, 2, 5, 3},
        {5, 2, 14, 0, 7, 8, 6, 3, 11, 12, 13, 15, 4, 10, 9, 1},
        {7, 8, 3, 2, 10, 12, 4, 6, 11, 13, 5, 15, 0, 1, 9, 14},
        {11, 6, 14, 12, 3, 5, 1, 15, 8, 0, 10, 13, 9, 7, 4, 2},
        {7, 1, 2, 4, 8, 3, 6, 11, 10, 15, 0, 5, 14, 12, 13, 9},
        {7, 3, 1, 13, 12, 10, 5, 2, 8, 0, 6, 11, 14, 15, 4, 9},
        {6, 0, 5, 15, 1, 14, 4, 9, 2, 13, 8, 10, 11, 12, 7, 3},
        {15, 1, 3, 12, 4, 0, 6, 5, 2, 8, 14, 9, 13, 10, 7, 11},
        {5, 7, 0, 11, 12, 1, 9, 10, 15, 6, 2, 3, 8, 4, 13, 14},
        {12, 15, 11, 10, 4, 5, 14, 0, 13, 7, 1, 2, 9, 8, 3, 6},
        {6, 14, 10, 5, 15, 8, 7, 1, 3, 4, 2, 0, 12, 9, 11, 13},
        {14, 13, 4, 11, 15, 8, 6, 9, 0, 7, 3, 1, 2, 10, 12, 5},
        {14, 4, 0, 10, 6, 5, 1, 3, 9, 2, 13, 15, 12, 7, 8, 11},
        {15, 10, 8, 3, 0, 6, 9, 5, 1, 14, 13, 11, 7, 2, 12, 4},
        {0, 13, 2, 4, 12, 14, 6, 9, 15, 1, 10, 3, 11, 5, 8, 7},
        {3, 14, 13, 6, 4, 15, 8, 9, 5, 12, 10, 0, 2, 7, 1, 11},
        {0, 1, 9, 7, 11, 13, 5, 3, 14, 12, 4, 2, 8, 6, 10, 15},
        {11, 0, 15, 8, 13, 12, 3, 5, 10, 1, 4, 6, 14, 9, 7, 2},
        {13, 0, 9, 12, 11, 6, 3, 5, 15, 8, 1, 10, 4, 14, 2, 7},
        {14, 10, 2, 1, 13, 9, 8, 11, 7, 3, 6, 12, 15, 5, 4, 0},
        {12, 3, 9, 1, 4, 5, 10, 2, 6, 11, 15, 0, 14, 7, 13, 8},
        {15, 8, 10, 7, 0, 12, 14, 1, 5, 9, 6, 3, 13, 11, 4, 2},
        {4, 7, 13, 10, 1, 2, 9, 6, 12, 8, 14, 5, 3, 0, 11, 15},
        {6, 0, 5, 10, 11, 12, 9, 2, 1, 7, 4, 3, 14, 8, 13, 15},
        {9, 5, 11, 10, 13, 0, 2, 1, 8, 6, 14, 12, 4, 7, 3, 15},
        {15, 2, 12, 11, 14, 13, 9, 5, 1, 3, 8, 7, 0, 10, 6, 4},
        {11, 1, 7, 4, 10, 13, 3, 8, 9, 14, 0, 15, 6, 5, 2, 12},
        {5, 4, 7, 1, 11, 12, 14, 15, 10, 13, 8, 6, 2, 0, 9, 3},
        {9, 7, 5, 2, 14, 15, 12, 10, 11, 3, 6, 1, 8, 13, 0, 4},
        {3, 2, 7, 9, 0, 15, 12, 4, 6, 11, 5, 14, 8, 13, 10, 1},
        {13, 9, 14, 6, 12, 8, 1, 2, 3, 4, 0, 7, 5, 10, 11, 15},
        {5, 7, 11, 8, 0, 14, 9, 13, 10, 12, 3, 15, 6, 1, 4, 2},
        {4, 3, 6, 13, 7, 15, 9, 0, 10, 5, 8, 11, 2, 12, 1, 14},
        {1, 7, 15, 14, 2, 6, 4, 9, 12, 11, 13, 3, 0, 8, 5, 10},
        {9, 14, 5, 7, 8, 15, 1, 2, 10, 4, 13, 6, 12, 0, 11, 3},
        {0, 11, 3, 12, 5, 2, 1, 9, 8, 10, 14, 15, 7, 4, 13, 6},
        {7, 15, 4, 0, 10, 9, 2, 5, 12, 11, 13, 6, 1, 3, 14, 8},
        {11, 4, 0, 8, 6, 10, 5, 13, 12, 7, 14, 3, 1, 2, 9, 15}};
    
    
    TileState toSolve;
    cout << "IDA* on Sliding Tile Puzzle\n\n";
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 16; j++) {
            toSolve.state[j] = instances[i][j];
        }
        cout << "Problem " << i + 1 << " of 100\nStart State: " << endl;
        for (int s = 0; s < 16; s++) {
            cout << toSolve.state[s] << ", ";
        }
        cout << "\n";
        const clock_t begin_time = clock();
        idast.GetPath(tile, toSolve, goal, man);
        std::cout << "Time Elapsed: " << (float( clock () - begin_time ) /  CLOCKS_PER_SEC) / 60 << " minutes";
        cout << "\nNodes Expanded: " << idast.GetNodesExpanded() << "\n" << endl;

    }
    */
    /*
     0   1   2   3
     4   5   6   7
     8   9   10  11
     12  13  14  15
     */
    
    
    
     /*HOMEWORK 1
     
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
     
     HOMEWORK 1 END*/
    
    
    return 0;
}
