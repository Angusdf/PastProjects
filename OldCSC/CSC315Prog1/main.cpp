/*************************************************************************//**
 * @file
 *
 * @mainpage Huffman Code
 *
 * @section course_section Course Information
 *
 * @author Jarod Osborn and Angus Frisch
 *
 * @date October 21, 2018
 *
 * @par Professor:
 *        Dr. Mengyu Qiao
 *
 * @par Course:
 *         CSC315 - M001 -  10:00 - 10:50 AM
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details Data compression programs contains both a encoder and decoder. The 
 * encoder will take in a file and encode it to an given output file (ideally 
 * one with less storage space). The decoder takes in a encoded file, and 
 * outputs the orginal file (with lossless data).
 *
 * A Huffman encoder reads the inputfile twice. The first time through, it will
 * calculate the frequency of occerence of a character in an imput file, and
 * generate a Huffman code tree. The tree is then used to create a table of the 
 * codes generated. The second time through, the encoder uses the table to 
 * compress the input data. 
 * 
 * Entropy is the average rate at which information is produced by a random 
 * source of data. Entropy can be caluculated by the summation of probability of
 * term i times the log base two of probability of term i. Average bits per 
 * symbol is the average bits to repersent a symbol. Average bits per symbol 
 * can be calculated by the sumation of probability of term i times the length
 * of the repersentive term of i. 
 *
 * Decoding will use the same Huffman codes that the encoder uses. Bits are 
 * read form the encoded file into a Huffman Tree. The Huffman Tree from the 
 * encoder will match decoder tree.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *  None.       
 *
 * @par Usage:
   @verbatim
  ./huffman -e orginalfile encodedfile
  ./huffman -d encodedfile decodedfile
  e - encode file
  d - decode file 
  orginalfile - input file not decode or encoded 
  encodedfile - file that is going to be or is encoded
  decoadedfile - output file of decoder that should match orginal file 
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * * When Decoding, Huffman Tree accesses nodes that don't exist in the tree, 
   going beyond existing nodes.  Causes all values after to be incorrect.
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/7280127/pa1/commits/master>
 
 *Please see gitlab repository</a>
 *
 *****************************************************************************/


#include "util.h"


/**************************************************************************//**
 * @author Jarod Osborn and Angus Frisch
 *
 * @par Description: Main starts the program with inputs of argc and argv. It
 * will determine and if the command line is correctly written.
 *
 * @param[in]   argc - Number of arguments. 
 * @param[in]   argv - contains the strings given to the program.
 * 
 * @returns 0    0 - Program ran correctly/
 * @returns -1  -1 - Not enough arguments or not using -e or -d.
 * @returns -2  -2 - input fiel didn't open.
 * @returns -3  -3 - output file didn't open. 
 *
 *****************************************************************************/
int main( int argc, char **argv )
{
    
    const int Chunksize = 1024;
    unsigned char buff[Chunksize];
    int i = 0, nbytes = 0, spaceCount = 0, outBytes = 0;
    float prec = 0;
    vector<char> input, simpleVect;
    vector<int> nums;
    vector<string> codes;
    vector<double> fqs;
   
   //store input/output files  
    char *inputfile = argv[2];
    char *outputfile = argv[3];
    
   // check to see if input arguments are valid
    if ( argc != 4 || ( strcmp( argv[1], "-e" ) != 0 && strcmp( argv[1], "-d" )
         !=0 ))
    {
        cout << "Usage for encoding " << argv[0]
            << " -e inputfile outputfile" << endl
            << "Usage for decoding " << argv[0]
            << " -d inputfile outputfile" << endl;

        return -1;
    }
    
    //open up files and check if opens
    ifstream fin( inputfile, ios::binary );
    ofstream fout( outputfile, ios::binary );
    
    if ( !fin )
    {
        cout << "Error: unable to open inputfile " << inputfile << endl;

        return -2;
    }

    if ( !fout )
    {
        cout << "Error: unable to open " << outputfile << endl;

        return -3;
    }

    //performs the encoder functions if needed   
    if( strcmp( argv[1], "-e" ) == 0 )
    {   
        //read in file to make hisogram
        fin.read( ( char * ) buff, Chunksize );

        while ( fin.gcount() > 0 )
        {
            nbytes += fin.gcount();
            fin.read( ( char * ) buff, Chunksize );
        }

        fin.seekg( 0, fin.beg );
    
        for( i = 0; i < nbytes; i++ )
            if( isspace( buff[i] ) )
                spaceCount++;
    
    
        cout << "Huffman Encoder Pass 1\n" << "-----------------------------\n"
            << "Read " << nbytes - spaceCount << " bytes from " << inputfile << ",";

        fin.clear();

        //performs all encoder functions to make a encoded file
        makeHistogram( buff, nbytes, input, nums );
        printHistogram( input, nums, nbytes - spaceCount, codes, fqs );
        outBytes = printHist2File( input, codes, fqs, fout );
        compress( codes, nbytes, input, fout, fin );
        pass2( outBytes, fout, outputfile );
        stats( nbytes - spaceCount, outBytes, fqs, codes );
    }

    //start the performance of the decoder if needed 
    if( strcmp( argv[1], "-d") == 0 )       
        decodeFileMain( fin, nbytes, fout );
        
    fin.clear();
    fin.close();
    fout.close();

    return 0;
}
