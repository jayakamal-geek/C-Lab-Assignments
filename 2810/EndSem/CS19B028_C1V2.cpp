#include<iostream>
#include<vector>    //including vector for making adjacency list
#include<queue> //adding queue to use priority queue
using namespace std;    //defining name space in global scope


/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP program to find the minimum cover of an undirected Graph
*    Question : CS2810 EndSem C1V2
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Graph
*    Application        : Used to represent the Graph 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Graph
{
    int vertexCount, edgeCount; //variables to store the number of vertices and edges of the graph
    vector< vector<int> > adjList;  //vector of vectors to maintain adjacency list of the Graph
    vector<int> degree; //vector to store degree of all vertices

    public: //all the public functions under this label
        Graph(int numVertices)    //class constructor of the class
        {
            this->vertexCount = numVertices;    //initialising the instance variables of an object 
            this->edgeCount = 0;    //initially making the number of edges 0

            for(int i=0; i<vertexCount; i++)
            {
                vector<int> tempVec;  //construct a temporary vector
                adjList.push_back(tempVec); //pushing the temporary vecor into the vector of vectors
                degree.push_back(0);    //initialising all degrees to 0
            }
        }

        ~Graph()    //class destructor to prevent memory leaks
        {
            for(int i=0; i<vertexCount; i++)    //for loop to traverse all vectors
                adjList[i].clear(); //properly destroying all the vectors

            adjList.clear();    //destroying vector of vectors
            degree.clear();    //destroying vector of vectors
        }

        void AddV(void);    //function to add a new vertex into the graph
        void AddE(int, int);   //Adds a edge into the Graph
        void DelE(int, int); //deletes a given edge from the Graph
        int cover(void);    //finds the minimum cover of the vertices of the given Graph

    private:    //private function of the class
        void removeEdge(int, int);  //removes one node from the adjacency list 
};


                /******************** THE GRAPH CLASS FUNCTIONS BEGIN HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : AddV (Graph)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function adds a new vertex into the graph
-------------------------------------------------------------------------------------------------*/
void Graph::AddV(void)
{
    vector<int> tempVec;  //a new vector to represent the adjList of new vertex
    adjList.push_back(tempVec); //pushing the adjList into the vector of vectors
    degree.push_back(0);    //adding space for the degree of new vertex
    vertexCount++;  //incrimenting the vertexCount
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : AddE (Graph)
*    Args          : 2 integers(int)(2 vertices and weight of the edge)
*    Return Type   : Nil
*    Application   : This Function adds a new edge into the graph
-------------------------------------------------------------------------------------------------*/
void Graph::AddE(int u, int v)
{
    adjList[u].push_back(v);    //adding v to the adjacency list of u
    degree[u]++;    //incrimenting the degree of vertex u

    if(u!=v)
    {
        adjList[v].push_back(u);    //adding u to the adjacency list of v
        degree[v]++;    //incrimenting the degree of vertex v
    }
    edgeCount++;    //incrimenting the count of edges in the Graph
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DelE (Graph)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the Graph
-------------------------------------------------------------------------------------------------*/
void Graph::DelE(int start, int dest)
{

    removeEdge(start, dest);    //removing edge from the adjacency list

    if(start!=dest)
        removeEdge(dest, start);    //removing edge from the adjacency list

    edgeCount--;    //decrimenting the number of edges
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : removeEdge (Graph)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the adjacency list
-------------------------------------------------------------------------------------------------*/
void Graph::removeEdge(int start, int dest)
{
    for(auto i=adjList[start].cbegin(); i!=adjList[start].end(); ++i)   //for loop to find the edge
    {
        if(*i == dest) //if the edge is found 
        {
            adjList[start].erase(i);    //erase the edge
            break;  //break out of the loop
        }
    }
    degree[start]--;    //decrimenting the degree of the vertex
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : cover (Graph)
*    Args          : Nil
*    Return Type   : int
*    Application   : This Function returns the number of vertices in the minimum cover of graph
-------------------------------------------------------------------------------------------------*/
int Graph::cover()
{
    bool markVisited[vertexCount] = {0};    //boolean pointer marking all vertices as not visited
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> degHeap;    //min heap used to minimise the cover of the vertices of the Graph
    int cover = 0;  //variable for counting the number of vertices in the cover

    for(int i=0; i<vertexCount; i++)    //for loop to go across all the edges to find the cover of the Graph
    {
        if(!markVisited[i])
        {
            for(auto j = adjList[i].begin(); j!=adjList[i].end(); j++)
            {
                if(!markVisited[*j])
                {
                    markVisited[i]  = true; //marking the vertices as visited
                    markVisited[*j] = true; //marking the vertices as visited
                    break;  //breaking the loop after one unvisited vertex is found
                }
            }
        }

        degHeap.push(make_pair(degree[i], i));   //pushing vertex degree into heap
    }

    while(!degHeap.empty()) //minimising the cover of the verices of the Graph
    {
        int i = degHeap.top().second;   //getting the vertex with minimum degree
        degHeap.pop();  //popping out the top element

        if(markVisited[i])  //if a vertex is visited
        {
            bool flag = true;   //flag bit to check is all adacent vertices are included or not
            for(auto j = adjList[i].begin(); j!=adjList[i].end(); j++)
                flag = markVisited[*j] && flag; //and all its adjacent vertices are visited

            markVisited[i] = !flag; //updating the value of the visited value
        }
    }

    for(int i=0; i<vertexCount; i++)    //counting the number of visited vertices
    {
        if(markVisited[i])
            cover++;    //incrimenting the number of vertices in the cover 
    }

    return cover;   //returning the number of vertices in minmum cover
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
    int numVertices, numEdges;  //defining the variables to store edges and vertices count
    int u, v;   //temporary vertices to initialise the graph
    cin >> numVertices >> numEdges; //taking in the inputs of edges and vertiex counts
    Graph G(numVertices);   //creating a graph with the given number of vertices and edges

    for(int i=0; i<numEdges; i++)   //for loop running to take input of all the edges
    {
        cin >> u >> v;  //taking input for ends of an edge
        G.AddE(u-1, v-1);   //adding the edge to the Graph
    }

    cout << G.cover() << "\n";  //printing the output of the minimum cover
    return 0;   //returning 0 to exit the code
}