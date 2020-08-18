/**************************************************************************//**
 * @file
 * @brief File to be used with util.h
 *****************************************************************************/


#include "util.h"


/**************************************************************************//**
 * @author Jarod Osborn 
 *
 * @par Description:  Creates a Histogram of symbols read in from file.
 *
 * @param[in]        buffer - array containing bytes read from file.
 * @param[in]        bytes - number of bytes read in from file.
 * @param[in,out]    input - vector storing symbols found in file.
 * @param[in,out]    nums - vector storing amount of a character in file.
 * 
 * @returns 0      
 *
 *****************************************************************************/
void makeHistogram( unsigned char buffer[], int bytes, vector<char> & input, 
    vector<int> & nums )
{
    int i = 0, j = 0, count = 1;
    bool found;
   
    input.clear();
    nums.clear();
   
    // Read through each input byte.
    for( i = 0; i < bytes; i++ )
    {
        found = false;

        // If character stored in buffer matches a preexisting input character in the vector, 
        // character is found and number of that character is incremented.
        for( j = 0; !found && j < input.size(); j++ )
            if( buffer[i] == input.at( j ) )
            {
                found = true;
                nums[j]++;
            }

        // If character read into buffer is not found, character is added to input vector and 
        // number of that character found is set to 1.
        if( buffer[i] != '\n' && !found )
        { 
            input.push_back( buffer[i] );
            nums.push_back( 1 );
        }
    } 
}


/**************************************************************************//**
 * @author Jarod Osborn and Angus Frisch
 *
 * @par Description:
 *
 * @param[in,out] 
 * 
 * @returns 0      
 *
 *****************************************************************************/
void printHistogram( vector<char> input, vector<int> nums, int bytes, 
    vector<string> & codes, vector<double> & fqs  )
{
    int i = 0;
    string code = "", found = "", temp = "";
    vector<treenode*> v1;
   

    treenode * root = new (nothrow) treenode;
   
    // Outputs the number of code words and Histogram table.
    cout << " found " << input.size() << " code words " << endl << endl;

    cout << "Huffman Code Table\n" 
        << "-----------------------------\n"
        << "ASCII Code       Probability (%)       Huffman Code\n"
        << endl;


    cout.precision( 2 );
    cout << fixed;

    fqs.clear();
    //calculate the frequences of each characters
    for( i = 0; i < input.size(); i++ )
        fqs.push_back( double( nums[i] ) / double( bytes ) * 100.0 );
    
    makeTree( v1, root, input, fqs );
    
    //develop the codes for the 
    for( i = 0; i < input.size(); i++)
    {
        searchTree( root, code, temp, input.at( i ), false);
        codes.push_back( temp );
    }

    for( i = 0; i < input.size(); i++ )
    {
        cout << " " << int( input.at( i ) ) << " ( " 
            << input.at( i ) << " )" << setw( 20 )
            << fqs.at( i ) << setw( 20 )
            << codes.at( i ) << endl;
    }

    cout << endl;
   
   //clear the tree
    deleteTree( root );
}


/**************************************************************************//**
 * @author Jarod Osborn  
 *
 * @par Description: Compares the frequencies of two nodes
 *
 * @param[in]  a - tree node 
 * @param[in]  b - tree node
 * 
 * @returns true    true - left frequency is less than right frequency  
 * @return false    false - left frequency is greater than right frequency        
 *
 *****************************************************************************/
bool cmpFreq( const treenode *a, const treenode *b )
{
    return a->freq < b->freq;
}


/**************************************************************************//**
 * @author Jarod Osborn  
 *
 * @par Description: Creates a Huffman Coding Tree from a vector of nodes.
 *
 * @param[in]       v1 - Vector of nodes. 
 * @param[in,out]   root - Parent node.
 * @param[in]       input - Vector of unique characters. 
 * @param[in]       fqs   - Vector of frequencies. 
 *
 *****************************************************************************/
void makeTree ( vector<treenode*> v1, treenode * & root, vector<char> input, 
    vector<double> fqs )
{
    int i = 0;

    v1.clear();

    // Creates a node for each character in the input vector and adds it to v1.
    for( i = 0; i < input.size(); i++ )
    {
        treenode *c = new ( nothrow ) treenode{ input.at( i ), 
            fqs.at( i ), NULL, NULL };
        v1.push_back( c );
    }

    // Sorts the nodes based on frequency.
    sort( v1.rbegin(), v1.rend(), cmpFreq );

    // Combines the two smallest node frequencies and makes a node with the 
    // two smaller nodes as children.
    // Then resorts vector.
    while( v1.size() > 1 )
    {
        double newFreq = v1.at( v1.size() - 1 )->freq + 
            v1.at( v1.size() - 2 )->freq;

        treenode *combNode = new ( nothrow ) treenode{ ' ', newFreq, 
            NULL, NULL };

        combNode->left = v1.at( v1.size() - 1 );
        combNode->right = v1.at( v1.size() - 2 );

        v1.pop_back();
        v1.pop_back();
        v1.push_back( combNode );

        sort( v1.rbegin(), v1.rend(), cmpFreq );
    }

    // Root of tree is the remaining node in the vector.
    root = v1.at( 0 );
}


