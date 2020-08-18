/**************************************************************************//**
 * @file graph.h
 * @brief Header file to be used with graph.cpp
 *****************************************************************************/


#ifndef GRAPH_H_
#define GRAPH_H_
#include "structs.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <queue>

/**
 * @brief Holds the functions of the graph class
 */

class graph
{
public:
    graph(){}
    ~graph(){}
      
    
    bool constructGraph(std::ifstream &fin); /*!< creates the adjacency lists*/
      
    void degreesOfSeparation(starInfo actor, starInfo target);
    /*!< deterimes the degree of separation and print to screen*/
     
    void movieDegreesOfSeparation(movieInfo startMovie, starInfo target);
    /*!< creates the belt deterimes the degree of separation
         and print to screen*/

    void makeHistogram(starInfo actor);
    /*!< find degree and connectivity of actor*/
    
    void movieMakeHistogram(movieInfo startMovie);
    /*!< find degree and connectivity of movie*/

    void getLongestShortestPaths();
  
private:
    std::map< movieInfo, std::set<starInfo> > movies; 
    /*!< map to movies*/
    std::map< starInfo, std::set<movieInfo> > stars;
    /*!< map to actors*/
    std::set<starInfo> longestShortestPaths;
};

#endif
