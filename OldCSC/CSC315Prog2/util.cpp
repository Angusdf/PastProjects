/**************************************************************************//**
 * @file util.cpp
 * @brief File to be used with util.h
 *****************************************************************************/

#include "util.h"

using namespace std;


/**************************************************************************//**
 * @author Dennis Kovarik 
 *
 * @par Description: Displays the usage statments.
 *
 *****************************************************************************/
void displayUsage()
{
    cout << "Incorrect number of arguments" << endl;
    cout << "This program requires the input file name." << endl;
    cout << "./start [input filename]" << endl;

    return;
}

/**************************************************************************//**
 * @author Dennis Kovarik
 *
 * @par Description: Opens the input file.
 *
 * @param[in,out]   fin           - Input file. 
 * @param[in]       inputFileName - Name of input file.
 * 
 * @returns true    true  - File opens correctly.
 * @returns false   false - File did not open correctly. 
 * 
 *****************************************************************************/
bool openFile( ifstream &fin, char inputFileName[] )
{
    //open file, alldata15.txt is only the first 15 movie entries, alldata.txt is the complete data  
    fin.open( inputFileName );
    
    //make sure movie file does open     
    if ( !fin.is_open() )
    {
        cout << "Movie file did not open" << endl;
        return false;
    }

    return true;
}


/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Menu lists options to preform within the program. 
 *
 * @param[in,out]   option - Chosen option form the menu 
 * @param[in,out]   input  - Contains either actor name or movie title.
 * @param[in,out]   target - target to find the degree to.
 *
 *****************************************************************************/
void menu(int& option, string& input, string& target)
{
   option = 0;
    //display the menu
    while(option <= 0 || option > 4)
    {
        cout << "Choose # for option: (1-6)"<<endl 
        << "1. Print degree of separation and shortest path." << endl 
        << "2. Print histogram." << endl
        << "3. Print longest shortest paths." << endl 
        << "4. Quit." << endl
	<< "Enter [1-4]: ";

    	//Read in option
    	cin >> option;
 	cout << endl;

	cin.ignore();
    	//deterime what the user wants to do

    	//Print degree of separation and shortest paths
        if(option == 1) 
        {
            cout << "Enter name of an actor or actress: ";
            getline(cin, input);

            return;
        }

	//Print histogram
        if(option == 2) 
        {
	    input = "Bacon, Kevin";
            return;
        }

        

	if(option == 4)
	{
	    return;
	}

    }

    return;
}



