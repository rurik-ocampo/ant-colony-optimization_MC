# ant-colony-optimization_MC
This code runs a simple ant colony optimization method using Monte Carlo simulation.

To build and run the application, run the following:

make
./ant-colony-optimization

Under the file main.cpp, the values can be changed under the following variables:

  //Define variables
  int i_NumRows = 50; // Number or rows in map
  int i_NumCols = 50; // Number of columns in map
  int i_NumAnts = 20; // Number o worker ants
  int i_NumIterations = 10000; // Number of iterations
  t_SinglePath t_ColCoords; // Starting coordinates; Entrance of colony
  t_ColCoords.push_back(t_XYPoint (5,5));
  t_SinglePath t_FoodCoords; // Destination; Food Source
  t_FoodCoords.push_back(t_XYPoint (15,15));
  
A txt file with prefix PMap is generated at the end of the simulation. From there you can see something similar to the following:

0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;6283  ;12370 ;28    ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;9227  ;20702 ;5923  ;327   ;13    ;1     ;0     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;6     ;395   ;8758  ;9168  ;451   ;15    ;3     ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;2     ;12    ;189   ;6169  ;11056 ;1783  ;16    ;0     ;0     ;0     ;0     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;1     ;3     ;42    ;3484  ;11271 ;2734  ;45    ;1     ;1     ;1     ;1     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;2     ;8     ;60    ;2556  ;11242 ;3664  ;2     ;0     ;0     ;1     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;1     ;2     ;21    ;1745  ;11223 ;3162  ;6     ;1     ;0     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;10    ;2173  ;11289 ;2266  ;20    ;1     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;29    ;3195  ;10969 ;1500  ;7     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;59    ;4479  ;11163 ;1753  ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;4     ;123   ;6249  ;531   ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;2     ;1     ;0     
0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     ;0     


Where the numbers indicate the pheremone value. The higher values indicate that most likely path the ants ended up taking. So the shortest paths
Are found by identifying the highest values that form a line.
