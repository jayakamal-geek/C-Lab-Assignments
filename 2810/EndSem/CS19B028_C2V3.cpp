#include<iostream>
#include<string>    //header file for inbuilt library string functions.
using namespace std;    //defining name space in global scope

/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP program to manage and operate graphs
*    Question : CS2810 EndSem C2V3
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Graph
*    Application        : Used to represent a undirected nonweighted graph
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Graph
{
    int** adjMatrix;    //double pointer to store adjacency matrix of the Graph
    int vertexCount, edgeCount; //variables to store vertex and edge count

    public:
        Graph(int numVertices)  //class destructor for initialisng the variables
        {
            this->vertexCount = numVertices;    //initialising the instance variable
            this->edgeCount = 0;    //marking number of edges initially as 0

            adjMatrix = new int*[numVertices];  //allocating heap memory for the matrix
            for(int i=0; i<vertexCount; i++)
            {
                adjMatrix[i] = new int[vertexCount];    //allocating heap memory for the matrix
                for(int j=0; j<vertexCount; j++)
                    adjMatrix[i][j] = 0;    //initialising all elements to 0
            }
        }

        ~Graph()    //class destructor
        {
            for(int i=0; i<vertexCount; i++)
                delete[] adjMatrix[i];  //deallocating allotted heap memory
            delete[] adjMatrix; //deallocating allotted heap memory
            adjMatrix = NULL;   //null initialisation to prevent stray pointing
        }

        void addE(int, int);    //graph function to add edges to a graph
        void delE(int, int);    //graph function to delete edges of a graph
        Graph* operator +(Graph&); //returns the Graph of (this U G)
        Graph* operator -(Graph&); //returns the Graph of (this - (this n G))
        Graph* operator %(Graph&); //returns the Graph of symmetric difference of this and G
        int LexicographicProduct(Graph&);   //returns the lexicographic product of the 2 Graphs
        int edges(void);    //returns the number of edges of the Graph
};

                /******************** THE GRAPH CLASS FUNCTIONS BEGIN HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : addE (Graph)
*    Args          : 2 integers(int)(2 vertices and weight of the edge)
*    Return Type   : Nil
*    Application   : This Function adds a new edge into the graph
-------------------------------------------------------------------------------------------------*/
void Graph::addE(int u, int v)
{
    adjMatrix[u][v] = 1;    //marking that there exits an edge between u and v
    adjMatrix[v][u] = 1;    //marking that there exits an edge between u and v
    edgeCount++;    //incrimenting the number of edges
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : delE (Graph)
*    Args          : 2 integers(int)(2 vertices)
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the Graph
-------------------------------------------------------------------------------------------------*/
void Graph::delE(int u, int v)
{
    if(adjMatrix[u][v]) //if edge exists
    {
        adjMatrix[u][v] = 0;    //marking as no edge
        adjMatrix[v][u] = 0;    //marking as no edge
        edgeCount--;    //decrimenting the eddge count
    }

    else
        cerr << "EDGE DOES NOT EXIST" << "\n";  //printing output to erroe stream
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : + (Graph)
*    Args          : Graphs
*    Return Type   : pointer of a graph
*    Application   : This Function returns the number of edges in the union of the Graphs
-------------------------------------------------------------------------------------------------*/
Graph* Graph::operator+(Graph& G)
{
    Graph* result = new Graph(this->vertexCount);    //creating a Graph for result

    for(int i=0; i<G.vertexCount; i++)
    {
        for(int j=0; j<=i; j++)  //j<i to reduce double counting 
        {
            if(this->adjMatrix[i][j] || G.adjMatrix[i][j])  //if an edge exists from i to j in any one of the matrices
                result->addE(i, j);  //adding edge to the result Graph
        }
    }

    return result;   //returning the result of the union of the graphs
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : - (Graph)
*    Args          : Graphs
*    Return Type   : pointer of a graph
*    Application   : This Function returns the number of edges in Graph1 - Graph2
-------------------------------------------------------------------------------------------------*/
Graph* Graph::operator-(Graph& G)
{
    Graph* result = new Graph(this->vertexCount);    //creating a Graph for result

    for(int i=0; i<G.vertexCount; i++)
    {
        for(int j=0; j<=i; j++)  //j<i to reduce double counting 
        {
            if(this->adjMatrix[i][j] && !G.adjMatrix[i][j])  //if an edge exists from i to j in both matrices
                result->addE(i, j);  //adding edge to the result Graph
        }
    }

    return result;   //returning the result of the difference of the graphs
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : % (Graph)
*    Args          : Graphs
*    Return Type   : pointer of a graph
*    Application   : This returns the number of edges in symmetric difference of the Graphs
-------------------------------------------------------------------------------------------------*/
Graph* Graph::operator%(Graph& G)
{
    Graph* result = new Graph(this->vertexCount);    //creating a Graph for result

    for(int i=0; i<G.vertexCount; i++)
    {
        for(int j=0; j<=i; j++)  //j<i to reduce double counting 
        {
            if(this->adjMatrix[i][j] ^ G.adjMatrix[i][j])  //if an edge exists from i to j in any one matrix only
                result->addE(i, j);  //adding edge to the result Graph
        }
    }

    return result;   //returning the number of edges in the symmetric difference of the graphs
}


int Graph::LexicographicProduct(Graph& G)
{
    int count = 0;  //variable to count the number of edges in the union of the Graphs

    //iterating across all (vertexCount)^2 pairs.
    for(int i=0; i<this->vertexCount; i++)
    {
        for(int j=0; j<G.vertexCount; j++)
        {
            for(int k=0; k<this->vertexCount; k++)
            {
                for(int l=0; l<G.vertexCount; l++)
                {
                    if(i==k)   //if i and k are same
                    {
                        if(G.adjMatrix[j][l])   //if j and l are adjacent vertices
                            count++;    //incriment the values of edges
                    }

                    else if(this->adjMatrix[i][k])   //if i and k are adjacent 
                        count++;    //incriment the values of edges
                }
            }
        }
    }

    return count/2;   //returning the value of the lexicographic product
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : edges (Graph)
*    Args          : Nil
*    Return Type   : int
*    Application   : This Function returns the number of edges in a graph
-------------------------------------------------------------------------------------------------*/
int Graph::edges()
{
    return edgeCount;   //returns the nummber of edges in the Graph
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
    int numVertices, numEdges1, numEdges2;  //defining the variables to store edges and vertices count
    int u, v, numQueries;   //temporary vertices to initialise the graph and take in queiries
    cin >> numVertices; //taking in the inputs of edges and vertiex counts
    string command;

    Graph G1(numVertices), G2(numVertices);   //creating 2 graphs with the given number of vertices and edges
    Graph *unionGraph = NULL, *differenceGraph=NULL, *symDifferenceGraph=NULL;   //pointers of the Graph of results

    cin >> numEdges1;   //taking input for number of edges of Graph 1
    for(int i=0; i<numEdges1; i++)   //for loop running to take input of all the edges
    {
        cin >> u >> v;  //taking input for ends of an edge
        G1.addE(u, v);   //adding the edge to the Graph
    }

    cin >> numEdges2;   //taking input for number of edges of Graph 2
    for(int i=0; i<numEdges2; i++)   //for loop running to take input of all the edges
    {
        cin >> u >> v;  //taking input for ends of an edge
        G2.addE(u, v);   //adding the edge to the Graph
    }

    cin >> numQueries;  //taking in the input for the number of queries
    for(int i=0; i<numQueries; i++)
    {
        cin >> command; //taking in the command for the query

        if(command.compare("ADD")==0)    //comparing input instruction with defined instructions
        {
            if(unionGraph)
            {
                unionGraph->~Graph();   //if already has any other data deallocate that to prevent memory leaks
                unionGraph = NULL;  //null initialisation to prevent stray pointings
            }
            unionGraph = G1 + G2;   //finding the union of the Graphs
            cout << unionGraph->edges() << "\n";    //calling the appropriate function to print output
        }


        else if(command.compare("MINUS")==0)    //comparing input instruction with defined instructions
        {
            if(differenceGraph)
            {
                differenceGraph->~Graph();  //if already has any other data deallocate that to prevent memory leaks
                differenceGraph = NULL; //null initialisation to prevent stray pointings
            }
            differenceGraph = G1 - G2;   //finding the difference of the Graphs
            cout << differenceGraph->edges() << "\n";    //calling the appropriate function to print output 
        }

        else if(command.compare("MOD")==0)    //comparing input instruction with defined instructions
        {
            if(symDifferenceGraph)
            {
                symDifferenceGraph->~Graph();   //if already has any other data deallocate that to prevent memory leaks
                symDifferenceGraph = NULL;  //null initialisation to prevent stray pointings
            }
            symDifferenceGraph = G1 % G2;   //finding the symmetric of the Graphs
            cout << symDifferenceGraph->edges() << "\n";    //calling the appropriate function to print output
        }

        else if(command.compare("LexicographicProduct")==0)    //comparing input instruction with defined instructions
            cout << G1.LexicographicProduct(G2) << "\n";    //calling the appropriate function

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;
    }

    if(unionGraph)
        unionGraph->~Graph();   //deallocating any memory allocated
    if(differenceGraph)
        differenceGraph->~Graph();  //deallocating any memory allocated
    if(symDifferenceGraph)
        symDifferenceGraph->~Graph();   //deallocating any memory allocated

    return 0;   //returning 0 to exit the code
}