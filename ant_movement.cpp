/*-----------------------------------------------------------------------------
ant_movement.cpp

2023-03-23 - Benjamin Ocampo - Created
2023-03-23 - Benjamin Ocampo - Defines the ant scout path via random walk using
                               a hex grid
-----------------------------------------------------------------------------*/


#include "ant_movement.h"

/*-----------------------------------------------------------------------------
ant_movement::ant_movement(t_SinglePath t_F, t_SinglePath t_C) 

Class Constructor
-----------------------------------------------------------------------------*/
ant_movement::ant_movement(t_SinglePath t_F, t_SinglePath t_C) : m_Gen(m_Eng()){

  //Set up roll 2 node coordinates
  m_Roll2Node.push_back(std::make_pair(-1, -1));
  m_Roll2Node.push_back(std::make_pair(-1,  0));
  m_Roll2Node.push_back(std::make_pair(-1,  1));
  m_Roll2Node.push_back(std::make_pair( 0, -1));
  m_Roll2Node.push_back(std::make_pair( 0,  1));
  m_Roll2Node.push_back(std::make_pair( 1, -1));
  m_Roll2Node.push_back(std::make_pair( 1,  0));
  m_Roll2Node.push_back(std::make_pair( 1,  1));

  //Assign coords
  m_FoodCoords = t_F;
  m_ColonyCoords = t_C;
}// ant_movement::ant_movement(t_SinglePath t_F, t_SinglePath t_C) 


/*-----------------------------------------------------------------------------
void ant_movement::define_num_initial_paths(int i_NumInitialPaths)

Change number of initial paths
-----------------------------------------------------------------------------*/
void ant_movement::define_num_initial_paths(int i_NumInitialPaths){
  m_NumInitialPaths = i_NumInitialPaths;
}// void ant_movement::define_num_initial_paths(int i_NumInitialPaths)


/*-----------------------------------------------------------------------------
int ant_movement::roll_dice()

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
int ant_movement::roll_dice(){
  // Roll a number between 0 and 999 using uniform dist
  return std::uniform_int_distribution<int>{0, (int)f_Amount-1}(m_Eng);
}// int ant_movement::roll_dice()



/*-----------------------------------------------------------------------------
void ant_movement::run_paths_initialization()

Initializes paths based on user defined number
-----------------------------------------------------------------------------*/
void ant_movement::run_paths_initialization(){
  //Run loop until number of scout paths are established
  int i_NumPaths = 0;
  while(i_NumPaths < m_NumInitialPaths){
    t_SinglePath t_ScoutPaths;
    //Choose between colony points
    int i_Roll = roll_dice();
    t_XYPoint t_Food;
    t_XYPoint t_Source;
    float f_CWeights = f_Amount/(1.0*m_ColonyCoords.size());
    for(int i = 1; i <= (int) m_ColonyCoords.size(); i++){
      if(i_Roll <= (int) f_CWeights*i){
        t_ScoutPaths.push_back(m_ColonyCoords.at(i-1));
        t_Source = m_ColonyCoords.at(i-1);
        break;
      } // if
    } // for
    //Choose between food points
    i_Roll = roll_dice();
    f_CWeights = f_Amount/(1.0*m_FoodCoords.size());
    for(int i = 1; i <= (int) m_FoodCoords.size(); i++){
      if(i_Roll <= (int) f_CWeights*i){
        t_Food = m_FoodCoords.at(i-1);
        break;
      } // if
    } // for
    //Create paths
    while(t_ScoutPaths.back() != t_Food){
      //Possible directions
      t_SinglePath t_PossiblyXY;
      //Get direction from source to food
      t_XYPoint t_Direction; 
      t_Direction.first = t_Food.first - t_Source.first;
      t_Direction.second = t_Food.second - t_Source.second;

      if(t_Direction.first >= 0 && t_Direction.second >= 0){
        for(int i = 0; i < (int) m_Roll2Node.size(); i++){
          if(m_Roll2Node.at(i).first >= 0 && m_Roll2Node.at(i).second >= 0){
            t_PossiblyXY.push_back(m_Roll2Node.at(i));
          } // if
        } // for
      } // if
      else if(t_Direction.first >= 0 && t_Direction.second <= 0){
        for(int i = 0; i < (int) m_Roll2Node.size(); i++){
          if(m_Roll2Node.at(i).first >= 0 && m_Roll2Node.at(i).second <= 0){
            t_PossiblyXY.push_back(m_Roll2Node.at(i));
          } // if
        } // for
      } // else if
      else if(t_Direction.first <= 0 && t_Direction.second >= 0){
        for(int i = 0; i < (int) m_Roll2Node.size(); i++){
          if(m_Roll2Node.at(i).first <= 0 && m_Roll2Node.at(i).second >= 0){
            t_PossiblyXY.push_back(m_Roll2Node.at(i));
          } // if
        } // for
      } // else if
      else{
        for(int i = 0; i < (int) m_Roll2Node.size(); i++){
          if(m_Roll2Node.at(i).first <= 0 && m_Roll2Node.at(i).second <= 0){
            t_PossiblyXY.push_back(m_Roll2Node.at(i));
          } // if
        } // for
      } // else

      //Decide on the path
      i_Roll = roll_dice();
      f_CWeights = f_Amount/(1.0*t_PossiblyXY.size());
      for(int i = 1; i <= (int) t_PossiblyXY.size(); i++){
        if(i_Roll <= (int) f_CWeights*i){
          t_XYPoint t_New;
          t_New.first = t_PossiblyXY.at(i-1).first + t_Source.first;
          t_New.second = t_PossiblyXY.at(i-1).second + t_Source.second;
          t_ScoutPaths.push_back(t_New);
          t_Source = t_New;
          break;
        } // if
      } // for
    } // while
    
    for(int i = 0; i < (int) t_ScoutPaths.size(); i++){
      m_ScoutVisits.push_back(t_ScoutPaths.at(i));
    }
    i_NumPaths++;
  } // while
} //void ant_movement::run_paths_initialization()


