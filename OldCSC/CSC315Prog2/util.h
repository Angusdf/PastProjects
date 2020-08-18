/**************************************************************************//**
 * @file util.h
 * @brief File containing libraries and function protoypes.
 *****************************************************************************/


#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"

using namespace std;


void displayUsage();
/*!< display the correct usage*/

bool openFile( ifstream &fin, char inputFileName[] );
/*!< open the file*/

void menu(int& option, string& input, string &target);
/*!< display the menu*/


#endif

