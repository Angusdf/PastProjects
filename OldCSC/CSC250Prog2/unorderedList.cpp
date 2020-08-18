/**************************************************************************//**
 * @file
 * @brief File to be used with unorderedList.h
 *****************************************************************************/
#include "unorderedList.h"

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Constructor for unorderedlist, set headptr=nullptr and
 *                   set count to zero
 *
 *****************************************************************************/
unorderedList::unorderedList()
{
    headptr = nullptr;
    count = 0;
}

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Deconstructs to the constructed unorderedlist, deletes
 *                   list
 *
 *****************************************************************************/

unorderedList::~unorderedList()
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
 * @par Description: This function will tell if a list is empty, if the list is
 *                   empty it will create the list. If the list has already been
 *                   created, it will add the number to the list at the front.
 *                   If the number is added 1 is added to count to keep the size
 *                   of the list.
 *
 * @param[in] num - num is the number that is going to be put into the list
 *
 * @return false  - memory was not allocated for the number.
 * @return true   - list was created with headptr at first node.
 * @return true   - number was aded to list, headptr pat new node.
 *
 *****************************************************************************/
bool unorderedList::insertBeg ( int num )
{
    //temp is a temporary node, headtemp to set temp->next to headptr
    node *temp = nullptr;
    node *headtemp = headptr;
    
    //gives temp and address
    temp = new ( nothrow ) node;
    
    //if memory was not allocated for the number return false
    if ( temp == nullptr )
    {
        return false;
    }
    
    //temp address points to input number
    temp->item = num;
    
    //check to see if list is empty
    if ( headptr == nullptr )
    {
        //create list with headptr = temp and headptr->next = nullptr
        headptr = temp;
        headptr->next = nullptr;
        
        //add one to count to keep track of list size
        count++;
        return true;
    }
    
    //temp->next to headptr, set headptr to temp to make front of list
    temp->next = headptr;
    headptr = temp;
    
    //temp->next to headtemp, add one to count
    temp->next = headtemp;
    count++;
    return true;
}

/**************************************************************************//**
 * @author Joshua Duklet
 *
 * @par Description: This function will insert a number at the end of an
 * unordered list.
 *
 *
 * @param[in]   num - the number being inserted
 *
 * @returns false memory was not allocated for the number.
 * @returns true the number was inserted when the list was empty.
 * @returns true the number was inserted at the end of the list.
 *
 *****************************************************************************/
bool unorderedList::insertEnd ( int num )
{
    node *curr = headptr; //pointer to the current number
    node *pre = headptr; //pointer to the previous number
    node *temp = nullptr; //pointer for the number being inserted
    
    //allocate memory for temp
    temp = new ( nothrow ) node;
    
    //if memory not allocated, return false
    if ( temp == nullptr )
    {
        return false;
    }
    
    //item in temp is the number that needs to be inserted
    temp->item = num;
    
    //if list is empty, let headptr point to it and the next go to nullptr
    if ( headptr == nullptr )
    {
        headptr = temp;
        headptr->next = nullptr;
        count++;
        return true;
    }
    
    //move pointers to the end of the list
    while ( curr != nullptr )
    {
        pre = curr;
        curr = curr->next;
    }
    
    //insert the number at the end of the list
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
 * @param[in]       num - this is the current item wanting to be removed
 *
 * @returns True if the item was removed
 *
 * @returns False if empty or could not be removed
 *
 *****************************************************************************/
bool unorderedList::removeItem ( int num )
{
    node *curr;
    node *pre;
    
    //makes sure the list is not empty before removing
    if ( isEmpty() )
    {
        return false;
    }
    
    //checks if the number is at the beginning, deletes node, decreases count
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
    
    //traverses the list until null or the number was found
    while ( curr != nullptr && curr->item != num )
    {
        pre = curr;
        curr = curr->next;
    }
    
    //if the number was not found false is returned
    if ( curr == nullptr )
    {
        return false;
    }
    
    //if the item is the last in the list, removes, decreases count and returns
    //true
    if ( curr->next == nullptr )
    {
        delete curr;
        pre->next = nullptr;
        count--;
        return true;
    }
    
    //bypasses node to be removed, decreases count of list, deletes the removed
    //node and returns true
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
 * @param[in]       fout - output file stream
 * @param[in]       listNum - the number of the list
 *
 *****************************************************************************/

void unorderedList::printUnordered ( ofstream &fout, int listNum )
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
 * @returns True if the list is empty
 *
 * @returns False if the list is not empty
 *
 *****************************************************************************/

bool unorderedList::isEmpty( )
{
    //checks if headptr is null, returns true
    if ( headptr == nullptr )
    {
        return true;
    }
    
    //the list is not empty
    return false;
}