/*-----------------------------------------------------------------------------
void ant_movement::define_num_ants(int i_NumAnts)

Change number of initial paths
-----------------------------------------------------------------------------*/
void ant_movement::define_num_ants(int i_NumAnts){
  m_NumAnts = i_NumAnts;
}// void ant_movement::define_num_ants(int i_NumAnts)


/*-----------------------------------------------------------------------------
void ant_movement::define_num_iterations(int i_NumIt)

Change number of initial paths
-----------------------------------------------------------------------------*/
void ant_movement::define_num_iterations(int i_NumIt){
  m_NumIterations = i_NumIt;
}// void ant_movement::define_num_iterations(int i_NumIt)


/*-----------------------------------------------------------------------------
std::vector<int> ant_movement::run_ACO()

Run ACO based on number of iterations and number of ants
-----------------------------------------------------------------------------*/
std::vector<int> ant_movement::run_ACO(std::vector<int> t_PMap){
  // Define Vars
  t_SinglePath t_AntPaths;
  t_SinglePath t_Foods;
  t_SinglePath t_Sources;
  t_SinglePath t_Targets;

  //Choose between colony points
  int i_Roll = roll_dice();
  float f_CWeights = f_Amount/(1.0*m_ColonyCoords.size());
  for(int h = 0; h < m_NumAnts; h++){
    for(int i = 1; i <= (int) m_ColonyCoords.size(); i++){
      if(i_Roll <= (int) f_CWeights*i){
        t_AntPaths.push_back(m_ColonyCoords.at(i-1));
        t_Sources.push_back(m_ColonyCoords.at(i-1));
        break;
      } // for
    } // if
  } // for

  //Choose between food points
  i_Roll = roll_dice();
  f_CWeights = f_Amount/(1.0*m_FoodCoords.size());
  for(int h = 0; h < m_NumAnts; h++){
    for(int i = 1; i <= (int) m_FoodCoords.size(); i++){
      if(i_Roll <= (int) f_CWeights*i){
        t_Foods.push_back(m_FoodCoords.at(i-1));
        t_Targets.push_back(m_FoodCoords.at(i-1));
        break;
      } //for
    } // if
  } // for

  int i_CurrentIt = 0;
  while(i_CurrentIt < m_NumIterations){
    //Run ant monte carlo for each ant
    for(int i = 0; i < (int) t_AntPaths.size(); i++){
      //Possible directions
      t_SinglePath t_PossiblyXY;
      //Possible weights
      std::vector<int> t_PossiblyW;
      int i_SumW = 0;
      //Get direction to target
      t_XYPoint t_Direction; 
      t_Direction.first = t_Targets.at(i).first - t_AntPaths.at(i).first;
      t_Direction.second = t_Targets.at(i).second - t_AntPaths.at(i).second;

      if(t_Direction.first >= 0 && t_Direction.second >= 0){
        for(int j = 0; j < (int) m_Roll2Node.size(); j++){
          if(m_Roll2Node.at(j).first >= 0 && m_Roll2Node.at(j).second >= 0){
            t_XYPoint t_Maybe;
            t_Maybe.first = t_AntPaths.at(i).first + m_Roll2Node.at(j).first;
            t_Maybe.second = t_AntPaths.at(i).second + m_Roll2Node.at(j).second;
            int i_Element = t_Maybe.first*m_NumCols + t_Maybe.second;
            t_PossiblyW.push_back(t_PMap.at(i_Element) + 1);
            t_PossiblyXY.push_back(m_Roll2Node.at(j));
            i_SumW = i_SumW + t_PMap.at(i_Element) + 1;
          } // if
        } // for
      } // if
      else if(t_Direction.first >= 0 && t_Direction.second <= 0){
        for(int j = 0; j < (int) m_Roll2Node.size(); j++){
          if(m_Roll2Node.at(j).first >= 0 && m_Roll2Node.at(j).second <= 0){
            t_XYPoint t_Maybe;
            t_Maybe.first = t_AntPaths.at(i).first + m_Roll2Node.at(j).first;
            t_Maybe.second = t_AntPaths.at(i).second + m_Roll2Node.at(j).second;
            int i_Element = t_Maybe.first*m_NumCols + t_Maybe.second;
            t_PossiblyW.push_back(t_PMap.at(i_Element) + 1);
            t_PossiblyXY.push_back(m_Roll2Node.at(j));
            i_SumW = i_SumW + t_PMap.at(i_Element) + 1;
          } // if
        } // for
      } // else if
      else if(t_Direction.first <= 0 && t_Direction.second >= 0){
        for(int j = 0; j < (int) m_Roll2Node.size(); j++){
          if(m_Roll2Node.at(j).first <= 0 && m_Roll2Node.at(j).second >= 0){
            t_XYPoint t_Maybe;
            t_Maybe.first = t_AntPaths.at(i).first + m_Roll2Node.at(j).first;
            t_Maybe.second = t_AntPaths.at(i).second + m_Roll2Node.at(j).second;
            int i_Element = t_Maybe.first*m_NumCols + t_Maybe.second;
            t_PossiblyW.push_back(t_PMap.at(i_Element) + 1);
            t_PossiblyXY.push_back(m_Roll2Node.at(j));
            i_SumW = i_SumW + t_PMap.at(i_Element) + 1;
          } // if
        } // for
      } // else if
      else{
        for(int j = 0; j < (int) m_Roll2Node.size(); j++){
          if(m_Roll2Node.at(j).first <= 0 && m_Roll2Node.at(j).second <= 0){
            t_XYPoint t_Maybe;
            t_Maybe.first = t_AntPaths.at(i).first + m_Roll2Node.at(j).first;
            t_Maybe.second = t_AntPaths.at(i).second + m_Roll2Node.at(j).second;
            int i_Element = t_Maybe.first*m_NumCols + t_Maybe.second;
            t_PossiblyW.push_back(t_PMap.at(i_Element) + 1);
            t_PossiblyXY.push_back(m_Roll2Node.at(j));
            i_SumW = i_SumW + t_PMap.at(i_Element) + 1;
          } // if
        } // for
      } // else

      //Decide on the path
      i_Roll = roll_dice();
      f_CWeights = f_Amount/(1.0*i_SumW);
      int i_CumulatedW = 0;
      for(int j = 0; j < (int) t_PossiblyXY.size(); j++){
        i_CumulatedW = i_CumulatedW + t_PossiblyW.at(j);
        if(i_Roll <= (int) f_CWeights*i_CumulatedW){
          t_XYPoint t_New;
          t_New.first = t_PossiblyXY.at(j).first + t_AntPaths.at(i).first;
          t_New.second = t_PossiblyXY.at(j).second + t_AntPaths.at(i).second;
          t_AntPaths.at(i).first = t_New.first;
          t_AntPaths.at(i).second = t_New.second;
          break;
        } // if
      } // for
      //Change target if ant path = target
      if(t_AntPaths.at(i) == t_Targets.at(i)){
        if(t_Targets.at(i) == t_Foods.at(i)){
          t_Targets.at(i) = t_Sources.at(i);
        } // if
        else{
          t_Targets.at(i) = t_Foods.at(i);
        } // else
      } // if
    } // for

    //update pmap
    for(int i = 0; i < (int) t_AntPaths.size(); i++){
      int i_E = t_AntPaths.at(i).first*m_NumCols + t_AntPaths.at(i).second;
      t_PMap.at(i_E)++;
    }//for
    
    i_CurrentIt++;
  } // while
  //Initialize all ants based on colony locations

  return t_PMap;
}// std::vector<int> ant_movement::run_ACO()


/*-----------------------------------------------------------------------------
void ant_movement::define_map_dims(int i_NumRows, int i_NumCols)

Define dims
-----------------------------------------------------------------------------*/
void ant_movement::define_map_dims(int i_NumRows, int i_NumCols){
  m_NumRows = i_NumRows;
  m_NumCols = i_NumCols;
} // void ant_movement::define_map_dims(int i_NumRows, int i_NumCols)