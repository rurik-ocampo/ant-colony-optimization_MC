/*-----------------------------------------------------------------------------
ant_map.h

2023-03-29 - Benjamin Ocampo - Created
2023-03-29 - Benjamin Ocampo - Defines and updates map


Hex Grid defined as

   a       b

c      o       d

   e       f

where a = (-1, +1)
      b = (+1, +1)
      c = (-2, +0)
      d = (+2, +0)
      e = (-1, -1)
      f = (+1, -1)
-----------------------------------------------------------------------------*/


#ifndef MAP_H
#define MAP_H


//  Get Standard libraries 
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>


// Defining coordinates that store coordinates of each scout
typedef std::pair<int, int> t_XYPoint;
typedef std::vector<t_XYPoint> t_SinglePath;
typedef std::vector<t_SinglePath> t_MultiplePaths;


/*-----------------------------------------------------------------------------
class map


The class does the following:

1. Initialize map
2. Updates map based on pheromones
-----------------------------------------------------------------------------*/
class ant_map{
  public:
    // Class Constructor
    ant_map(int i_NumRows, int i_NumCols);

    // Define cartesian grid
    void define_maps(int i_NumRows, int i_NumCols);

    // Add Colony coordinates
    void add_colonies(t_SinglePath t_Path);

    // Add Food Sources
    void add_food(t_SinglePath t_Path);
    
    // Add Scout paths
    void add_scout_paths(t_SinglePath t_Path);

    // Update map
    void update_map(std::vector<int> v_PMap);

    //Get PMap
    std::vector<int> get_PMap(){
      return m_PMap;
    }

    //Output PMap to text file
    void output_PMap();
    
  private:
    //Number of rows and cols
    int m_NumRows;
    int m_NumCols;

    //Define pheromones, colony, and food maps
    std::vector<int> m_PMap;
    std::vector<int> m_FMap;
    std::vector<int> m_CMap;
}; // class map

#endif //MAP_H