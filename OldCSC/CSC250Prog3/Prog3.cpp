/*************************************************************************//**
* @file
* @brief
*
* @mainpage Program 3 - Maze Solutions
*
* @section CSC250s17
*
* @author Angus Frisch
*
* @date 4/13/17
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
* @details This program will read in a maze from a .maz file into a dynamically
* allocated array. it will then try to find the least amount of steps to get to
* the exit of the maze.
*
* In this maze there is water 'W', lava 'L', walls '*', free space ' ' and one
* exit 'E'. Can not move through walls and lava, and cannot go diagonal. If
* the path goes through a water a '2' is placed and two is added to the step
* counter. If the path goes through free space a '1' is placed, and one is added
* to steps. Once it finds the exit it will add one to steps.
*
* The maze is then outputed to a file from the commadline with its starting
* infromation, the path it took to get to the exit and the amount of steps.
* The starting point is maked with a zero '0,' it does not count as a step.
* If no solution is found, it will display the maze with only the starting
* position
*

*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      Command line must have 3 arguments
*
* @par Usage:
  @verbatim
  c:\> prog3.exe input.maz output.txt
       input.maz - File that contains the maze size, starting location, and maze
       output.txt- file that records the fastest route to the exit, size,
       and starting location

  @endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
*
*
* @par Modifications and Development Timeline:
  <a href="https://gitlab.mcs.sdsmt.edu/7280127/csc250s17programs">
 Please see gitlab repository</a>
*
******************************************************************************/


#include <iomanip>
#include <iostream>
#include <fstream>


using namespace std;

void rightFiles ( int argc, char **argv, ifstream &fin, ofstream &fout );
void makeArray ( char ** &twodarray, int row, int col );
void deleteArray ( char **twodarray, int row );
void fillArray ( char **mazeptr, ifstream &fin, int row, int col );
void printArray ( char **twodarray, int row, int col, ofstream &fout );
void nextMove ( char ** &mazeptr, char ** &answerMaze, int startrow,
                int startcol, int row, int col, int &step, int &stepsFinal,
				int &count );
