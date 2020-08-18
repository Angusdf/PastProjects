/**************************************************************************//**
 * @file structs.h
 * @brief Header file to be used with graph.cpp and graph.h
 *****************************************************************************/

#ifndef STRUCT_H_
#define STRUCT_H_
#include <string>
#include <vector>


/**
 * @brief Holds the structure for actors
 */

struct starInfo
{
    std::string name = ""; /*!< name of actor*/
    int id;                /*!< Id of actor*/
    int degree = 0;	   /*!< Degree of separation from Bacon*/

    bool operator<(const starInfo &rhs) const
    {
	    return name < rhs.name;
    }
    
    bool operator==(const starInfo &rhs) const
    {
	return name == rhs.name;
    }

    std::string prev = "";  /*!< prev movie of actor*/
    bool visit = false;     /*!< determine if actor has been visited*/
};

/**
 * @brief Holds the structure for movies
 */
struct movieInfo
{
public:
    std::string movieName = ""; /*!< name of movie */
    bool visit = false;         /*!< determine if movie has been visited*/
    int id;                     /*!< id of the movie*/

    starInfo prev;              /*!< previous actor*/

    bool operator<(const movieInfo &rhs) const
    {
	    return movieName < rhs.movieName;
    }

    bool operator==(const movieInfo &rhs) const
    {
	return movieName == rhs.movieName;
    }    
};


#endif
