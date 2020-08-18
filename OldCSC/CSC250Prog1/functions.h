/*************************************************************************//**
* @file
* @brief File to be used with Prog1.cpp and functions.cpp
*/
#define  _CRT_SECURE_NO_WARNINGS
#pragma pack(1)
#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;
/*!
* @brief Holds conatct infromation form binary file
*/
struct Record
{
    char name[30];                  /*!< Holds contact name*/
    char address[30];               /*!< Holdes contact address*/
    char city[28];                  /*!< Holds contact city*/
    char state[2];                  /*!< Holds contact state*/
    unsigned int zipCode;           /*!< Holds contact Zip codes*/
    unsigned int birthDate;         /*!< Holdes contact Birthday*/
    unsigned int licensedDate;      /*!< Holds contact license date*/
    unsigned int expirationDate;    /*!< Holds contact expiration date*/
    char radioClass;                /*!< Holds contact radio class*/
    char callSign[5];               /*!< Holds contact callsign*/
};
#endif
int name ( char *name, int &j );
int State ( char *state );
int zip ( int code, int zipcodes[] );
int date ( unsigned int givdate, int dates[][3], int &i );
int expire ( int dates[][3] );
int radioClassTest ( char radioClass );
void call ( char *Sign, int calltest[] );
int fail ( int test[], int calltest[] );
void fail_write ( Record info, int dates[][3], int zip_codes[],
                  char *argv );
void fail_list1 ( int test[], char *argv, int calltest[] );
void fail_list2 ( int test[], char *argv, int calltest[] );
void good ( Record info, char *argv );