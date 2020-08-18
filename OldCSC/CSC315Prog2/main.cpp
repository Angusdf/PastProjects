/*************************************************************************//**
 * @file main.cpp
 *
 * @mainpage Bacon Number
 *
 * @section course_section Course Information
 *
 * @author Dennis Kovarik and Angus Frisch
 *
 * @date November 16, 2018
 *
 * @par Professor:
 *        Dr. Mengyu Qiao
 *
 * @par Course:
 *         CSC315 - M001 -  10:00 - 10:50 AM
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details Six Degrees of Kevin Bacon is popular game where a actor or movie 
 *is selected, and is connected to Kevin Bacon. It is said that any actor/movie
 *can be connected to Kevin Bacon form 1 to 6 degrees. Bacon himself has degree
 *zero. People that acted with in the same movie as him will get a degree of one.
 * Unique people that they acted with will have degree of 2, and etc.
 *
 *Given a file with one line entries of title/last, first/last, first.... the
 *program will construct adjacency lists of stars and movies. Once an option 
 *and its inputs are given, the program will either produce a path or histogram.
 *If actor or movie is not in the file, it will inform the user. 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *  None.       
 *
 * @par Usage:
   @verbatim
  ./Bacon_Number movieFile.txt
  
   movieFile - Movie database where one line contains a movie and all 
               actors/actress in that movie. Fields are separated by "/". 
               (ex. movie1/last1, first1/last2, first2/.../lastN, firstN)
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * 
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/7280127/csc315_fall2018_project2">
 
 *Please see gitlab repository</a>
 *
 *****************************************************************************/

#include "util.h"

/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Main starts the program with inputs of argc and argv. It
 *will determine and if the command line is correctly written.
 *
 * @param[in]   argc - Number of arguments. 
 * @param[in]   argv - contains the strings given to the program.
 * 
 * @returns 0    0 - Program ran correctly.
 * @returns 1    1 - Incorrect Usage of program.
 * @returns 2    2 - input file didn't open.
 * 
 *****************************************************************************/

int main (int argc, char *argv[])
{   
    ifstream fin;
    int option =0;
    string targName;
    string input = " ", name;
    starInfo target;
    starInfo actor;
    movieInfo movie;
    graph starGraph;

    

    //Check command line arguments and display usage
    if(argc != 2)
    {
	    //Display Usage
	    displayUsage();

	    return 1;
    }

    //Open input file
    if( !openFile(fin, argv[1]) )
    {
	    return 2;
    }

    starGraph.constructGraph( fin );

    do
    {
        target.name = "Bacon, Kevin";
    	menu(option, input, targName);
   


    	//Find an Actors Degrees of Bacon
    	if(option == 1) 
    	{
	    actor.name = input;
      	    starGraph.degreesOfSeparation(actor, target);	
    	}
    	//Print Histogram of actor
    	else if(option == 2) 
    	{
	    actor.name = input;
       	    starGraph.makeHistogram(actor); 
        }
	else if(option == 3)
	{
	    starGraph.getLongestShortestPaths();
	}
	
	cout << endl << endl;
	
    }while( option != 4 );
   
     return 0;
}

