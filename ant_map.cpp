/*-----------------------------------------------------------------------------
ant_map.cpp

2023-03-29 - Benjamin Ocampo - Created
2023-03-29 - Benjamin Ocampo - Defines and updates map

-----------------------------------------------------------------------------*/

#include "ant_map.h"


/*-----------------------------------------------------------------------------
ant_map::ant_map()

Class Constructor
-----------------------------------------------------------------------------*/
ant_map::ant_map(int i_NumRows, int i_NumCols){
  //Define map
  define_maps(i_NumRows, i_NumCols);
}// ant_map::ant_map()



/*-----------------------------------------------------------------------------
void ant_map::define_maps(int i_NumRows, int i_NumCols)

Define map
-----------------------------------------------------------------------------*/
void ant_map::define_maps(int i_NumRows, int i_NumCols){
  // Store num of rows and cols
  m_NumRows = i_NumRows;
  m_NumCols = i_NumCols;

  //Clear maps, then set all values in vector to 0
  m_PMap.clear();
  m_FMap.clear();
  m_CMap.clear();
  for(int i = 0; i < i_NumRows*i_NumCols; i++){
    m_PMap.push_back(0.0);
    m_FMap.push_back(0);
    m_CMap.push_back(0);
  } //for
}// void ant_map::define_maps(int i_NumScouts)


/*-----------------------------------------------------------------------------
void ant_map::add_colonies(t_SinglePath t_Path)

Define colonies. These entrances are assumed to be point sources
-----------------------------------------------------------------------------*/
void ant_map::add_colonies(t_SinglePath t_Path){
  for(int i = 0; i < (int) t_Path.size(); i++){
    std::pair<int, int> p_Coord = t_Path.at(i);
    if(p_Coord.first < m_NumRows && p_Coord.second < m_NumCols){
      int i_Element = p_Coord.first*m_NumRows + p_Coord.second;
      m_CMap.at(i_Element) = 1;
    } //if
  } //for
}// void ant_map::add_colonies(int i_NumScouts)


/*-----------------------------------------------------------------------------
void ant_map::add_food(t_SinglePath t_Path)

Define food location. These foods are assumed to be point sources
-----------------------------------------------------------------------------*/
void ant_map::add_food(t_SinglePath t_Path){
  for(int i = 0; i < (int) t_Path.size(); i++){
    std::pair<int, int> p_Coord = t_Path.at(i);
    if(p_Coord.first < m_NumRows && p_Coord.second < m_NumCols){
      int i_Element = p_Coord.first*m_NumRows + p_Coord.second;
      m_FMap.at(i_Element) = 1;
    } //if
  } //for
}// void ant_map::add_food(int i_NumScouts)


/*-----------------------------------------------------------------------------
void ant_map::add_scout_paths(t_SinglePath t_Path)

Define scout paths. Initialization.
-----------------------------------------------------------------------------*/
void ant_map::add_scout_paths(t_SinglePath t_Path){
  for(int i = 0; i < (int) t_Path.size(); i++){
    std::pair<int, int> p_Coord = t_Path.at(i);
    if(p_Coord.first < m_NumRows && p_Coord.second < m_NumCols){
      int i_Element = p_Coord.first*m_NumRows + p_Coord.second;
      m_PMap.at(i_Element) = 1;
    } //if
  } //for
}// void ant_map::add_scout_paths(int i_NumScouts)


/*-----------------------------------------------------------------------------
void ant_map::update_map(std::vector<int> v_PMap)

Update Pmap
-----------------------------------------------------------------------------*/
void ant_map::update_map(std::vector<int> v_PMap){
  for(int i = 0; i < m_NumCols*m_NumRows; i++){
      m_PMap.at(i) = v_PMap.at(i);
    }//for
}// void ant_map::update_map(std::vector<int> v_PMap)


/*-----------------------------------------------------------------------------
void ant_map::output_PMap()

Write PMap to file
-----------------------------------------------------------------------------*/
void ant_map::output_PMap(){
  //Get timestamp for filename
  std::time_t ti_Time = std::time(nullptr);
  std::string s_TimeNow = (std::string) std::asctime(std::localtime(&ti_Time));
  std::string s_FName = "PMap-" + s_TimeNow + ".txt";

  // Create and open a text file
  std::ofstream MyFile(s_FName);

  // Write to the file
  for(int i = 0; i < m_NumRows; i++){
    int i_Ei = i*m_NumCols;
    MyFile<<std::left<<std::setw(6)<<m_PMap.at(i_Ei);
    for(int j = 1; j < m_NumCols; j++){
      int i_Eij = i_Ei + j;
      MyFile<<";"<<std::left<<std::setw(6)<<m_PMap.at(i_Eij);
    } // for
    MyFile<<std::endl;
  } // for

  // Close the file
  MyFile.close();
}// void ant_map::output_PMap()