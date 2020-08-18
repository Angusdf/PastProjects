/**************************************************************************//**
 * @file graph.cpp
 * @brief File to be used with graph.h and structs.h
 *****************************************************************************/


#include "graph.h"
#include "structs.h"

using namespace std;

/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Reads in the given input file, Seperate movie title from 
 * actor(s) and constructs the adjacency lists. This function creates a 
 * bipartite graph that uses 2 adjacency lists. These lists are maps. The first 
 * list maps from movies to a set of actors that played in that movie. The 
 * second list maps performers to a set of movies that the performer was in. 
 *
 * @param[in,out]   fin - Input file. 
 *
 *****************************************************************************/
bool graph::constructGraph(ifstream &fin)
{
    string entry, title, actor;
    int i = 0;
    movieInfo newMovie;
    starInfo newStar;
    int starCounter = 0;
    int movieCounter = 0;
   
    //read in first entry   
    while(getline(fin,entry))
    {
       i = 0;

       	//seperates the name of the form the line 
       	while (entry[i] != '/')
       	{
           title += entry[i];
           i++;
       	} 

        //Store the title of the movie        	
	newMovie.movieName = title;

	if(movies.find(newMovie) != movies.end())
	{
	    newMovie.movieName += ' ';
	}

       	//seperate name of actors from the line 
       	for( i= title.size()+1;i<entry.size();i++)
       	{   
	    //if '/' is found, end of actor name, clear the actor variable else read in next char
            if(entry[i]=='/')
            { 
		//Store the actor name 
		newStar.name = actor;

		//Add movies and stars to adj lists
		movies[newMovie].insert( newStar );
		stars[newStar].insert( newMovie ); 
               	actor.clear();
            } 
            else
	    {
               	actor+=entry[i];
            }
	 } 

	//Add performers and movies to adj list
	newStar.name = actor;

	movies[newMovie].insert(newStar);
	stars[newStar].insert(newMovie);
       
        actor.clear();
        entry.clear();
        title.clear();    
    }
}


/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Will find the degrees of separation form actor to target. 
 * Prints out the path if found. BFS algorithm works on bipartite graph that 
 * uses 2 adj list 'stars' and 'movies'. This functon uses 2 queues to process 
 * the graph and deal with the actors and movies in the adj lists.
 *
 * @param[in]   actor  - Structure that holds the actor to find.   
 * @param[in]   target - Structure that holds the target the actor needs to 
 *                       connect to.
 * 
 *****************************************************************************/
void graph::degreesOfSeparation(starInfo actor, starInfo target)
{
    int i=0;
    queue<starInfo> sq;
    queue<movieInfo> mq;
    starInfo star, tstar;
    movieInfo movie, tmovie;
    set<movieInfo>::iterator it;
    set<starInfo>::iterator jt;
    map< starInfo, set<movieInfo> >::iterator mst;
    map< movieInfo, set<starInfo> >::iterator mmt = movies.begin();
    set<starInfo> svisited;
    set<movieInfo> mvisited; 
    bool done = false;
    	


    if (actor == target)
    {
    //Print path
    	cout << "Degrees of Separation from " << actor.name << " to " 
 	     << target.name << ": 0" << endl << endl << actor.name << endl;

    	return;
    }

    //determine if actor is in graph
    mst = stars.find(actor);

    if( mst == stars.end() )
    {
	cout << endl << "    Could not find performer named [" << actor.name 
	     << "]" << endl; 

	return;
    }

    //determine if target is in the path
    mst = stars.find( target );

    if( mst == stars.end() )
    {
	cout << endl << "    Could not find performer named [" << target.name 
	     << "]" << endl; 

	return;
    }
    
    
    target.visit = true;
    svisited.insert(target);
    target.prev = "";
    sq.push(target);


    //Run BFS
    //BFS i is degree of separtion
    for(i; !done;i++)
    {
	//First loop deals with actors to movies adj list
	while(!sq.empty())
	{	
	    star=sq.front();
	    sq.pop();
            //For each star iterate through movies they have been in and push to mq
            for( it = stars[star].begin(); it != stars[star].end(); it++ )
	    {	
		//if not visited add to queue
	    	if( mvisited.find(*it) == mvisited.end() )
	    	{
		    tmovie = *it;
		    tmovie.visit = true;
		    tmovie.prev = star;
	    	    mq.push( tmovie );
		    mvisited.insert(tmovie);
	    	}
	    }
        }

	//This loop deals with movies to actors
	while(!mq.empty())
	{
	    movie=mq.front();
	    mq.pop();

   	    //For each movie in queue, iterate through its stars and push to sq 
	    for( jt = movies[movie].begin(); !done && jt != movies[movie].end(); jt++ )
	    {
 	 	//Check if reached target
		if(*jt == actor)
		{
		    actor = *jt;
		    actor.prev = movie.movieName;
		    done = true;
		}
		//Otherwise if not visited add to queue
	    	else if(svisited.find(*jt) == svisited.end())
	    	{
		    tstar = *jt;
		    tstar.visit = true;
		    tstar.prev = movie.movieName;
		    svisited.insert( tstar );
		    sq.push( tstar );
	    	}	
	    }
        }

    	//if sq (queue for stars) is empty, then we are done
	if(sq.empty())
	{
	    done = true;
	} 
    
    }


    //Print path
    cout << "Degrees of Separation from " << actor.name << " to " 
	 << target.name << ": ";
    cout << i << endl << endl;

    while(actor.prev != "")
    {
        cout << actor.name << endl;

	tmovie.movieName = actor.prev;
	
        cout << "        " << tmovie.movieName << endl;
	cout << "    |" << endl;
	cout << "    V" << endl;

	it = mvisited.find(tmovie);
	tmovie = *it;
	actor = tmovie.prev;
	jt = svisited.find(actor);
	actor = *jt;
    } 

    cout << actor.name << endl;
    return;
}



