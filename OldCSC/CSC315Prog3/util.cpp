/**************************************************************************//**
 * @file util.cpp
 * @brief File to be used with util.h
 *****************************************************************************/

#include "util.h"

/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Open the files. Read the files into to vectors, and make
 *sure that the information is vaild.
 *
 * @param[in]       argv - contains the strings given to the program.
 * @param[in,out]   toVisit - lsit of all the cities to visit.
 * @param[in,out]   cord - lsit of structures of cities in the toVist, with 
 *                         their coordinates.
 * 
 * @returns true   - Files open correctly, files valid, visited cities 
 *                   valid.
 * @returns false  -Files didn't open, invalid file, invalid visit city.
 * 
 *****************************************************************************/
bool openFiles(char *argv[],vector<string>& toVisit, vector<cityInfo>& cord)
{
    ifstream cities2Vist, listOfCities;
    
    cities2Vist.open(argv[2]);
    listOfCities.open(argv[1]);
    
    if ( !cities2Vist.is_open() )
     {
        cout << "Cities to vist did not open"<<endl;
        cities2Vist.close();
        listOfCities.close();
        return false;
     }

    if ( !listOfCities.is_open() )
     {
        cout << "Cities Information did not open"<<endl;
        cities2Vist.close();
        listOfCities.close();

        return false;
     }
    readVisitCities(toVisit, cities2Vist);
    readCitiesInfo( toVisit, listOfCities, cord);
    
    if( checkIfValCity( toVisit, cord) == false && toVisit.size() <= 2)
    {
        cout << "One of the visit cities is invald and to few cities to visit" 
             << endl;
        cities2Vist.close();
        listOfCities.close();

        return false;
    }
    
    if (toVisit.size() <= 2)
    {
        cout << "Not enough cities to visit, must be three or greater" << endl;
        cities2Vist.close();
        listOfCities.close();

        return false;
    }
    
    if( checkIfValCity( toVisit, cord) == false )
    {
        cout << "One of the visit cities is invald" << endl;
        cities2Vist.close();
        listOfCities.close();

        return false;
    }    
    cities2Vist.close();
    listOfCities.close();
    
    return true;

}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Read from the visit file into a vector. 
 *
 * @param[in,out]   toVisit - list of all the cities to visit.
 * @param[in,out]   fin     - visted cities file.
 * 
 * 
 *****************************************************************************/
void readVisitCities(vector<string>& toVisit, ifstream& fin)
{
    string temp = "";
    int i = 0;
    
    //read in all cities 
    while (getline(fin,temp))
       {
            toVisit.push_back( temp );
            i++;      
       }
      
    displayVisit(toVisit);    
}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Read only desired cities form the city data base file into
 * a structure with coordinates. Each structure is then stored into a vector
 * screen
 *
 * @param[in]       toVisit - list of all the cities to visit.
 * @param[in,out]   cord    - lsit of all the cities to visit, with their 
 *                            coordinates.
 * @param[in,out]   fin     - file contains coordinates and city name.
 * 
 * 
 *****************************************************************************/
void readCitiesInfo(vector<string> toVisit, ifstream& fin, 
                    vector<cityInfo>& cord)
{
    cityInfo temp;
    double latitude = 0.0;
    double longitude = 0.0;
    string name;
    int i = 0, j=0;
 
    //read till end of file
    while (fin >> latitude)
    {
        fin.seekg(1,fin.cur);
        fin >> longitude;
        fin.seekg(1,fin.cur);  
        getline(fin,name);
    
        //check to see if the city is in the visited list       
        for (i = 0; i < toVisit.size(); i++)
        {
            //store if the input is being visited
            if ( name == toVisit[i] )
            {
                latitude=latitude/1000*(M_PI/180);
                longitude=longitude/1000*(M_PI/180);
                temp.name=name;
                temp.latitude = latitude;
                temp.longitude = longitude;
                cord.push_back( temp );
            }
        
        } 
      
      
    } 
 /*   //Just of testing 
    cout << setprecision(4)<<fixed;
for (i =0; i<cord.size();i++)
cout<< "City: " << cord[i].name << setw(15)<<"Latitude: " << cord[i].latitude 
    << setw(20) << "Longitude: " << cord[i].longitude<<endl;

*/

}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Open the files. Read the files into to vectors, and make
 *sure that the information is vaild.
 *
 * @param[in]   toVisit - lsit of all the cities to visit.
 * @param[in]   cord - lsit of structures of cities in the toVist, with 
 *                     their coordinates.
 * 
 * @returns true  - all cities are valid.
 * @returns false - one of the citeis is invalid 
 * 
 *****************************************************************************/
