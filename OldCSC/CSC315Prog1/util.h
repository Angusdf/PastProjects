/**************************************************************************//**
 * @file
 * @brief File containing libraries and function protoypes.
 *****************************************************************************/

#ifndef UTIL__H__
#define UTIL__H__

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <cstring>
#include <math.h>
#include <iomanip>

using namespace std;

/**
 * @brief Holds the structure of the treenode
 */

struct treenode {
   char data=0b0; /*!<     */
   double freq;
   treenode *left;
   treenode *right;
};

bool cmpFreq( const treenode *a, const treenode *b );
void makeHistogram( unsigned char buffer[], int bytes, vector<char> & input,
    vector<int> & nums );
void printHistogram( vector<char> input, vector<int> nums, int bytes, 
    vector<string> & codes, vector<double> & fqs );
void makeTree( vector<treenode*> v1, treenode * & root, vector<char> input, 
    vector<double> fqs );
void searchTree( treenode *root, string code, string & found, char & leaf, 
    bool print );
void deleteTree( treenode * & root);
void compress( vector<string> codes, int bytes, vector<char> input, 
    ofstream & fout, ifstream & fin );
void stats( int inBytes, int outBytes, vector<double> fqs, 
    vector<string> codes );
void string2Binary( string code, unsigned int & binary );
void uint2String( unsigned int code, string & binary);
int printHist2File( vector<char> input, vector<string> codes, 
    vector<double> fqs, ofstream & fout );
void pass2( int & outBytes, ofstream & fout, char * outfile );

void decodeFileMain( ifstream & fin, int nBytes, ofstream & fout );
void sepHist( unsigned char * histogram, unsigned char * enFile, int & nBytes,
    vector<char> & usedChar, vector<double> & freq );
void decodefile(treenode * root, unsigned char * enFile, ifstream & fin,
    ofstream & fout );
#endif