/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Finds the degree and connectivity of an actor. It does 
 * this by preforming a breadth-first search on the graph. It then prints the
 * histogram to screen.
 *
 * @param[in]   actor  - Structure that holds the actor to find.   
 * 
 *****************************************************************************/
void graph::makeHistogram(starInfo actor)
{
    int i=0, sumOfActors=1, sumOfLength=0, count = 0, maxDegree = 0;
    queue<starInfo> sq;
    queue<movieInfo> mq;
    starInfo star, tstar;
    movieInfo movie, tmovie;
    set<movieInfo>::iterator it;
    set<starInfo>::iterator jt;
    map< starInfo, set<movieInfo> >::iterator mst;
    map< movieInfo, set<starInfo> >::iterator mmt = movies.begin();
    set<starInfo> svisited;
    set<movieInfo> mvisited;
    bool done = false;
    


    //determine if actor is in graph
    mst = stars.find(actor);

    if( mst == stars.end() )
    {
	cout << "    Could not find performer [" << actor.name <<"]" <<endl;
	return;
    }

    //mark actor as visited and push to queue
    sq.push(actor);
    svisited.insert(actor);
    
    cout << endl << "    Histogram for " << actor.name << ": " << endl; 
    cout << "\t\t#\t\tFreq" << endl;
    cout << "------------------------------------------------------" << endl; 


    //BFS algorithm
    //BFS i is degree of separtion
    for(i = 1; !done;i++)
    {
	count = 0;
	
	//for each movie, push actor that performed in it
	while(!sq.empty())
	{
	
	    star=sq.front();
	    sq.pop();
            //For each star iterate through movies they have been in and push to mq
            for(it = stars[star].begin(); it != stars[star].end(); it++)
	    {
		tmovie = *it;	
		//if not visited then add to queue
	    	if(mvisited.find(*it) == mvisited.end())
	    	{
		    tmovie.visit = true;
		    tmovie.prev = star;
	    	    mq.push(tmovie);
		    mvisited.insert(tmovie);
	    	}
	    }
        }

   	//for each star, push the movies they were in
	while(!mq.empty())
	{
	    movie=mq.front();
	    mq.pop();

   	    //For each movie in queue, iterate through its stars and push to sq 
	    for(jt = movies[movie].begin(); !done && jt != movies[movie].end(); jt++)
	    {
		tstar = *jt;
	        //if not visited then push to sq
	    	if(svisited.find(*jt) == svisited.end() && !(*jt == actor))
	    	{
		    tstar.visit = true;
		    tstar.degree = i;
		    tstar.prev = movie.movieName;
		    svisited.insert(tstar);
		    sq.push( tstar );
		    count++;
	    	}	
	    }
        }

    	//if sq is empty then we are done
	if(sq.empty())
	{
	    done = true;
	}
	
 	if(count !=0)
	{
    	    cout <<"\t\t" << i <<  "\t\t" << count << endl; 
            // keep track of actor total and their length
    	    sumOfActors+=count;
    	    sumOfLength+=i*count;
	    maxDegree = i;
	}
    }	

    cout <<"\t\t" << "inf" <<  "\t\t" << stars.size() - svisited.size() << endl; 
  
    cout << endl << "Avg path Length: " 
        << (double)sumOfLength/(double)sumOfActors<< endl;

    //Find longest shortest paths
    for(jt = svisited.begin(); jt != svisited.end(); jt++)
    {
	tstar = *jt;

	//if longest shortest path, the add to list
	if(tstar.degree >= maxDegree)
	{
    	    longestShortestPaths.insert(tstar);
	}
    }
}



