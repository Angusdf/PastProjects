/**************************************************************************//**
 * @file
 * @brief File to be used with orderedList.h
 *****************************************************************************/
#include "orderedList.h"

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Creates the orderedlist, set headptr = nullptr, count= 0
 *
 *****************************************************************************/

orderedList::orderedList( )
{
    headptr = nullptr;
    count = 0;
    
}

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Deconstructs the orderedlist,  deletes the list
 *
 *****************************************************************************/

orderedList::~orderedList( )
{
    node *temp;
    
    while ( headptr != nullptr )
    {
        temp = headptr;
        headptr = headptr->next;
        delete temp;
    }
}

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Inserts the number into a oredered list
 *
 *
 * @param [in]       num - number passed in for insert

 * @return false  - memory was not allocated for the number.
 * @return true   - list was created with headptr at first node.
 * @return true   - number was aded to the
 *
 *****************************************************************************/

bool orderedList::insertItem ( int num )
{
    //curr and pre are address for a node.
    node *curr = headptr;
    node *pre = headptr;
    
    //Creates a tempoary node.
    node *temp = nullptr;
    temp = new ( nothrow ) node;
    
    //If memory was not allocated for the number return false.
    if ( temp == nullptr )
    {
        return false;
    }
    
    //Stores num onto temp node.
    temp->item = num;
    
    //If headptr == nullptr list is empty, create list.
    if ( headptr == nullptr )
    {
        headptr = temp;
        headptr->next = nullptr;
        //Add one to count to keep size.
        count++;
        return true;
    }
    
    //If input num is less than or equal to headptr num, make temp
    //the beganing of the list.
    if ( temp->item <= headptr->item )
    {
        temp->next = headptr;
        headptr = temp;
        count++;
        return true;
    }
    
    //Goes through to find num in the list.
    while ( curr != nullptr && curr->item <= temp->item )
    {
        pre = curr;
        curr = curr->next;
    }
    
    //If found will be added to the list in order, or if not found will be added
    //at the end of the list.
    pre->next = temp;
    temp->next = curr;
    
    count++;
    
    return true;
}

/**************************************************************************//**
 * @author Preston Ochsner
 *
 * @par Description: This function will remove the specified item from the
 * list. If the item is not in the list or the list is empty the function will
 * return false.
 *
 * @param [in]       num - this is the current item wanting to be removed
 *
 * @returns True the item was removed from the list
 *
 * @returns False the item was not in the list, of was empty
 *
 *****************************************************************************/

bool orderedList::removeItem ( int num )
{
    node *curr = nullptr;
    node *pre = nullptr;
    
    //makes sure the list is not empty
    if ( isEmpty() )
    {
        return false;
    }
    
    //checks if the item is in the front of the list, deletes, decreases count
    //and returns true
    if ( headptr->item == num )
    {
        curr = headptr;
        headptr = headptr->next;
        
        delete curr;
        
        count--;
        
        return true;
    }
    
    curr = headptr;
    pre = headptr;
    
    //traverses the list until end of list or the number is found
    while ( curr != nullptr && curr->item < num )
    {
        pre = curr;
        curr = curr->next;
    }
    
    //checks if end of list or if the item of the current node is not the
    //number being looked for
    if ( curr == nullptr || curr->item != num )
    {
        return false;
    }
    
    //if the last node is the desired node, deletes, decreases count and
    //returns true
    if ( curr->next == nullptr )
    {
        delete curr;
        pre->next = nullptr;
        count--;
        return true;
    }
    
    //the node was in the middle of the list, deletes, decreases count and
    //returns true
    pre->next = curr->next;
    
    count--;
    
    delete curr;
    
    return true;
}

/**************************************************************************//**
 * @author Joshua Duklet
 *
 * @par Description: This function will print out a list.  First, it prints
 * the list number and the size.  It then prints out all the numbers in the
 * list.  It prints a tab between each number and will create a new line every
 * 5 numbers.
 *
 * @param [in]       fout - output file stream
 * @param [in]       listNum - the number of the list
 *
 *****************************************************************************/

void orderedList::printList ( ofstream &fout, int listNum )
{
    //goes through the list and prints what number its on
    node *temp = nullptr;
    
    //number of integers currently printed for formatting
    int numPrinted = 0;
    
    
    //start temp at the begginging
    temp = headptr;
    
    //print off list number and size
    fout << "List " << listNum << ": size = " << count << endl;
    
    //while not at the end of the list, print each number
    while ( temp != nullptr )
    {
        fout << "\t" << temp->item;
        temp = temp->next;
        numPrinted++;
        
        
        //if 5 numbers in a row have been printed, start a new row
        if ( numPrinted % 5 == 0 )
        {
            fout << endl;
        }
    }
    
    fout << endl;
}

/**************************************************************************//**
 * @author Preston Ochsner
 *
 * @par Description: This function checks if the current list is empty
 *
 * @returns True if the list is empty, flase if not
 *
 * @returns False if the list is not empty
 *
 *****************************************************************************/

bool orderedList::isEmpty( )
{
    //checks if headptr is nullptr
    if ( headptr == nullptr )
    {
        return true;
    }
    
    //the list is not empty
    return false;
}