void copyArray ( char **mazeptr, char ** &answerMaze, int row, int col );


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will start the program, read in maze size amd starting location
* and end the program.
*
* @param[in]      argc - The count of the arguments provided by command prompt.
* @param[out]     argv - arguments provided by the command line
*
*
* @returns 0 program ran successful.
*****************************************************************************/
int main ( int argc, char **argv )
{
    ifstream fin;
    ofstream fout;
    int col, row, startrow, startcol, step = 0, stepsFinal = 0,
                                      count = 0, mazeNum = 1;
    char **mazeptr = nullptr, **answerMaze = nullptr;
    
    //Make sure that files are there and are opened
    rightFiles ( argc, argv, fin, fout );
    
    //continues to read in mazes as long as it reads in rows
    while ( fin >> row )
    {
        fin >> col;
        
        //resets the count, steps, and stepsFinal for ech maze
        count = 0;
        step = 0;
        stepsFinal = 0;
        fout << "Maze #" << mazeNum << ":" << endl;
        fout << "\t" << "Size: " << row << "x" << col << endl;
        
        //read in starting posistion
        fin >> startrow;
        fin >> startcol;
        //ignores end lines
        fin.ignore();
        
        fout << "\t" << "Start Location: " << startrow << " " << startcol << endl;
        
        //make arrays to hold maze and answer maze
        makeArray ( mazeptr, row, col );
        makeArray ( answerMaze, row, col );
        
        //puts maze into mazeptr
        fillArray ( mazeptr, fin, row, col );
        
        //sets starting postion to zero
        mazeptr[startrow][startcol] = '0';
        
        //copy maze into answer, incase of no solution
        copyArray ( mazeptr, answerMaze, row, col );
        
        //calls the first permutation
        nextMove ( mazeptr, answerMaze, startrow, startcol, row, col, step,
                   stepsFinal, count );
                   
        //counts the step onto the 'E' only if a sloution was found
        if ( stepsFinal != 0 )
        {
            stepsFinal++;
            fout << "\t" << "Shortest Path: " << stepsFinal << endl;
        }
        
        if ( stepsFinal == 0 )
        {
            fout << "\t" << "There is no solution" << endl;
        }
        
        printArray ( answerMaze, row, col, fout );
        
        //Function that deletes memory allocated to the arrays
        deleteArray ( mazeptr, row );
        deleteArray ( answerMaze, row );
        
        mazeNum++;
    }
    
    //Closes files
    fin.close();
    fout.close();
    
    return 0;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will open the check arguments, open files, check to see if
* the files open. If something fails, exits the program.
*
* @param[in]     argc - The count of the arguments provided by command prompt.
* @param[in]     argv - Arguments provided by the command line.
* @param[in,out] fin  - Input file.
* @param[in,out] fout - Output file.
*
*
*****************************************************************************/
void rightFiles ( int argc, char **argv, ifstream &fin, ofstream &fout )
{
    //Error if less than three arguments
    if ( argc < 3 )
    {
        cout << "To few arguments." << endl << "Ex: prog3 input.maz output.txt" <<
             endl;
        exit ( 1 );
    }
    
    //Error if more than three arguments
    if ( argc > 3 )
    {
        cout << "To many argumants." << endl << "Ex: prog3 input.maz output.txt" <<
             endl;
        exit ( 1 );
    }
    
    //If exactly three arguments open files
    fin.open ( argv[1] );
    fout.open ( argv[2] );
    
    //Error if both files fail to open
    if ( !fout && !fin )
    {
        cout << "Input file and Output file did not open" << endl;
        exit ( 1 );
    }
    
    //Check to see if the input file opens
    if ( !fin )
    {
        cout << "Input file did not open." << endl;
        exit ( 1 );
    }
    
    //Check to see if output opens
    if ( !fout )
    {
        cout << "Output file did not open" << endl;
        exit ( 1 );
    }
    
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will dynamically allocate a 2d array
*
* @param[in,out] twodarray - 2D array that will hold the maze
* @param[in]     row - variable that holds the amount of rows in the maze
* @param[in]     col - variable that holds the amount of columns in the maze
*
*
*****************************************************************************/
void makeArray ( char ** &twodarray, int row, int col )
{
    int i = 0, j = 0;
    
    //Give the array of pointers an address
    twodarray = new ( nothrow ) char *[row];
    
    //Checks to see if memory is avalible, deletes if not avalible
    if ( twodarray == nullptr )
    {
        cout << "Memory allocation error." << endl;
        delete [] twodarray;
        exit ( 1 );
    }
    
    //Makes array of columns, if memory is not avalible than deletes array
    for ( i = 0; i < row; i++ )
    {
        twodarray[i] = new ( nothrow ) char [col];
        
        if ( twodarray[i] == nullptr )
        {
            cout << "Memory allocation error." << endl;
            deleteArray ( twodarray, i );
            exit ( 1 );
        }
    }
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will free up the 2D array
*
* @param[in]     twodarray - 2D array that holds a maze.
* @param[in]     row - number of rows in the maze
*
*
*
*****************************************************************************/
void deleteArray ( char **twodarray, int row )
{
    int i = 0;
    
    //Check to see if there is anything to delete
    if ( twodarray == nullptr )
    {
        return;
    }
    
    //Deletes the columns
    for ( i = 0; i < row; i++ )
    {
        delete [] twodarray[i];
    }
    
    //deletes rows
    delete [] twodarray;
    
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will read in the maze from the file.

* @param[in]     mazeptr - contains the maze
* @param[in,out] fin - input file.
* @param[in]     row - variable that holds the amount of rows in the maze
* @param[in]     col - variable that holds the amount of columns in the maze
*
*****************************************************************************/
void fillArray ( char **mazeptr, ifstream &fin, int row, int col )
{
    int i = 0, j = 0;
    
    //Reads in maze from file to mazeptr
    for ( i = 0; i < row; i++ )
    {
        for ( j = 0; j < col; j++ )
        {
            //.get will get every character including whitespace
            mazeptr[i][j] = fin.get();
        }
        
        //Ignore new line character
        fin.ignore();
    }
}



/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will determind the next move to find the shortest path to 'E'

* @param[in,out]     mazeptr - contains the maze
* @param[in,out]     answerMaze - contans the shortest path
* @param[in]         startrow - staring row
* @param[in]         startcol - startig column
* @param[in]         row - variable that holds the amount of rows in the maze
* @param[in]         col - variable that holds the amount of columns in the maze
* @param[in,out]     step - number of steps in the attempt
* @param[in,out]     stepsFinal - shortest path steps
* @param[in, out]    count - deteminds if it is the fiest checked solution
*
*
*****************************************************************************/
void nextMove ( char ** &mazeptr, char ** &answerMaze, int startrow,
                int startcol, int row, int col, int &step, int &stepsFinal, int &count )
{

    //Checks to see if move is possible
    if ( mazeptr[startrow][startcol] == '*' ||
            mazeptr[startrow][startcol] == 'L' ||
            mazeptr[startrow][startcol] == '1' ||
            mazeptr[startrow][startcol] == '2' )
    {
    
        return;
    }
    
    if ( step != 0 )
    {
        if ( mazeptr[startrow][startcol] == '0' )
        {
            return;
        }
    }
    
    //Check to see if at the end of the maze
    if ( mazeptr[startrow][startcol] == 'E' )
    {
        //If first solution, make the stepsFinal=steps, count++, prevents
        //overwriting of a faster solution, and copies answer of the maze
        //into the answerMaze array
        
        if ( count == 0 )
        {
            stepsFinal = step;
            copyArray ( mazeptr, answerMaze, row, col );
            count++;
        }
        
        if ( step > stepsFinal )
        {
            return;
        }
        
        //Checks to see if solution is faster than previous
        if ( step < stepsFinal )
        {
            stepsFinal = step;
            copyArray ( mazeptr, answerMaze, row, col );
        }
        
        return;
    }
    
    //If next step is 'W' place 2 to indicate that it took two steps, also add
    //two to step
    if ( mazeptr[startrow][startcol] == 'W' )
    {
        mazeptr[startrow][startcol] = '2';
        step = step + 2;
    }
    
    //If next step is ' ' place 1 to indicate that it took one steps, also add
    //one to step
    if ( mazeptr[startrow][startcol] == ' ' )
    {
        mazeptr[startrow][startcol] = '1';
        step++;
    }
    
    //Next four fuctions determend if the next move in any direction is valid
    nextMove ( mazeptr, answerMaze, startrow - 1, startcol, row, col, step,
               stepsFinal, count );
               
    nextMove ( mazeptr, answerMaze, startrow + 1, startcol, row, col, step,
               stepsFinal, count );
               
    nextMove ( mazeptr, answerMaze, startrow, startcol + 1, row, col, step,
               stepsFinal, count );
               
    nextMove ( mazeptr, answerMaze, startrow, startcol - 1, row, col, step,
               stepsFinal, count );
               
    //Replaces the water steps back to a 'W' for later tests
    if ( mazeptr[startrow][startcol] == '2' )
    {
        mazeptr[startrow][startcol] = 'W';
        step = step - 2;
    }
    
    //Replaces the opens spaces to ' ' for later tests
    if ( mazeptr[startrow][startcol] == '1' )
    {
        mazeptr[startrow][startcol] = ' ';
        step--;
    }
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will copy a solution of the maze into a solution array.

* @param[in]     mazeptr - contains the maze
* @param[in,out] answerMaze - answer to the maze
* @param[in]     row - variable that holds the amount of rows in the maze
* @param[in]     col - variable that holds the amount of columns in the maze
*
*****************************************************************************/
void copyArray ( char **mazeptr, char ** &answerMaze, int row, int col )
{
    int i = 0, j = 0;
    
    //Copies the mazeptr into the answer
    for ( i = 0; i < row; i++ )
        for ( j = 0; j < col; j++ )
        {
            answerMaze[i][j] = mazeptr[i][j];
        }
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* This function will print the maze solution to the file given from the command
* line
*
* @param[in]     twodarray - contains the maze
* @param[in]     row - variable that holds the amount of rows in the maze
* @param[in]     col - variable that holds the amount of columns in the maze
* @param[in,out] fout- Output file.
*
*****************************************************************************/
void printArray ( char **twodarray, int row, int col, ofstream &fout )
{
    int i = 0, j = 0;
    
    //Print row after row
    for ( i = 0; i < row; i++ )
    {
        fout << "\t";
        
        for ( j = 0; j < col; j++ )
        {
            fout << twodarray[i][j];
        }
        
        fout << endl;
    }
    
    fout << endl;
}