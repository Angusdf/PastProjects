/*************************************************************************//**
* @file
* @brief File to be used with functions.h and Prog1.cpp
*/

#pragma pack(1)
#include "functions.h"
/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* function determends if a name, address, or city are vaild in the contact
* infromation
*
* @param[in]      name - character string of name, address, or city
* @param[in,out]  j    - counter to determined
* *
* @returns 0 function found no errors.
* @returns -# function found # errors.
***************************************************************************/
int name ( char *name, int &j )
{
    // value that will be returned
    int results = 0;
    // i is counter
    unsigned int i = 0;
    
    // j decides what to test, name j=0, j=1 address, j=2 city
    if ( j == 0 )
    {
        // checks to see if any invalid
        for ( i = 0; i < strlen ( name ); i++ )
        {
            //characters
            if ( !isalpha ( name[i] ) && name[i] != ' ' && name[i] != '.' )
            {
                //if invalid minus one from results
                results--;
            }
        }
    }
    
    // check address if all characters are valid
    if ( j == 1 )
    {
        for ( i = 0; i < strlen ( name ); i++ )
        {
            if ( !isalnum ( name[i] ) && name[i] != ' ' && name[i] != '.' &&
                    name[i] != '#' )
            {
                //subtract one if found error
                results--;
            }
        }
    }
    
    // check city for vaild characters
    if ( j == 2 )
    {
        for ( i = 0; i < strlen ( name ); i++ )
        {
            if ( !isalpha ( name[i] ) && name[i] != ' ' && name[i] != '.' )
            {
                //minus one if error
                results--;
            }
        }
    }
    
    //counter to keep tract of what to check
    j++;
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* A detailed description of the function.  It can
* extend to multiple lines
*
* @param[in,out]  state - state given from contact informaion
*
* @return  0 no errors found
* @return -1 first character is undercase
* @return -2 State code is invaild
* @return -3 state code is invaild and first character is undercase
*****************************************************************************/
int State ( char *state )
{
    int i = 0, test = 0, cap_test = 0, results = 0; //test if vaild state
    //cap_test is capitalization
    //results is output errors
    //found
    
    //list of states, temp_states stores saves state that is input
    char *listostates[50] = { "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE",
                              "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS",
                              "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS",
                              "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY",
                              "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
                              "SD", "TN", "TX", "UT", "VA", "WA", "WV", "WI",
                              "WY", "VT"
                            }, temp_state[2];
    //stores state into temp to later resave into state unaltered
    temp_state[0] = state[0];
    temp_state[1] = state[1];
    
    // checks to see if first letter is
    if ( !isupper ( temp_state[0] ) )
    {
        // capital
        cap_test--;
    }
    
    // forces both char to be capital
    _strupr ( temp_state );
    
    for ( i = 0; i < 50; i++ )
    {
        // runs through the list to find a match
        // compares first 2 char in the strings
        if ( strncmp ( temp_state, listostates[i],
                       2 ) == 0 )
        {
            // if mach found adds 1 to test
            test++;
        }
        
    }
    
    //if the first character isnt capital subtract one
    if ( cap_test == -1 )
    {
        results--;
    }
    
    // if no match ins found subtracts -2
    if ( test == 0 )
    {
        results -= 2;
    }
    
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* decompress zip codes and determineds if the zipcodes are vaild
*
* @param[in]      code     - compressed number that conatins both 5zip and 4 zip
* @param[out]     zipcodes - contains both 5 zip and 4 zip after decompression
*
* @return  0 no errors found
* @return -1 problem with 4 zip
* @return -2 problem with 5 zip
* @return -3 both had errors
*****************************************************************************/
int zip ( int code, int zipcodes[] )
{
    //results are the results of the tests
    int results = 0;
    // sub mask for zip code for 4zip is 16383 and for 5zip is 524287
    zipcodes[1] = code & 16383;
    // move bits over 14 to the right to get access to 5zip
    code = code >> 14;
    zipcodes[0] = code & 524287;
    
    //check to see if 4zip is valid not checking if it is zero
    if ( zipcodes[1] < 1000 || zipcodes[1] > 9999 )
    {
        results--;
    }
    
    //check to see if it is 0 if it is undo last check
    if ( zipcodes[1] == 0 )
    {
        results++;
    }
    
    //checks to see if 5zip is vallid subtracts two
    if ( zipcodes[0] < 10000 || zipcodes[0] > 99999 )
    {
        results -= 2;
    }
    
    //retuns -1 if 4zip error, -2 if 5zip error, -3 if both error, 0 if good
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* decompress the compressed date, and tests dates
* @param[in]      givdate - date given from contact info
* @param[in,out]  dates - keeps dates in array for later use
* @param[in,out]  i - saves dates into correct index in dates[i][]
*
* @return   0 no errors
* @returns -1, -3, -5, -7 error with month
* @returns -2, -3, -4, -7 error with day
* @returns -4, -5, -6, -7 error with year
*
*****************************************************************************/
int date ( unsigned int givdate, int dates[][3], int &i )
{
    int  day = 0, month = 0, year = 0, date = givdate, mtest = 0, dtest = 0,
         ytest = 0, results = 0;
         
    //takes out the day using 63 as submask
    day = date & 63;
    //removes last six bits to
    date = date >> 6;
    // find month using 15 as submask
    month = date & 15;
    //removes the last six bit
    date = date >> 6;
    //finds month using submask 4095
    year = date & 4095;
    
    // checks to see if month if incorrect
    if ( month < 1 || month > 12 )
    {
        //  subtracts 1 from mtest
        mtest--;
    }
    
    // checkes Feb. days
    if ( month == 2 )
    {
        //if not in range subtracts 1 form dtest
        if ( day < 1 || day > 28 )
        {
            dtest--;
        }
    }
    
    if ( month == 4 || month == 6 || month == 9 || month == 11 )
    {
        //checks April, Hune, Sep., Nov. days
        if ( day < 1 || day > 30 )
        {
            // if out if range subtracts 1 form dtest
            dtest--;
        }
    }
    //checks if it is a reasonable day if invalid
    else if ( day < 1 || day > 31 )
    {
        //invalid is found, if month is not found
        dtest--;
    }
    
    //checks if vaild year, if not subtracts
    if ( year < 1900 || year > 2017 )
    {
        //1 from ytest
        ytest--;
    }
    
    //stores date to be used for output
    dates[i][0] = month;
    dates[i][1] = day;
    dates[i][2] = year;
    
    //add one to counter
    i++;
    
    // determines what to out put if an error is found
    if ( mtest == -1 )
    {
        results--;
    }
    
    if ( dtest == -1 )
    {
        results -= 2;
    }
    
    if ( ytest == -1 )
    {
        results -= 4;
    }
    
    //returns 0 if no error is found or
    //a negative number to the sum of the errors found
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* checks to see if expireation date comes before license date
*
* @param[in]      dates - array of dates
*
* @return  0 no errors found
* @return -1 xpiration date comes before license
*****************************************************************************/
int expire ( int dates[][3] )
{
    int results = 0;
    
    //test to years
    if ( dates[1][2] > dates[2][2] )
    {
        results--;
    }
    
    //if years = then test months
    if ( dates[1][2] == dates[2][2] )
    {
        dates[1][1] = dates[2][1];
        
        if ( dates[1][1] < dates[2][1] )
        {
            results--;
        }
        
        //if months = then test days
        if ( dates[1][1] == dates[2][1] )
        {
            if ( dates[1][0] < dates[2][0] )
            {
                results--;
            }
        }
        
    }
    
    //returns a negative 1 if one fails
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* decompress zip codes and determineds if the zipcodes are vaild
*
* @param[in,out]   radioClass   - class that is given by contact info
*
* @return  0 no errors found
* @return -1 not vaild Class
******************************************************************************/
int radioClassTest ( char radioClass )
{
    //lsit of possible
    char typeoclass[6][1] = { 'T', 'N', 'G', 'A', 'X', 'P' },
                            temp_class;
    int out = -1, i;
    //inputs, temp_class stores Class to mod
    temp_class = radioClass;
    //forces class to be capital
    temp_class = toupper ( temp_class );
    
    //checks input with all possible options
    for ( i = 0; i < 6; i++ )
    {
        if ( temp_class == typeoclass[i][0] )
        {
            //adds onre to a negative 1 to make a zero if correct
            out += 1;
        }
    }
    
    // return -1 for fail, 0 for success
    return out;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* decompress zip codes and determineds if the zipcodes are vaild
*
* @param[in,out]   Sign - call sign given by contact information
* @param[in,out]   calltest- contains errors for call test
*
*****************************************************************************/
void call ( char *Sign, int calltest[] )
{
    //all possible inputs and temp_sign to store
    char valsign[3] = { 'K', 'W', 'N' };
    char num[11] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' },
                   temp_sign[5];
    int first_up_test = 0, first_correct = -1, Sec_Four_five = 0,
        num_test = -1, Alpha_test = 0, i = 0, results = 0;
    calltest[0] = 0;
    calltest[1] = 0;
    calltest[2] = 0;
    calltest[3] = 0;
    calltest[4] = -1;
    
    //saves the Sign into temp to return later on
    for ( i = 0; i < 5; i++ )
    {
        temp_sign[i] = Sign[i];
    }
    
    // checks to see if the first is upper
    if ( !isupper ( Sign[0] ) )
    {
        first_up_test--;
    }
    
    //test to see if is aplhabet and upper
    if ( isalpha ( Sign[1] ) && !isupper ( Sign[1] ) || isalpha ( Sign[3] ) &&
            !isupper ( Sign[3] ) || isalpha ( Sign[4] ) &&
            !isupper ( Sign[4] ) )
    {
        //if error found subtract 1
        Alpha_test--;
    }
    
    if ( !isupper ( Sign[1] ) || !isupper ( Sign[3] ) || !isupper ( Sign[4] ) )
    {
        //checks to make sure the second fourth and fith are valid
        Sec_Four_five--;
    }
    
    //forces callsign to be upper
    Sign[0] = toupper ( Sign[0] );
    
    for ( i = 0; i < 3; i++ )
    {
        //makes sure that the first character is valid
        if ( Sign[0] == valsign[i] )
        {
            first_correct++;
        }
    }
    
    // checks to see if the third index is a valid number
    for ( i = 0; i < 10; i++ )
        if ( Sign[2] == num[i] )
        {
            calltest[4]++;
        }
        
    //determines what is an error
    if ( first_up_test == -1 )
    {
        calltest[0]--;
    }
    
    if ( first_correct == -1 )
    {
        calltest[1]--;
    }
    
    if ( Alpha_test == -1 )
    {
        calltest[2]--;
    }
    
    if ( Sec_Four_five == -1 )
    {
        calltest[3]--;
    }
    
    //reverts the sign to the orginal
    for ( i = 0; i < 5; i++ )
    {
        Sign[i] = temp_sign[i];
    }
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* test to see if anything fails (anything=-#)
*
* @param[in]      test    - arrary of errors
* @param[in]     calltest - array of callsign errors
*
* @return  0 no errors found
* @return -# erros found
******************************************************************************/
int fail ( int test[], int calltest[] )
{
    int results = 0, i = 0;
    
    //checks to see if anything failed
    for ( i = 0; i < 10; i++ )
        if ( test[i] != 0 || calltest[0] )
        {
            results--;
        }
        
    //checks to see if the call sign passes tests
    if ( calltest[0] != 0 || calltest[1] != 0 ||
            calltest[2] != 0 || calltest[3] != 0 || calltest[4] != 0 )
    {
        results--;
    }
    
    //returns negative number if anything fails
    return results;
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* Writes bad contact information
*
* @param[in]    info  - contact information
* @param[in]    dates - array of dates
* @param[in]    zip_codes- array of zipcodes
* @param[in]    argv- name of file writing to
*
*****************************************************************************/
void fail_write ( Record info, int dates[][3], int zip_codes[],
                  char *argv )
{
    int i = 0;
    ofstream bad;
    bad.open ( argv, ios::out | ios::app );
    //makes the top line 80 char of *, and formates information found
    bad << setfill ( '*' ) << setw ( 80 ) << " " << endl
        << "Name:" << "               " << info.name << endl
        << "Address:" << "            " << info.address << endl
        << "City State Zip:" << "     " << info.city << " " << info.state[0] <<
        info.state[1]
        << " " << setw ( 5 ) << setfill ( '0' ) << zip_codes[0] << "-" << setw (
            4 ) <<
        setfill ( '0' ) << zip_codes[1] << endl << "Birthdate:" << "          ";
        
    for ( i = 0; i < 3; i++ )
    {
        bad << dates[0][i];
        
        if ( i == 0 || i == 1 )
        {
            bad << "/";
        }
    }
    
    bad << endl << "Lincesnsing Dates:" << "  ";
    
    for ( i = 0; i < 3; i++ )
    {
        bad << dates[1][i];
        
        if ( i == 0 || i == 1 )
        {
            bad << "/";
        }
    }
    
    bad << "-";
    
    for ( i = 0; i < 3; i++ )
    {
        bad << dates[2][i];
        
        if ( i == 0 || i == 1 )
        {
            bad << "/";
        }
    }
    
    bad << endl << "Class-Callsign:" << "     " << info.radioClass << "-";
    
    for ( i = 0; i < 5; i++ )
    {
        bad << info.callSign[i];
    }
    
    bad << endl << endl;
    bad.close();
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* out puts the error into the file
*
* @param[in]     test - array of errors
* @param[in]     argv - name of file
* @param[in]     calltest - array of callsign test
*
*****************************************************************************/
void fail_list1 ( int test[], char *argv, int calltest[] )
{
    ofstream bad;
    bad.open ( argv, ios::out | ios::app );
    
    //if a stament is true output error
    if ( test[0] != 0 )
    {
        bad << "     Invalid character in the name field " << endl;
    }
    
    if ( test[1] != 0 )
    {
        bad << "     Invalid character in the address field " << endl;
    }
    
    if ( test[2] != 0 )
    {
        bad << "     Invalid character in the city field " << endl;
    }
    
    if ( test[3] == -1 || test[3] == -3 )
    {
        bad << "     First character of State Code not capitalized" << endl;
    }
    
    if ( test[3] == -2 || test[3] == -3 )
    {
        bad << "     Invalid State code " << endl;
    }
    
    if ( test[4] == -1 || test[4] == -3 )
    {
        bad << "     Invalid 4 digit plus code" << endl;
    }
    
    if ( test[4] == -2 || test[4] == -3 )
    {
        bad << "     Invalid 5 digit zip code  " << endl;
    }
    
    if ( test[5] == -1 || test[5] == -3 || test[5] == -5 || test[5] == -7 )
    {
        bad << "     Invalid month in Birthday " << endl;
    }
    
    if ( test[5] == -2 || test[5] == -3 || test[5] == -6 || test[5] == -7 )
    {
        bad << "     Invalid day in Birthday " << endl;
    }
    
    if ( test[5] == -4 || test[5] == -5 || test[5] == -6 || test[5] == -7 )
    {
        bad << "     Invalid year in Birthday " << endl;
    }
    
    bad.close();
}


/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* out puts the error into the file
*
* @param[in]     test - array of errors
* @param[in]     argv - name of file
* @param[in]     calltest - array of callsign test
*
*****************************************************************************/
void fail_list2 ( int test[], char *argv, int calltest[] )
{
    ofstream bad;
    bad.open ( argv, ios::out | ios::app );
    
    if ( test[6] == -1 || test[6] == -3 || test[6] == -5 ||
            test[6] == -7 )
    {
        bad << "     Invalid month in License " << endl;
    }
    
    if ( test[6] == -2 || test[6] == -3 || test[6] == -6 ||
            test[6] == -7 )
    {
        bad << "     Invalid day in License " << endl;
    }
    
    if ( test[6] == -4 || test[6] == -5 || test[6] == -6 ||
            test[6] == -7 )
    {
        bad << "     Invalid year in License " << endl;
    }
    
    if ( test[7] == -1 || test[7] == -3 || test[7] == -5 ||
            test[7] == -7 )
    {
        bad << "     Invalid month in Expiration" << endl;
    }
    
    if ( test[7] == -2 || test[7] == -3 || test[7] == -6 ||
            test[7] == -7 )
    {
        bad << "     Invalid day in Expiration" << endl;
    }
    
    if ( test[7] == -4 || test[7] == -5 || test[7] == -6 ||
            test[7] == -7 )
    {
        bad << "     Invalid year in Expiration" << endl;
    }
    
    if ( test[8] == -1 )
    {
        bad << "     Expiration Date is not after the License Date" << endl;
    }
    
    if ( test[9] != 0 )
    {
        bad << "     Radio Class code is invalid" << endl;
    }
    
    if ( calltest[1] == -1 )
    {
        bad << "     Invalid first character in call sign" << endl;
    }
    
    if ( calltest[3] == -1 && calltest[2] == 0 )
    {
        bad << "     Invalid second, fourth or fifth character in call sign" <<
            endl;
    }
    
    if ( calltest[4] == -1 )
    {
        bad << "     Invalid digit in call sign" << endl;
    }
    
    if ( calltest[0] == -1 || calltest[2] == -1 )
    {
        bad << "     Call Sign not upper case" << endl;
    }
    
    bad.close();
}

/**************************************************************************//**
* @author Angus Frisch
*
* @par Description:
* decompress zip codes and determineds if the zipcodes are vaild
*
* @param[in]     info     - contact infromation
* @param[in]     argv - file name
*
*
*****************************************************************************/
void good ( Record info, char *argv )
{
    //out puts everything into good file
    ofstream good;
    good.open ( argv, ios::out | ios::app | ios::binary );
    good.write ( ( char * ) info.name, sizeof ( Record ) );
}