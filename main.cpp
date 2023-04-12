/*-----------------------------------------------------------------------------
main.cpp

2023-03-23 - Benjamin Ocampo - Created
2023-03-23 - Benjamin Ocampo - Main program. Talks with other modules.
-----------------------------------------------------------------------------*/

/*  Get Modules */
#include "ant_movement.h"
#include "ant_map.h"


/*
    Main function. Will run the following:

    1. Initialization of paths between colony and food source.
    2. Path optimization based on "The Ant System: Optimization by a colony of 
       cooperating agents" by Dorigo et al in 1996.
    3. Run scouts that generate new paths in parallel with 2
*/
int main(void) {
  //Define variables
  int i_NumRows = 50;
  int i_NumCols = 50;
  int i_NumAnts = 20;
  int i_NumIterations = 10000;
  t_SinglePath t_ColCoords;
  t_ColCoords.push_back(t_XYPoint (5,5));
  t_SinglePath t_FoodCoords;
  t_FoodCoords.push_back(t_XYPoint (15,15));


  //Initialize classes
  ant_movement a_AM(t_FoodCoords, t_ColCoords);
  a_AM.define_num_iterations(i_NumIterations);
  a_AM.define_num_ants(i_NumAnts);
  a_AM.define_map_dims(i_NumRows, i_NumCols);

  ant_map a_AMap(i_NumRows, i_NumCols);
  std::vector<int> v_PMap = a_AMap.get_PMap();

  std::vector<int>  v_nPMap = a_AM.run_ACO(v_PMap);

  a_AMap.update_map(v_nPMap);

  //Output File
  a_AMap.output_PMap();

  return 0;
}