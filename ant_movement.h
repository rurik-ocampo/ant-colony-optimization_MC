/*-----------------------------------------------------------------------------
ant_movement.h

2023-03-23 - Benjamin Ocampo - Created
2023-03-23 - Benjamin Ocampo - Defines the ant scout path via random walk using
                               a hex grid


Calculate the next point for ant. Grid is square based:

Hex Grid defined as

-----------------> +
|
|
|
|
|
V
+

a     b     c

d     o     e

f     g     h


where a = (-1, -1)
      b = (-1, +0)
      c = (-1, +1)
      d = (+0, -1)
      o = (+0, +0) ==> Not included in random walk
      e = (+0, +1)
      f = (+1, -1)
      g = (+1, +0)
      h = (+1, +1)
-----------------------------------------------------------------------------*/


#ifndef AM_H
#define AM_H


//  Get Standard libraries 
#include <iostream>
#include <vector>
#include <random>


// Defining coordinates that store coordinates of each scout
typedef std::pair<int, int> t_XYPoint;
typedef std::vector<t_XYPoint> t_SinglePath;
typedef std::vector<t_SinglePath> t_MultiplePaths;


/*-----------------------------------------------------------------------------
class ant_movement


The class does the following:

1. Initialize paths between colony and food.
2. 
-----------------------------------------------------------------------------*/
class ant_movement{
    public:
    //class constructor
    ant_movement(t_SinglePath t_F, t_SinglePath t_C);

    //Change number of initial paths
    void define_num_initial_paths(int i_NumInitialPaths);

    //Get probability roll
    int roll_dice();

    //Calculate and define inital paths
    void run_paths_initialization();

    //Get Scout paths
    t_SinglePath get_scout_initpaths(){
      return m_ScoutVisits;
    }

    //Change num of ants
    void define_num_ants(int i_NumAnts);

    //Change num of iterations
    void define_num_iterations(int i_NumIt);

    //Run ACO
    std::vector<int> run_ACO(std::vector<int> t_PMap);

    //Define map dim
    void define_map_dims(int i_NumRows, int i_NumCols);

  private:
    // Number of scouts that runs in parallel with path optimization
    int m_NumScouts = 2;

    // Number of Initial Paths
    int m_NumInitialPaths = 10;

    // Stores scout coordinates travelled
    t_SinglePath m_ScoutVisits;

    // Stores paths between colony and food
    t_MultiplePaths m_Colony2FoodPaths;

    // Scout random num gen
    std::random_device m_Eng;
    std::mt19937 m_Gen;

    // Defines coordinates based on hex roll
    t_SinglePath m_Roll2Node;

    // Coordinates for colony and food.
    t_SinglePath m_FoodCoords;
    t_SinglePath m_ColonyCoords;

    //Number of rows and cols on map
    int m_NumRows;
    int m_NumCols;

    //Number of ants
    int m_NumAnts;

    //Number of iterations
    int m_NumIterations;

    //Constant roll amount
    float f_Amount = 1000000.0;
}; //class ant_movement


#endif //AM_H