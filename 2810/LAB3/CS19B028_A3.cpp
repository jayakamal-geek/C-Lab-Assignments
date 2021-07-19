#include<iostream>
#include<string>    //header file for inbuilt library string functions.
using namespace std;
/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to manage graphs and operations using stacks
*    Question : CS2810 A3Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : StackNode
*    Application        : Used to represent the singular node of Stack. 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class StackNode
{
    public:
        int value;  //integer to store the value of the stack node
        StackNode* link;    //link to store the pointer of the next stack node

        StackNode(int value)    //class constructor of StackNode to easeup initialisation
        {
            this->value = value;    //initialising value
            this->link = NULL;    //initialising link to NULL to prevent pointing stray adresses
        }
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Stack
*    Application        : Used to represent a stack, a collection of stackNode
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Stack
{
    StackNode* root = NULL;    //A pointer to keep track of top of the stack initialised to NULL to prevent pointing stray adresses

    public:
        void Push(int);     //A stack function to push a new element into the stack; puts a new element at the top of the stack
        int Pop(void);      //A stack function to pop out and return the top element of the stack.
        int Top(void);      //A stack function to return the top element of the stack.
        int isEmpty(void);  //A stack function to return 1 if stack is empty else return zero.
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Graph
*    Application        : Used to represent a Graph(E, V) and perform operations on it 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Graph
{
    int** adjMatrix;    //Adjacency Matrix to store edges
    int vertexCount;    //value to store the number of vertices

    public:
        Graph(int vertexCount)  //class constructor to easen up initialisation
        {
            this->vertexCount = vertexCount;    //initialising vertex count
            adjMatrix = new int*[vertexCount];  //allotting memory to the matrix

            for(int i=0; i<vertexCount; i++)    //for loop to traverse rows of the matrix
            {
                adjMatrix[i] = new int[vertexCount];    //allotting memory to the matrix 

                for(int j=0; j<vertexCount; j++)    //for loop to traverse across the columns
                {
                    adjMatrix[i][j] = 0;    //initialising all the matrix elements to zero
                }
            }
        }

        void operator += (pair<int, int>);     //function to add new edge to the graph
        void operator -= (pair<int, int>);     //function to delete an edge from the graph
        int detectCycle(void);      //function to check if a graph contains any cycles
        int components(void);   //function to find number of components in a graph
        int reach(pair<int, int>);    //function to check if the given two vertices of graph are connected         
        bool DFS_Helper(int, bool*, int);  //A helper function that uses DFS.
        void DFS_HelperStack(int, bool*);   //A helper function that uses DFS
};


                /******************** THE STACK FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : Push (Stack)
*    Args          : int
*    Return Type   : None
*    Application   : This Function allots memory and inserts a new element on the top of the Stack
-------------------------------------------------------------------------------------------------*/
void Stack::Push(int temp)
{
    StackNode* tempPtr = root;  //using temporary pointer to store the value of root before adding new element
    root = new StackNode(temp); //creating a new stack node and storing its adress as new root
    root->link = tempPtr;   //appending old root node to new root
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : Pop (Stack)
*    Args          : Nil
*    Return Type   : int
*    Application   : This Function pops out top element of the stack and returns it
-------------------------------------------------------------------------------------------------*/
int Stack::Pop()
{
    int tempVal = -1;    //A new integer to store the value of the top node, initialising to int_min

    if(!isEmpty())  //preventing stack underflow by checking if stack is nonempty or not
    {
        StackNode* tempPtr = root;  //using temporary pointer to store the value of root before deleting the topmost element
        root = root->link;  //updating the new root to pointer of the 2nd stack node of the stack
        tempVal = tempPtr->value;   //obtaining the value of the top stack node.
        delete(tempPtr);  //freeing the memory allotted to that pointer to prevent memory leaks
    }

    return tempVal;     //returning the top element
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : Top (Stack)
*    Args          : Nil
*    Return Type   : int
*    Application   : This Function returns the Top element of the Stack
-------------------------------------------------------------------------------------------------*/
int Stack::Top()
{
    int tempVal = -1;    //A new integer to store the value of the top node, initialising to int_min
    if(!isEmpty())  //preventing stack underflow by checking if stack is nonempty or not
        tempVal = root->value;  //getting the value of the top node of the stack
    
    return tempVal;     //returning the top element
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : isEmpty (Stack)
*    Args          : Nil
*    Return Type   : int (1 or 0)
*    Application   : This Function to check if a stack is empty
-------------------------------------------------------------------------------------------------*/
int Stack::isEmpty()
{
    if(root == NULL) //checking if root equals NULL
        return 1;   //returns 1 if stack is empty
    return 0;   //returns 0 if stack is not empty
}
                /******************** THE STACK FUNCTIONS END HERE ********************/


                /******************** THE GRAPH FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : += (Operator)(Graph)
*    Args          : An std::pair of integers
*    Return Type   : Nil
*    Application   : This Function adds an edge to the Graph; i.e. to the adjacency matrix.
-------------------------------------------------------------------------------------------------*/
void Graph::operator += (pair<int, int> tempPair)
{
    int temp1 = tempPair.first, temp2 = tempPair.second;    //obtaining the values of the pair
    adjMatrix[temp1][temp2] = 1;    //making an edge in the adjacency matrix from v to u
    adjMatrix[temp2][temp1] = 1;    //adding edge in the matrix from u to v
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : -= (Operator)(Graph)
*    Args          : An std::pair of integers
*    Return Type   : Nil
*    Application   : This Function deletes an edge from the Graph; i.e. from the adjacency matrix.
-------------------------------------------------------------------------------------------------*/
void Graph::operator -= (pair<int, int> tempPair)
{
    int temp1 = tempPair.first, temp2 = tempPair.second;    //obtaining the values of the pair
    adjMatrix[temp1][temp2] = 0;    //deleting an edge in the adjacency matrix from v to u
    adjMatrix[temp2][temp1] = 0;    //deleting an edge in the matrix from u to v
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : detectCycle(Graph)
*    Args          : Nil
*    Return Type   : int(1 or 0)
*    Application   : This Function that checks for cycles in the Graph
-------------------------------------------------------------------------------------------------*/
int Graph::detectCycle()
{
    int found_cycle = 0;    //variable to return
    bool visited[vertexCount];    //boolean array to keep a track whether the vertex is visited or not
    for(int i=0; i<vertexCount; i++)   //for loop to initialise all boolean values to false
    {
        visited[i] = false; //marking all unvisited
    }

    for(int i=0; i<vertexCount; i++)    //for loop to check whether all vertices are reached or not
    {
        if(!visited[i]) //if a vertex is not visited then do DFS from that vertex
        {
            bool flag = DFS_Helper(i, visited, i);  //found cycle or not

            if(flag)    //if found a cycle
            {
                found_cycle = 1;    //update found value
                break;  //breaking out of the loop
            }
        }        
    }

    return found_cycle; //retuning 1 or 0
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DFS_Helper(Graph)
*    Args          : Array of boolean values and 2 integers
*    Return Type   : Boolean
*    Application   : Uses DFS to detect cycle using recursion
-------------------------------------------------------------------------------------------------*/
bool Graph::DFS_Helper(int start, bool* visited, int parent)
{
    visited[start] = true;  //marking the start vertex as visited
    bool flag = false;  //initialising the return variable to false

    for(int i=0; i<vertexCount; i++)    //for loop to traverse across all vertices
    {
        if(!flag)
        {
            if(adjMatrix[start][i] && i!=parent)    //if edge exists and its not the parent
            {
                if(visited[i])  //if reached an already visited vertex then cycle exists
                    return true;    //returning true
                
                flag = DFS_Helper(i, visited, start);   //calling next recurssion
            }
        }
    }

    return flag;    //returning the flag variable
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : components(Graph)
*    Args          : Nil
*    Return Type   : int
*    Application   : Finds number of connected components in the graph
-------------------------------------------------------------------------------------------------*/
int Graph::components()
{
    bool visited[vertexCount];    //an array to mark vertices as visited or unvisited
    int component_count = 0;    //variable to count number of components in the graph

    for(int i=0; i<vertexCount; i++)    //for loop to travel across all values
    {
        visited[i] = false; //marking all vertices as unvisited
    }

    for(int i=0; i<vertexCount; i++)    //for loop to check whether all vertices are reached or not
    {
        if(!visited[i]) //if a vertex is not visited then do DFS from that vertex
        {
            DFS_HelperStack(i, visited);  //make a DFS from unvisited vertex
            component_count++;  //incrimenting the number of components
        }        
    }

    return component_count;   //returns the number of components in the graph
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : DFS_HelperStack(Graph)
*    Args          : Array of boolean values and an integer
*    Return Type   : Nil
*    Application   : Does a DFS on the graph
-------------------------------------------------------------------------------------------------*/
void Graph::DFS_HelperStack(int start, bool* visited)
{
    Stack S;    //creating a stack 
    visited[start] = true;  //marking start vertex as unvisited
    S.Push(start);  //pushing the start vertex into the stack

    while(!S.isEmpty()) //while a stack the non empty
    {
        start = S.Pop();    //pop out the topmost element of the stack
        for(int i=0; i<vertexCount; i++)    //for loop to traverse across the columns
        {
            if(adjMatrix[start][i]) //if there exists an edge
            {
                if(!visited[i]) //if vertex is not visited
                {
                    visited[i] = true;  //mark as visited
                    S.Push(i);  //push in a new element
                }
            }
        }
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : reach(Graph)
*    Args          : a pair of integers
*    Return Type   : int (1 or 0)
*    Application   : finds whether a path exists between the pair of vertices or not
-------------------------------------------------------------------------------------------------*/
int Graph::reach(pair<int, int> tempPair)
{
    int temp1 = tempPair.first, temp2=tempPair.second;

    if(temp1==temp2 || adjMatrix[temp1][temp2]) //if both vertces are same or there exists an edge
        return 1;

    bool visited[vertexCount];    //boolean array to keep a track whether the vertex is visited or not
    for(int i=0; i<vertexCount; i++)   //for loop to initialise all boolean values to false
    {
        visited[i] = false; //marking all unvisited
    }
    DFS_HelperStack(temp1, visited);    //making a dfs using stack

    if(visited[temp2])
        return 1;

    return 0;
}
                /******************** THE GRAPH FUNCTIONS END HERE ********************/


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int n, m, temp1, temp2, vertices; //variables for number of stack and graph commands respectively
    string inputCommand;    //string for input command
    pair<int, int> tempPair;    //defining a pair

    cin >> n;   //input for number of stack operations
    Stack S;    //initialising a Stack

    while(n)
    {
        cin >> inputCommand;    //taking input strings

        if(inputCommand.compare("push")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1; //taking input of necessary second argument
            S.Push(temp1);   //calling the appropriate function
        }

        else if(inputCommand.compare("pop")==0)    //comparing input instruction with defined instructions
            cout << S.Pop() << endl;   //calling the appropriate function
        
        else if(inputCommand.compare("top")==0)    //comparing input instruction with defined instructions
            cout << S.Top() << endl;   //calling the appropriate function

        else if(inputCommand.compare("empty")==0)    //comparing input instruction with defined instructions
            cout << S.isEmpty() << endl;   //calling the appropriate function

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;

        n--;    //decrimenting m to keep track of iterations
    }

    cin >> vertices;    //input for number of vertices
    Graph G(vertices);  //initialising a graph
    cin >> m;   //number of Graph Commands

    while(m)
    {
        cin >> inputCommand;    //taking input strings

        if(inputCommand.compare("add")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1 >> temp2; //taking input of necessary argument
            tempPair.first = temp1;  //initialising values into a new pair
            tempPair.second = temp2;  //initialising values into a new pair
            G += tempPair;  //adding a new edge to the graph
        }

        else if(inputCommand.compare("del")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp1 >> temp2; //taking input of necessary argument
            tempPair.first = temp1;  //initialising values into a new pair
            tempPair.second = temp2;  //initialising values into a new pair
            G -= tempPair;  //adding a new edge to the graph
        }

        else if(inputCommand.compare("cycle")==0)
            cout << G.detectCycle() << endl;

        else if(inputCommand.compare("components")==0)
            cout << G.components() << endl;

        else if(inputCommand.compare("reach")==0)
        {
            cin >> temp1 >> temp2; //taking input of necessary argument
            tempPair.first = temp1;  //initialising values into a new pair
            tempPair.second = temp2;  //initialising values into a new pair
            cout << G.reach(tempPair) << endl;  //checks if there exists path between given vertices 
        }

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;

        m--;    //decrimenting m to keep track of iterations
    }

    return 0;   //exit call
}