/**************************************************************************//**
 * @author Dennis Kovarik and Angus Frisch
 *
 * @par Description: Finds the longest shortest paths from Bacon in the graph. 
 * It does this by preforming a breadth-first search on the graph if the set of 
 * longest shortest paths is empty. It then prints the endpoints of all the 
 * longestest-shortest paths to screen.  
 * 
 *****************************************************************************/
void graph::getLongestShortestPaths()
{
    starInfo actor;
    actor.name = "Bacon, Kevin";
    int i=0, sumOfActors=1, sumOfLength=0, count = 0, maxDegree = 0;
    queue<starInfo> sq;
    queue<movieInfo> mq;
    starInfo star, tstar;
    movieInfo movie, tmovie;
    set<movieInfo>::iterator it;
    set<starInfo>::iterator jt;
    map< starInfo, set<movieInfo> >::iterator mst;
    map< movieInfo, set<starInfo> >::iterator mmt = movies.begin();
    set<starInfo> svisited;
    set<movieInfo> mvisited;
    bool done = false;
    


    //determine if actor is in graph
    mst = stars.find(actor);

    if( mst == stars.end() )
    {
	cout << "    Could not find performer [" << actor.name <<"]" <<endl;
	return;
    }

    //mark actor as visited and push to queue
    sq.push(actor);
    svisited.insert(actor);



    //BFS algorithm
    //BFS i is degree of separtion
    if(longestShortestPaths.empty())
    {
    	for(i = 1; !done;i++)
    	{
	    count = 0;
	
	    //for each movie, push actor that performed in it
	    while(!sq.empty())
	    {
	        star=sq.front();
	        sq.pop();

                //For each star iterate through movies they have been in and push to mq
                for(it = stars[star].begin(); it != stars[star].end(); it++)
	        {
		    tmovie = *it;	
		    //if not visited then add to queue
	    	    if(mvisited.find(*it) == mvisited.end())
	    	    {
		    	tmovie.visit = true;
		    	tmovie.prev = star;
	    	    	mq.push(tmovie);
		    	mvisited.insert(tmovie);
	    	    }
	    	}
            }
	

   	    //for each star, push the movies they were in
	    while(!mq.empty())
	    {
	    	movie=mq.front();
	    	mq.pop();

   	    	//For each movie in queue, iterate through its stars and push to sq 
	    	for(jt = movies[movie].begin(); !done && jt != movies[movie].end(); jt++)
	    	{
		    tstar = *jt;
	            //if not visited then push to sq
	    	    if(svisited.find(*jt) == svisited.end() && !(*jt == actor))
	    	    {
		     	tstar.visit = true;
		    	tstar.degree = i;
		    	tstar.prev = movie.movieName;
		    	svisited.insert(tstar);
		    	sq.push( tstar );
		    	count++;
	    	    }	
	    	}
            }

    	    //if sq is empty then we are done
	    if(sq.empty())
	    {
	    	done = true;
	    }
	
 	    if(count !=0)
	    {
	    	maxDegree = i;
	    }
        }	
    }


    //Find longest shortest paths
    for(jt = svisited.begin(); jt != svisited.end(); jt++)
    {
	tstar = *jt;

	//if longest shortest path, the add to list
	if(tstar.degree >= maxDegree)
	{
    	    longestShortestPaths.insert(tstar);
	}
    }



    //Print longest shortest paths
    for(jt = longestShortestPaths.begin(); jt != longestShortestPaths.end(); jt++)
    {
	tstar = *jt;
	if(!(star == actor))
	{ 
		cout << tstar.name << endl;
	}
    }

    return;
}
