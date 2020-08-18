/*************************************************************************//**
 * @file main.cpp
 *
 * @mainpage Traveling Salesman Problem
 *
 * @section course_section Course Information
 *
 * @author Levi Bergevin and Angus Frisch
 *
 * @date December 5, 2018
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
 * @details The Traveling Salesman Problem (TSP) is a common topic when 
 * discussing a Hamilton Circuit. A Salesman must travel to a list of cities, 
 * but the saleman must at home. In order to save gas, time, 
 * and money the salesman needs to take the shortest possible path, while still 
 * going to all the cities. The solution can be found in two different ways: 
 * Brute Force and/or Minimal Spanning Tree (MST).
 *
 * Brute Force method will always find the shortest path. The programs speed 
 * depends on the visit file size. If the visit file is small, then the program 
 * is relatively fast. As the visit file increases, so does the time. Brute 
 * Force method will calculate all possible paths from the starting point, and 
 * only store the shotest.
 *
 * Minimal Spanning Tree (MST) will approximate the shortest path. Once a visit
 * file becomes large, MST is the recommended method. Where it sacrifice the 
 * exact shortest path for speed. From the starting point it will always choose
 * the shortest path to the next city. When the vist file has been completed, 
 * the
 * path will end back at the starting point.
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *  None.       
 *
 * @par Usage:
   @verbatim
  ./TSP allcities.txt visitedcities.txt
  
   allcities.txt - Data base of cities. Each line will have the coordinates 
                   * 1000 degree, name, county, and state abbreviation 
                   separated by "|".
                   (ex. #####|#####|City|County|State) 
   
   visitedcities.txt - List of cities that are desired to visit on each line.
                       Each line consisits of name, county, and state 
                       abbreviation separated.
                       (ex. City|County|State) 
  
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * 
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/7280127/csc315_fall2018_project3">
 
 *Please see gitlab repository</a>
 *
 *****************************************************************************/



#include "util.h"



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Main starts the program with inputs of argc and argv. It
 *will determine and if the command line is correctly written.
 *
 * @param[in]   argc - Number of arguments. 
 * @param[in]   argv - contains the strings given to the program.
 * 
 * @returns  0   - Program ran correctly.
 * @returns -1   - Incorrect Usage of program.
 * @returns -2   - input file didn't open, invalid information in one of the
                       files.
 * 
 *****************************************************************************/

int main(int argc, char *argv[])
{
    vector<string> toVisit;
    vector<cityInfo> cord;
    string startCity =" ", again = " ";
    vector<cityInfo>::iterator it; 
    bool found = false;
    int i=0, count=0, startIndex=0;
    double adjMatrix[1000][1000], BF_elapsed_sec = 0.0, MST_elapsed_sec = 0.0;
    clock_t begin, end;
    
    //check for correct arguments
    if ( argc != 3 )
    {
        cout << "Usage ./TSP allcities.txt visitedcities.txt "<<endl;
        return -1;
    }
    
    //make sure files open, 
    if ( openFiles(argv, toVisit, cord) == false)
        return -2;

    //make adjacency matrix    
    adjacencyMatrix(cord, adjMatrix);

    do
    {
        if (again=="y")
            resetVar(again, found, cord, toVisit );
            
        //Make sure user is going to a valid visit city 
        while(found == false)
        {
            cout << "Enter a city (City|County|State): ";
            getline(cin,startCity);
    
            for ( it = cord.begin(); found==false && it != cord.end(); it++)
            {
                if (startCity==(*it).name)
                {   
                    found=true;
                }
            }
        }
    

        cout << endl << "Tour computed by brute force algorithm" << endl;
    
       
        //find the index of the start city 
        for (i =0; i<cord.size(); i++)
        {
            if (cord[i].name == startCity)
            {
                cord[i].start = true;
                startIndex=i;
            }
        }
        
         //start timer for brute force 
        begin = clock();
        
        //find the shortest path by brute force 
        bruteForcePath(startIndex, cord, adjMatrix);
    
         //end timer 
        end = clock();
    
       //find the difference in seconds 
       BF_elapsed_sec = double (end-begin)/CLOCKS_PER_SEC;
    
       cout << endl << endl << "Tour computed by MST algorithm" << endl << endl; 
       begin = clock();     
 
       //function to do this, plus timer
       prim(cord, adjMatrix, startIndex);

         //end timer 
        end = clock();
    
        //find the difference in seconds 
         MST_elapsed_sec = double (end-begin)/CLOCKS_PER_SEC;
 
        cout << setprecision(8)<<fixed;
        cout << "Brute Force method took: " << BF_elapsed_sec << " seconds" 
            << endl << "MST method took:         " << MST_elapsed_sec 
            << " seconds" << endl;
        while(again !="y" && again != "n") 
        {
            cout << endl << "New starting point? (y/n): ";
            getline(cin,again);
        }
    }while(again =="y");
    return 0;   
}
