/**************************************************************************//**
 * @file
 * @brief Header file to be used with unorderedList.cpp
 *****************************************************************************/

#include <fstream>
using namespace std;

/**
 * @brief Holds the functions of the unordered list class
 */

class unorderedList
{
    public:
        //will create an empty list
        unorderedList();
        /*!< Constructor, creates headptr and sets the count to 0*/
        
        //will free up all the nodes in the list
        ~unorderedList();
        /*!< Deconstructor, deletes the unordered list*/
        
        //if inserted return true
        bool insertBeg ( int num );
        /*!< Inserts the number in the front of the list*/
        
        //if inserted return true
        bool insertEnd ( int num );
        /*!< Inserts the number at the end of the list*/
        
        //if removed return true
        bool removeItem ( int num );
        /*!< Removes the selected number from the list, if in the list*/
        
        //print numbers on to screen
        void printUnordered ( ofstream &fout, int listNum );
        /*!< Prints out the selected unordered list*/
        
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
