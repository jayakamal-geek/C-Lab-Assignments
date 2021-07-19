#include<iostream>
#include<string>    //header file for inbuilt library string functions.
#include<vector>    //using vector header file to manage adjacency list
#include<queue>     //using queue header file for facilitating DFS
#include<utility>   //using pair to facilitate SSP
using namespace std;    //defining name space in global scope
#define INT_MAX 2147483647  //defining individually instead of importing entire header file

/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to Represent a graph and implement BFS and SSP
*    Question : CS2810 A6Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : GraphEdge
*    Application        : Used to represent the edges of the Graph 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
template <class T> class GraphEdge
{
    public:
        int dest;   //index of destination vector
        T weight; //variable to represent the weight of the edge

        GraphEdge(int dest, T weight) //class constructor to initialise variables
        {
            this->dest = dest;  //initialising the destination
            this->weight = weight;  //initialisng the weight of the edge
        }

        bool operator < (GraphEdge G2)  //defining less than operator
        {
            if(this->weight < G2.weight)    //returning true if the constraint is satisfied
                return true;

            else if(this->weight == G2.weight)
            {
                if(this->dest < G2.dest)    //returning true if the constraint is satisfied
                    return true;
                return false;   //constraint not satisfied
            }

            else
                return false;   //default return
        }
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Graph
*    Application        : Used to represent the Graph 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
template <class T> class Graph
{
    vector<vector<GraphEdge<T>>> adjList;  // A vector of vector to implement adjacency list
    int vertexCount;    //variable to keep track of number of vectors

    public: //public methods of the class
        Graph(int vertexCount)  //class constructor
        {
            this->vertexCount = vertexCount;    //initialising vertex count
            
            for(int i=0; i<vertexCount; i++)
            {
                vector<GraphEdge<T>> tempVec;  //construct a temporary vector
                adjList.push_back(tempVec); //pushing the temporary vecor into the vector of vectors
            }
        }

        ~Graph()    //class destructor
        {
            for(int i=0; i<vertexCount; i++)    //for loop to traverse all vectors
                adjList[i].clear(); //properly destroying all the vectors

            adjList.clear();    //destroying vector of vectors
        }

        void AddV(void);    //function to add a new vertex into the graph
        void AddE(int, int, T);   //Adds a edge into the Graph
        void DelE(int, int); //deletes a given edge from the Graph
        void BFS(int);  //performs a BFS from a given vertex
        void SSP(int);  //finds shortest path to a all vertices from a given vertex

    private:    //private methods of the class
        void removeEdge(int, int);  //removes edge from adjacency list
};


                /******************** THE GRAPH CLASS FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : AddV (Graph)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function adds a new vertex into the graph
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::AddV(void)
{
    vector<GraphEdge<T>> tempVec;  //a new vector to represent the adjList of new vertex
    adjList.push_back(tempVec); //pushing the adjList into the vector of vectors
    vertexCount++;  //incrimenting the vertexCount
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : AddE (Graph)
*    Args          : 3 integers(int)(2 vertices and weight of the edge)
*    Return Type   : Nil
*    Application   : This Function adds a new edge into the graph
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::AddE(int start, int dest, T weight)
{
    if(start<vertexCount && dest<vertexCount)   //checking validity of the vertices
    {
        GraphEdge<T> tempEdge(dest, weight); //creating a new Edge
        auto tempIterator = adjList[start].begin(); //initialising the iterator
        for(; tempIterator!=adjList[start].end(); tempIterator++)   //for loop for vector traversal
        {
            if(tempEdge < *tempIterator)    //comparing elements
                break;  //breaking the loop if required value is reached
        }

        adjList[start].insert(tempIterator, tempEdge);  //adding edge at the required position

        if(start!=dest) //if start and edge are different
        {
            tempEdge.dest = start;  //changing dest to start
            tempIterator = adjList[dest].begin(); //initialising the iterator
            for(; tempIterator!=adjList[dest].end(); tempIterator++)   //for loop for vector traversal
            {
                if(tempEdge < *tempIterator)    //comparing elements
                    break;  //breaking the loop if required value is reached
            }

            adjList[dest].insert(tempIterator, tempEdge);  //adding edge at the required position
            }
    }

    else
        cerr << "INVALID INDICES" << endl;  //message into the error stream
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DelE (Graph)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the Graph
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::DelE(int start, int dest)
{
    if(start<vertexCount && dest<vertexCount)   //checking validity of the vertices
    {
        removeEdge(start, dest);    //removing edge from the adjacency list
        removeEdge(dest, start);    //removing edge from the adjacency list
    }

    else
        cerr << "INVALID INDICES" << endl;  //message into the error stream
}
/*-------------------------------------------------------------------------------------------------
*    Function Name : removeEdge (Graph)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the adjacency list
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::removeEdge(int start, int dest)
{
    for(auto i=adjList[start].cbegin(); i!=adjList[start].end(); ++i)   //for loop to find the edge
    {
        if(i->dest == dest) //if the edge is found 
        {
            adjList[start].erase(i);    //erase the edge
            break;  //break out of the loop
        }
    }    
}
/*-------------------------------------------------------------------------------------------------
*    Function Name : BFS (Graph)
*    Args          : integer(int)(start point of the BFS)
*    Return Type   : Nil
*    Application   : This Function performs a BFS from a given start point
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::BFS(int start)
{
    //cout << "HI" << endl;   //debugging Statement
    bool visitedMark[vertexCount];  //a boolean array of visited to facilitate BFS
    for(int i=0; i<vertexCount; i++)
        visitedMark[i] = false; //initially marking all vertices as unvisited

    visitedMark[start] = true;  //marking started vertex as visited
    queue<int> tempVertexList;  //creating a queue to help in DFS
    tempVertexList.push(start);    //pushing the start vertex into the queue

    while(!tempVertexList.empty())
    {
        start = tempVertexList.front(); //getting the first vertex in the list
        tempVertexList.pop();   //popping the first element in the queue

        for(auto i=adjList[start].cbegin(); i!=adjList[start].end(); ++i)
        {
            if(!visitedMark[i->dest])   //if we come across an unvisited vertex
            {
                visitedMark[i->dest] = true;    //mark the new vertex as visited
                tempVertexList.push(i->dest);  //pushing back the new visited vertex into the queue
            }
        }

        cout << start << ' ';   //printing every visited vertex
    }

    cout << endl;   //printing a new line after printing all new vertices visited in the BFS
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : SSP (Graph)
*    Args          : integer(int)(source point)
*    Return Type   : Nil
*    Application   : This Function finds the shortest path to all points from source using BFS
-------------------------------------------------------------------------------------------------*/
template<class T>
void Graph<T>::SSP(int start)
{
    pair<int, int> minDistance[vertexCount];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> distanceQueue;  //priority que with higher priority to lesser value
    for(int i=0; i<vertexCount; i++)    //for loop for initialisations
    {
        if(i==start)    //distance from point to itself is 0
            minDistance[i].first = 0;

        else    //initialising all other distances to int max
            minDistance[i].first = INT_MAX;

        minDistance[i].second = 1;  //marking that no distances have reached minimum
    }

    distanceQueue.push({0, start}); //push the start into the queue

    while(!distanceQueue.empty())   //while queue is not empty
    {
        int temp = distanceQueue.top().second;  //getting top element of priority queue
        distanceQueue.pop();    //popping out the top element
        minDistance[temp].second = 0;   //marking that this reached minimum already
        for(auto i=adjList[temp].begin(); i!=adjList[temp].end(); i++)
        {
            if(minDistance[i->dest].second) //if a distance to vertex hasnt reached minimum
            {
                if((minDistance[temp].first) + i->weight < minDistance[i->dest].first)  //if new minimum is found
                {
                    minDistance[i->dest].first = (minDistance[temp].first) + i->weight; //update the distance with new minimum
                    distanceQueue.push({minDistance[i->dest].first, i->dest});  //push it into the priority queue
                }
            }
        }
    }

    for(int i=0; i<vertexCount; i++)    //for loop to print all distances
    {
        cout << minDistance[i].first << ' ';
    }

    cout << endl;
}
                /******************** THE GRAPH CLASS FUNCTIONS END HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int vertexCount, commandCount, temp1, temp2, temp3;  //vertexCount and number of commands and temporary variables
    string command; //input Command
    cin >> vertexCount; //taking input for number of vertices

    Graph<int> G(vertexCount);   //creating a Graph

    cin >> commandCount;    //taking input for number of commands
    for(int i=0; i<commandCount; i++)   //for loop to execute commands
    {
        cin >> command; //taking string input of the command

        if(command.compare("ADDV")==0)    //comparing input instruction with defined instructions
            G.AddV();

        else if(command.compare("ADDE")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1 >> temp2 >> temp3; //taking input of necessary argument
            G.AddE(temp1, temp2, temp3);  //calling the respective function 
        }

        else if(command.compare("DELE")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1 >> temp2; //taking input of necessary argument
            G.DelE(temp1, temp2);  //calling the respective function 
        }
    }

    for(int i=0; i<2; i++)
    {
        cin >> command; //taking string input of the command
        if(command.compare("BFS")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1; //taking input of necessary argument
            G.BFS(temp1);  //calling the respective function 
        }

        else if(command.compare("SSP")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1; //taking input of necessary argument
            G.SSP(temp1);  //calling the respective function 
        }

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;
    }

    return 0;   //returning 0 to exit the program
}
