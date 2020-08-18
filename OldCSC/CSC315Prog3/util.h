/**************************************************************************//**
 * @file util.h
 * @brief Header file to be used with util.cpp and main.cpp
 *****************************************************************************/


#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

/**
 * @brief Holds the structure for cities
 */
struct cityInfo
{
    string name = "";       /*!< name of city*/
    double latitude = 0.0;  /*!< latitude of the city*/
    double longitude = 0.0; /*!< longitude of the city*/
    double dist=0.0;        /*!< distance to the next city*/
    
    bool start = false;     /*!< flag for start city*/
    bool visit = false;     /*!< flag for visited city*/
    
    bool operator==(const cityInfo &rhs) const
    {
        return name == rhs.name;
    }
    
};




void adjacencyMatrix(vector<cityInfo> cities, double adjMatrix[][1000]);
/*!< creates the adjacency matrix for cities to cities*/

bool openFiles(char *argv[],vector<string>& toVisit, vector<cityInfo>& cord);
/*!< open files and performs checking*/

void readVisitCities(vector<string>& toVisit, ifstream& fin); 
/*!< reads in visited cities*/

void readCitiesInfo(vector<string> toVisit, ifstream& fin, 
                    vector<cityInfo>& cord);
/*!< reads in desired cities*/

bool checkIfValCity(vector<string> toVisit, vector<cityInfo> cord);
/*!< check if visited cities are valid*/

void bruteForcePath(int startIndex, vector<cityInfo> cities, 
                    double adjMatrix[][1000]);
/*!< performes the brute force method to find shortest path*/

void resetVar( string& again, bool& found, vector<cityInfo>& cord, 
               vector<string> toVisit  );
/*!< reset varibles for rpeatig program*/

void displayVisit(vector<string> toVisit);
/*!< display the cities to visit*/


void print( vector <cityInfo> cities, double adjMatrix[][1000]);
/*!< Prints cities visitedt*/
void prim(vector<cityInfo> cities, double adjMatrix[][1000], int start_index  );
/*!< Uses prim based algorithm to find shortest path*/
int find(int target, vector<int> route);
/*!< searches for city*/
void displayResult(vector<cityInfo> &cities, vector<int> route, double sum,
		int start_index);
/*!< Prints results of the prim algorithm*/

#endif