bool checkIfValCity(vector<string> toVisit, vector<cityInfo> cord)
{
    int i = 0;
   //if the vectors have the same length than they are equal
    if(toVisit.size() == cord.size())
    {
        
        return true;
    }      

    return false;

    //could try to find which one if we feel like it but i feel like it meets the req


}


/**************************************************************************//**
 * @author Levi Bergevin
 *
 * @par Description: Creates 2D array that stores adjacency matrix.
 *
 * @param[in]   
 * @param[in]   
 * 
 * 
 *****************************************************************************/
void adjacencyMatrix(vector<cityInfo> cities, double adjMatrix[][1000])
{
    int r, c;
    double dlon =0;
    double dlat = 0;

    double a = 0;
    double b = 0;
    double d = 0;
    for (r = 0; r < cities.size(); r++)
    {
	    for (c = 0; c < cities.size(); c++)
	    {
		    if (r == c)
		    {
			    adjMatrix[r][c] = 0;
		    }
		    else
		    {
			    dlon = cities[c].longitude -cities[r].longitude;
			    dlat = cities[c].latitude -cities[r].latitude;
			    a = (sin(dlat/2.0))*(sin(dlat/2.0)) + cos(cities[r].latitude) *
				    cos(cities[c].latitude) * sin(dlon/2.0)*sin(dlon/2.0);
			    b = 2 * atan2( sqrt(a), sqrt(1-a) );
			    d = 6373 * b;
			    adjMatrix[r][c] = d;
		    }
	    }
    }
}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Brute Forxe path will calculate all the possible pathes
 *but only displays the path with least distance.
 *
 * @param[in]   startIndex - The start city index in the adjMatrix, choosen by
 *                           the user.
 * @param[in]   cities     - lsit of structures of cities in the toVist, with 
 *                           their coordinates.
 * @param[in]   adjMatrix  - adjacency matrix of cities.
 * 
 * 
 *****************************************************************************/
void bruteForcePath(int startIndex, vector<cityInfo> cities, 
                    double adjMatrix[][1000])
{
    vector<int> vert;
    int i=0, k;
    double cur=0, cost=0;
    double max=999999999999999999.9;
    vector<int> shortp, temp;
    
    //record cities that are not the start 
    for(i=0; i< cities.size();i++)
        if( i != startIndex)
            vert.push_back(i);

    
    //calculate all paths    
    do{
        cur=0;
        
        k=startIndex;
        //add distances 
        for (i=0;i<vert.size();i++)
        {
            cur+=adjMatrix[k][vert[i]];
            k=vert[i];
            temp.push_back(vert[i]);
        }
        cur+= adjMatrix[k][startIndex];
        
        //determine if it is shorer than the last known path
        if(max>cur)
        {
            shortp=temp;
            max=cur;
        }
        
        temp.clear();
        }while(next_permutation(vert.begin(),vert.end()));
        
        //add start to first visist, and add end to start    
         
        shortp.insert(shortp.begin(),startIndex);
        shortp.push_back(startIndex);
        
       
        //display shortest path    
        cout << endl << endl;
        for(i=0;i<shortp.size();i++)
        {
            
            cout<< cities[shortp[i]].name;   
            if (i+1<shortp.size())
            {
                cout << " --> ";
                cost+=adjMatrix[shortp[i]][shortp[i+1]];
           }
        }   
       
        
        //display the cost
        cout << setprecision(3) << fixed<< endl;
        cout <<endl<<"Shortest Path: " << cost << endl;


}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Rest variables to make repeating program possible.
 *
 * @param[in,out]   again - determines if the program will run again.   
 * @param[in,out]   found - flag that determines if user input is valid.
 * @param[in,out]   cord  - vector of stuctures that hold city info.
 * @param[in]       toVisit - list of cities to vist
 * 
 * 
 *****************************************************************************/
