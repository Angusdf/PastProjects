/*************************************************************************//**
* @file
* @brief File to be used with functions.h and functions.cpp
*
* @mainpage program 1 - dbham Error checking
*
* @section CSC250s17
*
* @author Angus Frisch
*
* @date 2/24/17
*
* @par Professor:
*         Professor Shrader
*
* @par Course:
*         CSC250 - Section 2 -  1:00 pm
*
* @par Location:
*         McLaury - 313
*
* @section program_section Program Information
*
* @details This program will read in a binary file from the command line, once
*file is read into the program, it will detertime if the contact
*information is vaild.
*
*If the information is considered to be invaild
*the information is out put to a file "bad.txt" this will display
*the user information that was given and a list of errors that was
*found.
*
*If no errors are found, the information will go to a "good.bin".
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      Command line must have 4 arguments
*
* @par Usage:
  @verbatim
  c:\> prog1.exe input_file.bin good_file.bin bad_file.txt
       input_file.bin-binary file that contains contact infromation
       good_file.bin-binary file that outputs good contacts
       bad_file.txt- text file that shows contact infomation with errors
  @endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
*
*
* @par Modifications and Development Timeline:
  @verbatim
  Date          Modification
 ------------  --------------------------------------------------------------
 Feb 10, 2017  Start program
 Feb 13, 2017  Read in file, make sure everything is read in correctly
               find dates
 Feb 15, 2017  Work on state, call, and class fuctions
 Feb 17, 2017  Work on date, state, RC, call functions, and some fomating
 Feb 20, 2017  Work on comments, and write to files, made it to read whole
               file
 Feb 23, 2017  Fix error with state, comments
 Feb 24, 2017  fix error with callsign function, comments
 Feb 25, 2017  Doxygen
 March 14, 2017 Fix errors
 March 15, 2017 Fix formating
 March 17, 2017 Fix formating

 @endverbatim
 *
 *****************************************************************************/

#pragma pack(1)
#include "functions.h"
/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will start the program, check to see if there is the right number
* of arguments in the command line. Check to see if the files open, calls fuctions
* closes files, and ends program.
*
* @param[in]      argc - The count of the arguments provided by command prompt.
* @param[out]     argv - arguments provided by the command line
*
*
* @returns 0 program ran successful.
*****************************************************************************/

int main ( int argc, char **argv )
{
    //file being read in
    ifstream fin;
    //files out
    ofstream fgood, fbad;
    // i, j are to keep track of where values are stored
    int i = 0, j = 0;
    //test holds most of the testing variables, fail_test determends if a test failed
    //calltest holds the tests for only the callsign
    int test[12], fail_test, dates[3][3], zip_codes[3], calltest[5];
    
    Record data;
    
    //checks to see if correct number of arguments
    if ( argc != 4 )
    {
        cout << "Not enough files";
        exit ( 1 );
    }
    
    //opens all filles
    fin.open ( argv[1], ios::in | ios::binary );
    fgood.open ( argv[2], ios::out | ios::trunc | ios::binary );
    fbad.open ( argv[3] );
    
    //checks to see if files open
    if ( !fin || !fgood || !fbad )
    {
        cout << "File did not open" << endl;
        exit ( 1 );
    }
    
    //close out put right away
    fgood.close();
    fbad.close();
    
    // reads in information from file
    while ( fin.read ( ( char * ) &data,
                       sizeof ( Record ) ) )
    {
        //if a function returns a negative number error was found
        //reset counter
        i = 0;
        test[0] = name ( data.name, i );
        test[1] = name ( data.address, i );
        test[2] = name ( data.city, i );
        test[3] = State ( data.state );
        test[4] = zip ( data.zipCode, zip_codes );
        //reset counter for date functions
        i = 0;
        test[5] = date ( data.birthDate, dates, i );
        test[6] = date ( data.licensedDate, dates, i );
        test[7] = date ( data.expirationDate, dates, i );
        test[8] = expire ( dates );
        test[9] = radioClassTest ( data.radioClass );
        call ( data.callSign, calltest );
        fail_test = fail ( test, calltest );
        
        //tests to see if any errors
        if ( fail_test != 0 )
        {
            //write errors to bad file
            fail_write ( data, dates, zip_codes, argv[3] );
            fbad.open ( argv[3], ios::out | ios::app );
            fbad << "Error(s):" << endl;
            fbad.close();
            fail_list1 ( test, argv[3], calltest );
            fail_list2 ( test, argv[3], calltest );
        }
        //if no errors found good record and writes to file
        else
        {
            good ( data, argv[2] );
        }
    }
    
    //closes files
    fin.close();
    fgood.close();
    fbad.close();
    return 0;
}