/**************************************************************************//**
 * @author Jarod Osborn  
 *
 * @par Description: Recursively searches tree to find either a code to a leaf
 * or a leaf to a code depending on if the given leaf is null.
 *
 * @param[in]        root - Root node of tree. 
 * @param[in]        code - Huffman code of a specific node.
 * @param[in,out]    found - Huffman code given or retrieved by the function.
 * @param[in,out]    leaf - Symbol of leaf given or retrieved by the function.
 * @param[in]        print - Boolean that enables output of tree if true.
 *      
 *****************************************************************************/
void searchTree( treenode * root, string code, string & found, char & leaf, 
    bool print )
{
    if( root->left == NULL )
    {
        // If leaf has a value and leaf matches current node,
        // found is now the Huffman Code.
        if( leaf != '\0' && root->data == leaf )
            found = code;
        // If leaf is null and current Huffman Code compares to passed in 
        //section of Huffman Code, leaf is the current node's symbol.
        else if( leaf == '\0' && found.compare(0,code.size(),code) == 0)
           leaf = root->data;

        // Outputs root if print is true.
        if( print )
            cout << root->data << '-' << code << "-" << root->freq << endl;

        return;
    }
    // Goes through each child node recursively.
    searchTree( root->left, code + '0', found, leaf, print );
    searchTree( root->right, code + '1', found, leaf, print );
}


/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Clears the tree nodes and its contents.
 *
 * @param[in,out] root - root to the tree 
 * 
 *****************************************************************************/
void deleteTree( treenode * & root)
{
    //delete the left node and contents
    if ( root->left == NULL )
    {
        root->data = char ( NULL );
        root->freq = double ( NULL );

        delete [] root;

        return;
    }
        
    deleteTree( root->right );    
    deleteTree( root->left );
    
    //delete the right node and contents
    root->data = char( NULL );
    root->freq = double( NULL );

    delete [] root;   
}


/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: compares the input file to the huffman table, inputs it 
 * a unsigned char, once the unsigned char is full, output to file.  
 *
 * @param[in]       codes - Huffman code table. 
 * @param[in]       bytes - Number of bytes in the file to be encoded.
 * @param[in]       input - Unique char from input file.  
 * @param[in,out]   fout - Output file.
 * @param[in,out]   fin - Input file.
 *
 *****************************************************************************/
void compress( vector<string> codes, int bytes, vector<char> input, 
    ofstream & fout, ifstream & fin )
{

    int i = 0, j = 0, bufflen = 0, overlen = 0, first = 0, 
        allowed = 0, k = 0, over = 0;
    unsigned int temp = 0;  
    unsigned char buff, ansbuff=0b00000000, tempshift=0b00000000, 
        tempover=0b00000000;
    vector<unsigned int> binary;

    binary.clear();
    binary.resize(codes.size());
    
    //set the postion back to to the start
    fin.seekg(0, fin.beg);
    
    //convert the string of 1's and 0's to binary
    for( i = 0; i < codes.size(); i++ )
    {
        string2Binary( codes[i], temp );
        binary[i] = temp;
    }

    i = 0;

    while( fin.read( ( char * ) &buff, sizeof(char) ))
        for( j = 0; j < codes.size(); j++ )

            //compare input to vector of known charcters
            if( buff == input[j] )
            { 
                if( ( codes[j].length() + bufflen ) == 8 )
                { 
                    //shift and OR the answer
                    ansbuff <<= codes[j].length();
                    ansbuff |= binary[j];

                    fout.write( ( char * ) & ansbuff, sizeof( char ) );

                    bufflen = 0;
                    ansbuff = 0b0; 
                }
 
                else if( ( codes[j].length() + bufflen ) < 8)
                {
                    ansbuff <<= codes[j].length();
                    ansbuff |= binary[j];
                    bufflen = bufflen + codes[j].length(); 
                }                   

                else
                {

                    allowed = 8 - bufflen;
                    over = codes[j].length() - allowed;
                    tempover = binary[j] >> allowed;
                    
                    ansbuff <<= allowed; 
                    ansbuff |= tempover;
                    
                    fout.write( ( char * ) & ansbuff, sizeof( char ) );
                    ansbuff = 0b0;
                    
                    tempshift |= binary[j];
                    tempshift << 8 - bufflen;
                    tempshift >> 8 - bufflen;
                    
                    ansbuff |= tempshift;
                    bufflen = codes[j].length() - allowed;  
                }
            }

        //print any extra 
        if( bufflen > 0 )
            fout.write( ( char * ) & ansbuff, sizeof( char ) );
}


