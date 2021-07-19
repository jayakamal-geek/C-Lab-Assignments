#include<iostream>
#include<string>    //header file for inbuilt library string functions.
#include<vector>    //using vector header file to manage adjacency list
#include<queue>     //for priority queue in Prims algo
using namespace std;    //defining name space in global scope
#define INT_MAX 2147483647  //defining individually instead of importing entire header file


/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to find the Minimum Spanning Tree of an undirected weighted graph
*    Question : CS2810 A7Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Edge
*    Application        : Used to represent the edges of the Graph in the adjacency list
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Edge
{
    public:
        int u, v;   //vertices between whom the edge is present
        int weight;   //weight of the edge

        Edge(int u, int v, int weight)
        {
            if(u < v)
            {
                this->u = u;    //initialising the vertex values
                this->v = v;    //initialising the vertex values
            }

            else
            {
                this->u = v;    //initialising the vertex values
                this->v = u;    //initialising the vertex values
            }

            this->weight = weight;  //initialising the weight of the edge
        }

        bool operator < (Edge E2)  //defining less than operator
        {
            if(this->weight < E2.weight)    //returning true if the constraint is satisfied
                return true;

            else if(this->weight == E2.weight)
            {
                if(this->u < E2.u)    //returning true if the constraint is satisfied
                    return true;
                return false;   //constraint not satisfied
            }

            else
                return false;   //default return
        }
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : GraphEdge
*    Application        : Used to represent the edges of the Graph in the adjacency list
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class GraphEdge
{
    public:
        int dest;   //index of destination vector
        int weight; //variable to represent the weight of the edge

        GraphEdge(int dest, int weight) //class constructor to initialise variables
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
class Graph
{
    protected:
        vector<vector<GraphEdge>> adjList;  // A vector of vector to implement adjacency list
        vector<Edge> edgeList;  //the list of all the edges in the Graph
        int vertexCount;    //variable to keep track of number of vectors

    public: //public methods of the class
        Graph(int vertexCount)
        {
            this->vertexCount = vertexCount;    //initialising vertex count

            for(int i=0; i<vertexCount; i++)
            {
                vector<GraphEdge> tempVec;  //construct a temporary vector
                adjList.push_back(tempVec); //pushing the temporary vecor into the vector of vectors
            }
        }

        //overloading all of these functions to make changes and reduce complexity of MST
        virtual void AddV(void);    //function to add a new vertex into the graph
        virtual void AddE(int, int, int);   //Adds a edge into the Graph
        virtual void DelE(int, int); //deletes a given edge from the Graph

    protected:    //private methods of the class
        void removeEdge(int, int);  //removes edge from adjacency list
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : MST
*    Application        : Used to find the minimum spanning tree
*    Inheritances       : Graph
-------------------------------------------------------------------------------------------------*/
class MST : public Graph
{
    vector<vector<GraphEdge>> minSpanTree;   //the vector to contain all the edges of the minimum spanning Tree
    vector<Edge> edgeMinSpanTreeList;  //the list of all the edges in the minimum spanning tree
    long long int costOfGraph;    //sum of weights of all edges of MST
    bool statusBit; //true when minimum spanning tree must be updated

    public:
        MST(int vertexCount) : Graph(vertexCount)   //calling Graph coonstructor along with this constructor
        {
            this->statusBit = true; //status bit saying that MST is not upto date
            for(int i=0; i<vertexCount; i++)    //vector of vectors to store adj list of MST
            {
                vector<GraphEdge> tempVec1; //construct a temporary vector
                minSpanTree.push_back(tempVec1);    //pushing the temporary vecor into the vector of vectors
            }
        }

        ~MST()  //class destructor of class MST
        {
            for(int i=0; i<vertexCount; i++)    //for loop to traverse all vectors
            {
                adjList[i].clear(); //properly destroying all the vectors
                minSpanTree[i].clear(); //properly destroying all the vectors
            }

            adjList.clear();    //destroying vector of vectors
            minSpanTree.clear();    //destroying vector of vectors
        }

        void AddV(void);    //function to add a new vertex into the graph
        void AddE(int, int, int);   //Adds a edge into the Graph
        void DelE(int, int); //deletes a given edge from the Graph
        void Prims(int);   //Creates the minimum spanning tree of a Graph
        void Kruskal(void); //Creates the minimum spanning forest of a Graph
        void TreeUpToDate(void);    //minimum spanning tree/forest is up to date or not
        void DisplayTree(void);     //prints the edges of spanning tree in ascending order of edge weight

    private:
        bool noCycle(int);  //checks if a Graph contains cycle or not
        bool dfS_helper(int, bool*, int);    //recursive helper function to detect cycles
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
    vector<GraphEdge> tempVec;  //a new vector to represent the adjList of new vertex
    adjList.push_back(tempVec); //pushing the adjList into the vector of vectors
    vertexCount++;  //incrimenting the vertexCount
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : AddE (Graph)
*    Args          : 3 integers(int)(2 vertices and weight of the edge)
*    Return Type   : Nil
*    Application   : This Function adds a new edge into the graph
-------------------------------------------------------------------------------------------------*/
void Graph::AddE(int start, int dest, int weight)
{
    if(start<vertexCount && dest<vertexCount)   //checking validity of the vertices
    {
        GraphEdge tempEdge(dest, weight); //creating a new Edge
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
void Graph::DelE(int start, int dest)
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
void Graph::removeEdge(int start, int dest)
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

                /******************** THE GRAPH CLASS FUNCTIONS END HERE ********************/

/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/

                /******************** THE MST CLASS FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : AddV (MST)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function adds a new vertex into the graph
-------------------------------------------------------------------------------------------------*/
void MST::AddV(void)
{
    vector<GraphEdge> tempVec;  //a new vector to represent the adjList of new vertex
    vector<GraphEdge> tempVec1;  //a new vector to represent the adjList of new vertex
    statusBit = true;
    adjList.push_back(tempVec); //pushing the adjList into the vector of vectors
    minSpanTree.push_back(tempVec1);    //pushing the adjList into vector of lists
    vertexCount++;  //incrimenting the vertexCount
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : AddE (MST)
*    Args          : 3 integers(int)(2 vertices and weight of the edge)
*    Return Type   : Nil
*    Application   : This Function adds a new edge into the graph
-------------------------------------------------------------------------------------------------*/
void MST::AddE(int start, int dest, int weight)
{
    if(start<vertexCount && dest<vertexCount)   //checking validity of the vertices
    {
        GraphEdge tempEdge(dest, weight); //creating a new Edge
        Edge tempEdge1(start, dest, weight); //creating an edge
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

        auto tempIterator1 = edgeList.begin();  //initialising an iterator
        for(; tempIterator1!=edgeList.end(); tempIterator1++)   //for loop for traversal
        {
            if(tempEdge1 < *tempIterator1)    //comparing elements
                break;  //breaking the loop if required value is reached
        }

        edgeList.insert(tempIterator1, tempEdge1);  //inserting the new edge into list of edges
        statusBit = true;   //the MST is not up to date
    }

    else
        cerr << "INVALID INDICES" << endl;  //message into the error stream
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DelE (MST)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the Graph
-------------------------------------------------------------------------------------------------*/
void MST::DelE(int start, int dest)
{
    if(start<vertexCount && dest<vertexCount)   //checking validity of the vertices
    {
        removeEdge(start, dest);    //removing edge from the adjacency list
        removeEdge(dest, start);    //removing edge from the adjacency list
        statusBit = true;   //the MST is not up to date

        for(auto i=edgeList.cbegin(); i!=edgeList.end(); ++i)   //for loop to find the edge
        {
            if(i->u == start && i->v == dest) //if the edge is found 
            {
                edgeList.erase(i);    //erase the edge
                break;  //break out of the loop
            }
        }    
    }

    else
        cerr << "INVALID INDICES" << endl;  //message into the error stream
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : TreeUpToDate (MST)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function prints whether the tree is upto date or not
-------------------------------------------------------------------------------------------------*/
void MST::TreeUpToDate(void)
{
    if(statusBit)   //if tree is not up to date
        cout << "NO" << endl;   //print no

    else    //if tree is up to date 
        cout << "YES" << endl;  //print yes
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DisplayTree (MST)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function prints the minimum spanning tree
-------------------------------------------------------------------------------------------------*/
void MST::DisplayTree(void)
{
    for(auto tempIterator=edgeMinSpanTreeList.begin(); tempIterator!=edgeMinSpanTreeList.end(); tempIterator++)  //for loop to traverse across all edges
        cout << tempIterator->u << " " << tempIterator->v << " " << tempIterator->weight << endl;   //printing edges
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : Kruskal (MST)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function creates minimum spanning forest of a Graph and prints cost
-------------------------------------------------------------------------------------------------*/
void MST::Kruskal(void)
{
    if(statusBit)   //do the process only if MST is not up to date
    {
        costOfGraph = 0;    //reset the value to 0
        for(int i=0; i<vertexCount; i++)
            minSpanTree[i].clear(); //clearing all edges in adjlist of MST
        edgeMinSpanTreeList.clear();    //clearing all edges in the MST edge list

        for(auto i=edgeList.begin(); i!=edgeList.end(); i++)
        {
            GraphEdge tempEdge(i->v, i->weight);
            minSpanTree[i->u].push_back(tempEdge);  //push edge into adj list of MST
            tempEdge.dest = i->u;
            minSpanTree[i->v].push_back(tempEdge);  //push edge into adj list of MST

            if(noCycle(i->u) && (i->u)!=(i->v))
            {
                costOfGraph = costOfGraph + i->weight;  //updating the sum of weights of edges of MST
                edgeMinSpanTreeList.push_back(*i);  //add the edge to the MST
            }

            else
            {
                minSpanTree[i->u].pop_back();  //pop edge if it forms a cycle 
                tempEdge.dest = i->u;
                minSpanTree[i->v].pop_back();  //pop edge if it forms a cycle 
            }
        }
    }

    statusBit = false;  //saying that the MST is just updated
    cout << costOfGraph << endl;    //printing sum of all weights of minimum spanning tree
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : noCycle (MST)
*    Args          : 1 integer(1 vertex of the edge)
*    Return Type   : boolean
*    Application   : This Function returns true if no cycles exist upon adding this edge
-------------------------------------------------------------------------------------------------*/
bool MST::noCycle(int u)
{
    bool visitedMark[vertexCount];  //mark to know if a vertex is visited or not
    for(int i=0; i<vertexCount; i++)    //initialising all values
        visitedMark[i] = false;

    bool flag = dfS_helper(u, visitedMark, u);  //calling a recursive DFS function to check for cycles
    return (!flag);
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : dfs_helper (MST)
*    Args          : 2 integers(vertices of the edge) and a boolean array
*    Return Type   : boolean
*    Application   : This Function is recurssive and helps noCycle function using DFS
-------------------------------------------------------------------------------------------------*/
bool MST::dfS_helper(int start, bool* visited, int parent)
{
    visited[start] = true;  //marking the start vertex as visited
    bool flag = false;  //initialising the return variable to false

    for(auto i=minSpanTree[start].begin();i!=minSpanTree[start].end(); i++)    //for loop to traverse across all vertices
    {
        if(!flag)
        {
            if(i->dest != parent)    //if edge exists and its not the parent
            {
                if(visited[i->dest])  //if reached an already visited vertex then cycle exists
                    return true;    //returning true
                
                flag = dfS_helper(i->dest, visited, start);   //calling next recurssion
            }
        }
    }

    return flag;    //returning the flag variable
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : Prims (MST)
*    Args          : integer(int)(start vertex)
*    Return Type   : Nil
*    Application   : This Function creates minimum spanning forest of a Graph and prints cost
-------------------------------------------------------------------------------------------------*/
void MST::Prims(int start)
{
    if(start < 0 || start >= vertexCount)   //if an invalid vertex is entered 
    {
        cerr << "INVALID INDEX" << endl;    //print output to the error stream
        return;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> vertexQueue;  //priority que with higher priority to lesser value
    bool vertexStatus[vertexCount]; //boolean value to know if the vertex is included already or not
    costOfGraph = 0;    //reset the value to 0
    for(int i=0; i<vertexCount; i++)    //clearing all data from previous run
        minSpanTree[i].clear(); //clearing all edges in adjlist of MST

    edgeMinSpanTreeList.clear();    //clearing all edges in the MST edge list

    int vertexKey[vertexCount], MSTParent[vertexCount]; //the edge weight and parent vertex
    for(int i=0; i<vertexCount; i++)    //initialising all the keyvalues
    {
        if(i==start)    //initialising the key value of start vertex to 0
            vertexKey[i] = 0;

        else    //initialising all other key values to INT_MAX
            vertexKey[i] = INT_MAX;
        
        vertexStatus[i] = false;    //marking all vertices as not included
    }

    vertexQueue.push({0, start});   //pushing start into the the priority queue //pushing the start vertex into the heap

    while(!vertexQueue.empty()) //iterating as long the minheap is no empty
    {
        int temp = vertexQueue.top().second;    //getting and popping out the top vertex as it is the current minimum
        vertexStatus[temp] = true;  //marking this vertex as included
        vertexQueue.pop();

        for(auto i=adjList[temp].begin(); i!=adjList[temp].end(); i++)  //traversing the adjacency list of popped out vertex
        {
            int tempVertex = i->dest;
            int tempW = i->weight;

            if(vertexKey[tempVertex] > tempW && !vertexStatus[tempVertex])  //if the adjacent vertex of popped out vertex hasn't reached min and not added
            {
                vertexKey[tempVertex] = tempW;  //update all the values (key and parent)
                vertexQueue.push({tempW, tempVertex});  //push the edge into minHeap
                MSTParent[tempVertex] = temp;
            }
        }
    } 

    for(int i=0; i<vertexCount; i++)    //for loop traversing all edges
    {
        if(i!=start)    //if not the start vertex
        {
            GraphEdge tempEdge(i, vertexKey[i]);
            Edge tempEdge1(i, MSTParent[i], vertexKey[i]);
            minSpanTree[MSTParent[i]].push_back(tempEdge);  //add the edge to adjacency lists of MST
            tempEdge.dest = MSTParent[i];
            minSpanTree[i].push_back(tempEdge);  //add the edge to adjacency lists of MST

            auto tempIterator1 = edgeMinSpanTreeList.begin();  //initialising an iterator
            for(; tempIterator1!=edgeMinSpanTreeList.end(); tempIterator1++)   //for loop for traversal
            {
                if(tempEdge1 < *tempIterator1)    //comparing elements
                    break;  //breaking the loop if required value is reached
            }

            edgeMinSpanTreeList.insert(tempIterator1, tempEdge1);  //inserting the new edge into list of edges
        }

        costOfGraph = costOfGraph + vertexKey[i];   //finding the sum of the weights of the MST edges 
    }

    statusBit = false;  //saying that the MST is just updated
    cout << costOfGraph << endl;    //printing sum of all weights of minimum spanning tree
}
                /******************** THE MST CLASS FUNCTIONS END HERE ********************/


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

    MST G(vertexCount);   //creating a Graph

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

        else if(command.compare("DisplayTree")==0)    //comparing input instruction with defined instructions
            G.DisplayTree();  //calling the respective function 

        else if(command.compare("TreeUptodate")==0)
            G.TreeUpToDate();   //calling the respective function

        else if(command.compare("Kruskal")==0)
            G.Kruskal();   //calling the respective function

        else if(command.compare("Prims")==0)
        {
            cin >> temp1; //taking input of necessary argument
            G.Prims(temp1);   //calling the respective function
        }

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;
    }

    return 0;   //returning 0 to exit the program
}