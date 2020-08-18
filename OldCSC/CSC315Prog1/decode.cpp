#include "util.h"

/**************************************************************************//**
 * @author Angus Frish
 *
 * @par Description: Reads in the inputfile and is the amin function that starts
 *              the decoder process
 *
 * @param[in,out]  fin - input file
 * @param[in]      nBytes - number of input bytes
 * @param[in,out]  fout - output file
 *
 *****************************************************************************/
void decodeFileMain(ifstream& fin,  int nBytes, ofstream& fout)
{
    const int Chunksize =1024;
    int i=0, tempnum;
    unsigned char enFile[Chunksize];
    unsigned char histo[Chunksize];
    vector<char > usedChar;
    vector<double> freq;
    vector<treenode*> v1;
    vector<string> codes;
    string code = "", found = "", temp = "";
    treenode * root = new (nothrow) treenode;
    
    usedChar.clear();
    freq.clear();
    fin >> tempnum;
    //cout << endl<<tempnum<<endl;
    fin.seekg(102,fin.beg);
    
    fin.read( ( char * ) histo, Chunksize );
        while ( fin.gcount() > 0 && fin.tellg()<=tempnum )
        {
        
           nBytes += fin.gcount();
           fin.read( ( char * ) histo, Chunksize );
           
    }
    fin.clear();
    fin.seekg(0,fin.beg);
    
    sepHist( histo,  enFile,  nBytes, usedChar, freq);
    
    makeTree (  v1, root, usedChar,  freq );
    for( i = 0; i < usedChar.size(); i++)
    {
        searchTree( root, code, temp, usedChar.at( i ), false);
        codes.push_back( temp );
    }
    
    decodefile(root, enFile, fin, fout);
}
    
/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Seperates histogram and encoded file 
 *
 * @param[in,out] histo - holdes the histogram
 * @param [in,out] enFile -Holds the input files , 
 * @param [in,out] nBytes - number of bytes in file
 * @param [in,out] usedChar - char used in file 
 * @param [in,out] freq - holds the frequencies
 * 
 * 
 *
 *****************************************************************************/
void sepHist(unsigned char* histo, unsigned char* enFile, int &nBytes,
 vector<char>& usedChar, vector<double>& freq)
{

    int i,j,k=0, l=0,m=0;    
    unsigned char numfeq[1024];
    
    
    for( i=0;i<nBytes;i++)
    { 
    if(isprint(histo[i]))
       { 
        if(isalpha(histo[i]))
            {
               usedChar.push_back(histo[i]);
               l=0;
               for(j=i;j<i+23;j++)
                if(isdigit(histo[j]))
                   {
                   numfeq[l]=histo[j];
                   l++;
                   }
                numfeq[l]='\0';
                freq.push_back(atof((const char *)numfeq));    
                k++;    
             }
         } 
      
    } 
}
/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Seperates histogram and encoded file 
 *
 * @param [in,out] root - Parent to tree
 * @param [in,out] enFile -Holds the input files , 
 * @param [in,out] fin - input file
 * @param [in,out] fout - output file
 * 
 * 
 *
 *****************************************************************************/
void decodefile(treenode *root, unsigned char* enFile, ifstream& fin, ofstream& fout)
{   
    int size = strlen((const char *)enFile);
     int histsize=0;
    unsigned char buff;
    int end=0, i=0,j=0, k=0, len=0;
    unsigned char mask = 0b10000000, tempmask=mask, tempans=mask;
    treenode *temp=root;
    unsigned char check;
    char leaf = '\0';
    string binCheck,leafPath="";
    string allCode, fullCode = "";
    
    allCode.clear();
    

    fin.seekg(0,fin.end);
    end=fin.tellg();
   
    fin.clear();
    fout.clear();
    fin.seekg(279,fin.beg);
   
    while (fin.read((char *) &buff,sizeof(char)))
        allCode+=buff;
    cout << allCode<<endl;
    
   for(i=0; i<sizeof(allCode)-1;i++)
    {
        check = allCode.at(i);
        
        uint2String((unsigned int)check, binCheck);
        fullCode += binCheck;
        
        binCheck = "";
       }
        //cout << fullCode << endl;
   
   while(fullCode != "")
   {
       searchTree(root,"", fullCode, leaf, false);
   
       fout << leaf << endl;
       searchTree(root,"",leafPath,leaf,false);
       leaf = '\0';
       reverse(fullCode.begin(),fullCode.end());
       for(i = 0; i < leafPath.size();i++)
           fullCode.pop_back();
       reverse(fullCode.begin(),fullCode.end());
       
   
   }           
    cout<< endl;

}
