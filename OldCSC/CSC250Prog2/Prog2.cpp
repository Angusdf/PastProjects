/*************************************************************************//**
 * @file
 *
 * @mainpage Program 2 - List Mania
 *
 * @section course_section Course Information
 *
 * @author Joshua Duklet, Preston Ochsner, and Angus Frisch
 *
 * @date March 27, 2017
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC250 - M002 -  1:00 - 1:50 PM
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details This program will take integers from a text file and organize them
 * into three lists depending on some rules.  First, the program will check to
 * see if there is a valid amount of command line arguements and check to see
 * if the input and output files open.  If any of these fails, the program will
 * end.  List 1 is an ordered list, and list 2 and 3 are unordered lists.
 *
 *   For these lists, an ordered list class and unordered list class were
 * created.  Each of these has the the functions removeItem, printList, and
 * is Empty along with the constructor and deconstructor.  The ordered list has
 * a insertItem function because a number needs to be inserted in order, while
 * the unordered list class has a insertBeg and insertEnd because numbers in
 * the unordered list can only be inserted at the beginning and end.
 *
 *   Numbers are sorted by rules depending on if the same number is already in
 * a list or not.  Once a number has been inserted in a list, go on to the next
 * number.  If the number is not in list 1, insert it into the list.  If the
 * number is in list 1, remove it from list 1 and put in in list 2 at the front
 * if the number is not in list 2.  If the number is in list 2, remove it from
 * list 2 and put it into list 3 at the end if it is not in list 3.  If the
 * number is in list 3, remove it and place it back into the front of list 3.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None.
 *
 * @par Usage:
   @verbatim
   c:\> prog1.exe numbers.txt lists.txt
   d:\> c:\bin\prog1.exe numbers.txt lists.txt
   numbers.txt - input text file with integers
   lists.txt - output text file for the lists
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/csc250s17prog2/team23">
 *Please see gitlab repository</a>
 *
 *   
 *   
 *  
 *
 *****************************************************************************/

#include "orderedList.h"
#include "unorderedList.h"
#include <iomanip>
#include <iostream>

void fileOpen ( int argc, char **argv, ifstream &fin, ofstream &fout );

/**************************************************************************//**
 * @author Joshua Duklet
 *
 * @par Description:  This function mainly organizes what list to insert a
 * number in.  First, it will call another function to make sure there are
 * proper command line arguements.  Then, it will go through steps and insert
 * the number where it should be inserted.  Last, it will print out the lists.
 *
 * @param[in]  argc - Number of command line arguements.
 * @param[in]  argv - Stores the command line arguements.
 *
 * @returns 0 program is done
 *
 *****************************************************************************/

int main ( int argc, char **argv )
{
    ifstream fin; //input file stream
    ofstream fout; //output file stream
    
    orderedList list1; //first list, ordered
    unorderedList list2; //second list, unordered
    unorderedList list3; //thirst list, unordered
    
    //number currently being read
    int num = 0;
    
    //check to see if files have opened
    fileOpen ( argc, argv, fin, fout );
    
    //while numbers are being read in
    while ( fin >> num )
    {
    
        //if you can't remove from list 1, insert it
        if ( !list1.removeItem ( num ) )
        {
            list1.insertItem ( num );
        }
        else
        {
            //if removed from list 1, check list 2
            //if you can't remove it from list 2, insert it at the beginning
            if ( !list2.removeItem ( num ) )
            {
                list2.insertBeg ( num );
            }
            else
            {
                //if removed from list 2, check list 3
                //if you can't remove it from list 3, insert it at the end
                if ( !list3.removeItem ( num ) )
                {
                    list3.insertEnd ( num );
                }
                else
                {
                    //if removed from list 3, insert it at the beginning of 3
                    list3.insertBeg ( num );
                }
                
            }
            
        }
        
        
    }
    
    //print out the lists
    list1.printList ( fout, 1 );
    fout << endl << endl;
    list2.printUnordered ( fout, 2 );
    fout << endl << endl;
    list3.printUnordered ( fout, 3 );
    
    //close files
    fin.close();
    fout.close();
    
    return 0;
}


/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: This function will determind if there is the correct
 *                   number of arugments in the command line. If the correct,
 *                   it will open the files
 *
 * @param[in]     argc - number of arguments in command line (3).
 * @param[in]     argv - name of files from command line.
 * @param[in,out] fin  - name of input file that stored a list of numbers.
 * @param[in,out] fout - name of output file that will hold the three lists
 *                       of numbers
 *****************************************************************************/
void fileOpen ( int argc, char **argv, ifstream &fin, ofstream &fout )
{
    //Check to see if correct number of arguments, exit program if invalid
    if ( argc != 3 )
    {
        cout << "Incorrect amount of arguements.  Please only enter the ";
        cout << "input text file and the output text file." << endl;
        exit ( 1 );
    }
    
    //Open both input and output file
    fin.open ( argv[1] );
    fout.open ( argv[2] );
    
    //Checks to see if input and output open, if fail exit program
    if ( !fin )
    {
        cout << "Input file did not open." << endl;
        fin.close();
        fout.close();
        exit ( 1 );
    }
    
    if ( !fout )
    {
        cout << "Output file did not open." << endl;
        fin.close();
        fout.close();
        exit ( 1 );
    }
    
}