/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Prints and calculates stats of the compression
 *
 * @param[in] inBytes - Number of bytes read in.
 * @param[in] outBytes - Number of bytes of encoded file.
 * @param[in] fqs - frequency of occurrence of the unique input characters.
 * @param[in] codes - Huffman table, vector of codes.  
 *      
 *
 *****************************************************************************/
void stats( int inBytes, int outBytes, vector<double> fqs, 
    vector<string> codes )
{
    int i = 0;
    double entropy = 0.0, avgbit= 0.0;
    double log2 = log( 2 );

    cout << "Huffman Coding Statistics\n-----------------------------\n"
        << "Compression Ratio = "
        << ( ( double ) outBytes / ( double ) inBytes ) * 100.0
        << "%" << endl;
    
    for( i = 0; i < fqs.size(); i++ )
        entropy -= ( fqs[i] / 100.0 ) * ( log( fqs[i] / 100.0 ) / log2 );

    cout << "Enthropy = " << entropy << endl;

    for( i = 0; i < fqs.size(); i++ )
        avgbit += ( double ) codes[i].length() * ( fqs[i] / 100.0 );

    cout << "Average Bits per symbol in Huffman coding = " << avgbit << endl;
}


/**************************************************************************//**
 * @author Angus Frisch 
 *
 * @par Description: Converts the Huffman code as string into binary.
 *
 * @param[in]       code - code in string form.
 * @param[in,out]   binary - code in binary form.
 *      
 *
 *****************************************************************************/
void string2Binary( string code, unsigned int & binary )
{ 
    int i = 0;

    binary = 0;
   
    for( i = 0; i < code.length(); i++ )
    {
        //if the code ends in a 0 OR w/ 0
        if( code[i] == '0' )
            binary |= 0b0;

        //if codes end a 1 OR  w/1
        if( code[i] == '1' )
            binary |= 0b1;

        //shift to correct length
        if( i + 1 < code.length() )
            binary <<= 1;
    }

}


/**************************************************************************//**
 * @author Jarod Osborn and Angus Frisch
 *
 * @par Description: Converts an unsigned int into a binary representation 
 * stored in a string.
 *
 * @param[in]       code - code in unsigned int form.
 * @param[in,out]   binary - binary form of code stored in a string.
 * 
 * @returns 0      
 *
 *****************************************************************************/
void uint2String( unsigned int code, string & binary )
{
    unsigned int temp = 0;
    string uCode = "";
    int mask[8] = { 128, 64, 32, 16, 8, 4, 2, 1};
    int i = 0;
    
    temp = code;

    for( i = 0; i < 8; i++ )
    {
        if( code % 2 == 0 )
            binary += "0";
        else if( code % 2 == 1 )
            binary += "1";

        code = code / 2;
    }

    reverse( binary.begin(), binary.end() );
}


/**************************************************************************//**
 * @author Angus Frisch and Jarod Osborn 
 *
 * @par Description: Prints the Histogram to output file
 *
 * @param[in]        input - Unique characters of the input file. 
 * @param[in]        codes - Codes from the Huffman Tree.
 * @param[in]        fqs   - Frequency of the unque characters
 * @param[in,out]    fout - Output file.
 * 
 * @returns 0      
 *
 *****************************************************************************/
int printHist2File( vector<char> input,  vector<string> codes,
    vector<double> fqs, ofstream & fout)
{
    int i = 0, histbits = 0, size = 0;
    
    // Outputs Histogram table to file.
    fout.clear();
    fout.seekp( 0, fout.beg );
    fout << "Huffman Code Table " 
        << "----------------------------- "
        << "ASCII Code       Probability (%)       Huffman Code "
        << endl;

    fout.precision(2);
    fout<<fixed; 
    
    // Prints the symbol, frequency, and respective frequency to file.
    for( i = 0; i < input.size(); i++ )
    {   
        fout << " " << int( input.at( i ) ) << " ( " 
            << input.at( i ) << " )" << "         "
            << fqs.at( i ) << "         "      
            << codes.at( i ) << " ";
    }

    // Outputs the size of the file to the file.
    size = fout.tellp();

    fout.seekp( 0, fout.beg );
    fout << size << " ";  
    fout.seekp( 0, fout.end );
    
    return fout.tellp();
}


/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Print to the screen on information form pass 2
 *
 * @param[in,out] outBytes - number of bytes of histogram, then just encoded.
 * @param[in,out] fout - Output file.
 * @param[in] outfile - Name of output file.
 * 
 * @returns 0      
 *
 *****************************************************************************/
void pass2( int & outBytes, ofstream & fout, char * outfile )
{
    int totalFileSize=0;

    fout.seekp( 0, fout.end );
    totalFileSize = fout.tellp();
    outBytes = totalFileSize - outBytes;

    cout << "Huffman Encoder Pass 2\n" << "-----------------------------\n"
        << "Wrote " << outBytes << " encoded to " << outfile << " ";
    
    fout.seekp( 0, fout.end ); 
    cout << "(" << fout.tellp() << " bytes including the Histogram)"
        << endl << endl;

}