void resetVar( string& again, bool& found, vector<cityInfo>& cord, 
               vector<string> toVisit )
{
    int i = 0;
    
    //reset all varibles 
    again = " ";
    found = false;
    
    for (i =0; i<cord.size(); i++)
        {
            cord[i].start = false;
        }
    // displays the cities to visit
    displayVisit(toVisit);


}



/**************************************************************************//**
 * @author Angus Frisch
 *
 * @par Description: Display cities to visit
 *
 * @param[in]       toVisit - list of cities to vist
 * 
 * 
 *****************************************************************************/
void displayVisit(vector<string> toVisit)
{
    int i = 0;   
    cout << endl << "Cities to Visit: " << endl << endl;
    
    while (i<toVisit.size())
    {
        cout<<toVisit[i]<<endl;
        i++;
    }
    
    cout << endl;

}
/**************************************************************************//*
* @author Levi Bergevin
*
* @par Description: Finds best path line by line in a 2D array. Storing a 0
* in any spot used already or a path that doesn't exist.
*
* @param[in]            cities- holds the cities 
* @param[in]            adjMatrix - holds adjacency matrix of distance
* @param[in]            start_index - used to hold location of prim value
*
******************************************************************************/
void prim(vector<cityInfo> cities, double adjMatrix[][1000], int start_index )
{
    //double temp[1000][1000];
    int min_index = 0;
    int row = start_index;
    double sum = 0;
   // vector<double>pri;
    int used[1000]= {0};
    vector <int> route;
   
    used[row] = 1;
    route.push_back(row);
    
    //copy( cities, adjMatrix, temp );
    for(int i = 0; i < cities.size(); i++)
    {
        min_index = 0;
	for(int j = 0; j < cities.size(); j++)
	{
            if(adjMatrix[row][j] != 0)												    {
	   	    if((adjMatrix[row][j] < adjMatrix[row][min_index]) || 
				    adjMatrix[row][min_index] == 0)
		    {
			if (used[j] < 2 )
			{
			    min_index = j;
			}
		    }
		    else if(used[min_index] == 2)
		    {
			min_index = j;
		    }

	    }

	}
	if (i == (cities.size() -1))
	{
	    min_index = start_index;
	}

	used[min_index]++;
	used[row]++;
	sum = sum + adjMatrix[row][min_index];
	route.push_back(min_index);
        row = min_index;

    }
    
    //display shortest path
    //print(cities, adjMatrix);

    displayResult(cities, route, sum, start_index);
}
/**************************************************************************//*
* @author Levi Bergevin
*
* @par Description: Displays results of hamilton circuit.
*
* @param[in]            cities- holds the cities
* @param[in]            route - holds direction to use for
* @param[in]            sum - total 
* @param[in]            start_index - holds prim lowest value for row
*
******************************************************************************/
void displayResult(vector<cityInfo> &cities, vector<int> route, double sum, 
		int start_index)
{
      int i;

      cout << endl << cities[route[0]].name;
      for(i = 1; i < route.size(); i++)
      { 
	  cout << " --> " << cities[route[i]].name;
      }
      cout << endl << endl <<  "Shortest path: " << sum << endl << endl;
}
/**************************************************************************//*
* @author Levi Bergevin
*
* @par Description: Finds city of the path found in other functions
*
* @param[in]            target- target city
* @param[in]            route - holds direction to use for target city
*
* @returns 0  - if route not found
* @returns i+1 - When some route is found.
******************************************************************************/
int find(int target, vector<int> route)
{
    int i = 0;
    for (i = 0; i < route.size(); i+=2)
    {
	if (route[i] == target)
	{
	    return route[i+1];
	}
    }
    cout << "something went wrong";
    return 0;
}
/**************************************************************************//*
* @author Levi Bergevin
*
* @par Description: Prints cities.
*
* @param[in]            cities- holds the cities
* @param[in]            adjMatrix - holds adjacency matrix of distance
*
******************************************************************************/
void print( vector <cityInfo> cities, double adjMatrix[][1000] )
{
    cout << "          ";
    for (int i = 0; i < cities.size(); i++)
    {
	cout << setw(10) << cities[i].name.substr(0,5);
    }

    cout << endl;

    for(int i = 0; i<cities.size(); i++)
    {
	cout << setw(10) << cities[i].name.substr(0,5);
        for(int j = 0; j<cities.size(); j++)
	{
	    cout << setw(10) << adjMatrix[i][j];
	}
	cout << endl;
    }
}
