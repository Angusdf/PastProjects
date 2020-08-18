/**************************************************************************//**
 * @file
 * @brief Header file to be used with orderedList.cpp
 *****************************************************************************/
#include <fstream>
using namespace std;

/**
 * @brief Holds the functions of the ordered list class
 */

// Team 23, Joshua Duklet, Preston Ochsner, Angus Frisch
class orderedList
{
    public:
        //will create an empty list
        orderedList();
        /*!< Constructor, creates headptr and sets the count to 0*/
        
        //will free up all the nodes in the list
        ~orderedList();
        /*!< Deconstructor, deletes the ordered list*/
        
        //will place number into list in ascending order, return true if successful
        bool insertItem ( int num );
        /*!< Inserts the number into the list*/
        
        //will remove the node if number is found, return true if found
        bool removeItem ( int num );
        /*!< Removes the selected number from the list, if in the list*/
        
        //print numbers on to screen
        void printList ( ofstream &fout, int listNum );
        /*!< Prints out the selected ordered list*/
        
        //Checks if the list is empty
        bool isEmpty( );
        /*!< Checks if the headptr points to nullptr, which is an empty list*/
        
        
    private:
    
        /**
        * @brief Holds the functions of the ordered list class
        */
        
        struct node
        {
        
            int item;
            /*!< Contains the number stored in the node*/
            node *next;
            /*!< Contains the address of the next node*/
        };
        
        node *headptr;
        /*!< Holds the address of the first node of a list or nullptr*/
        int count;
        /*!< Holds the number of items in the list*/
};