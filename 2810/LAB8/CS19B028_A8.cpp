#include<iostream>
#include<string>    //header file for inbuilt library string functions.
using namespace std;    //defining name space in global scope


/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to find the Edit Distance between two strings
*    Question : CS2810 A8Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : EDD
*    Application        : Used to find the Edit Distance of 2 strings
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class EDD
{
    string s1, s2;  //creating 2 strings for the class
    unsigned int numCols, numRows;   //variables to store number of rows an columns of matrix 
    int** matrixPtr;    //double pointer to store the integer matrix
    bool assignStatus, valueStatus;  //status of the assignment

    public:
        EDD()   //class constructor
        {
            this->matrixPtr = NULL; //initialisng pointer to NULL to prevent stray pointings
            this->assignStatus = false; //marking that strings are not assigned
            this->valueStatus = false;  //marking that the value of edit distance is not updated
        }

        ~EDD()  //class destructor to deallocate all alotted memory
        {
            if(matrixPtr)   //if matrix already has some data
            {
                for(unsigned int i=0; i<numRows; i++)
                    delete[] matrixPtr[i];  //unallocating all allocated heap memory at matrixPtr

                delete[] matrixPtr; //unallocating all allocated heap memory at matrixPtr
                matrixPtr = NULL;   //avoiding stray pointings
            }
        }

        void assign(string, string);    //function to assign strings to the instance variables
        void compdist(void);    //function to compute the edit distance
        int dist(void); //returns the edit distance
        void table(void);   //prints the table

    private:    //private functions of the class
        int min(int, int);  //returns minimum integer among 2 integers
};

                /******************** THE EDD CLASS FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : min (EDD)
*    Args          : 2 integers(int)
*    Return Type   : Nil
*    Application   : This function gives minimum of 2 integers
-------------------------------------------------------------------------------------------------*/
int EDD::min(int a, int b)
{
    if(a<b) //checking minimum integer
        return a;   //return a if it is minimum

    return b;   //return b if it is min
}

/*-------------------------------------------------------------------------------------------------
*    Function Name : assign (EDD)
*    Args          : 2 strings
*    Return Type   : Nil
*    Application   : This function assigns strings to the instance variables
-------------------------------------------------------------------------------------------------*/
void EDD::assign(string a, string b)
{
    s1 = a; //copying the value of a into S1
    s2 = b; //copying the value of b into s2

    if(matrixPtr)   //if matrix already has some data
    {
        for(unsigned int i=0; i<numRows; i++)
            delete[] matrixPtr[i];  //unallocating all allocated heap memory at matrixPtr

        delete[] matrixPtr; //unallocating all allocated heap memory at matrixPtr
        matrixPtr = NULL;   //avoiding stray pointings
    }

    assignStatus = true;    //markiing that strings are assigned
    valueStatus = false; //marking that edit distance is not up to date
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : compdist (EDD)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This function computes the edit distance of 2 strings
-------------------------------------------------------------------------------------------------*/
void EDD::compdist(void)
{
    if(assignStatus)
    {
        if(!valueStatus)
        {
            numRows = s1.size() + 1;    //getting number of rows
            numCols = s2.size() + 1;    //getting number of columns

            matrixPtr = new int*[numRows];   //allocating heap memory to the matrix
            for(unsigned int i=0; i<numRows; i++)
                matrixPtr[i] = new int[numCols];    //allocating heap memory for the matrix

            for(unsigned int i=0; i<numRows; i++)   //for loop to change rows
            {
                for(unsigned int j=0; j<numCols; j++)   //for loop to change columns across a row
                {
                    if(i==0 || j==0)    //making initialisations
                        matrixPtr[i][j] = i+j;  //i if j equals 0 and 0 if i equals 0

                    else if(s2[j-1] == s1[i-1])
                        matrixPtr[i][j] = matrixPtr[i-1][j-1];  //computing values of lower terms

                    else
                        matrixPtr[i][j] = 1 + min(matrixPtr[i-1][j-1], min(matrixPtr[i][j-1], matrixPtr[i-1][j]));  //finding minimum of 3 terms
                }
            }

            valueStatus = true; //marking that edit value is just updated
        }
    }

    else    //throwing an exception when strings are not assigned
    {
        try //for exception handling
        {
            throw "STRINGS ARE NOT ASSIGNED";
        }

        catch(const char* msg)  //catching the exception
        {
            cout << msg << endl;    //printing message to error screen
        }
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : dist (EDD)
*    Args          : Nil
*    Return Type   : integer(int)
*    Application   : This function returns the edit distance of 2 strings
-------------------------------------------------------------------------------------------------*/
int EDD::dist(void)
{
    if(!valueStatus)    //checking if the edit distance is up to date or not
        compdist(); //calling the compdist function

    if(matrixPtr)
        return matrixPtr[numRows-1][numCols-1];    //returning the edit distance of the 2 strings

    return -1;  //default return
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : table (EDD)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This function prints the matrix
-------------------------------------------------------------------------------------------------*/
void EDD::table(void)
{
    if(!valueStatus)
        compdist(); //edit distance is not upto date

    for(unsigned int i=1; i<numRows; i++)    //for loop to traverse rows
    {
        for(unsigned int j=1; j<numCols; j++)    //for loop to traverse columns
            cout << matrixPtr[i][j] << " "; //printing all the elements of row one by one

        cout << endl;   //printing each row in a new line
    }
}
                /******************** THE EDD CLASS FUNCTIONS END HERE ********************/


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int numQueries; //number of queries
    string command, a, b; //input Command and input argumments

    cin >> numQueries;  //number of queries that need to be processed
    EDD Obj;    //creating an object for the class

    while(numQueries)
    {
        cin >> command; //taking string input of the command

        if(command.compare("assign")==0)    //comparing input instruction with defined instructions
        {
            cin >> a;   //taking input of first string
            cin >> b;   //taking input of second string
            Obj.assign(a, b);   //calling the appropriate function
        }

        else if(command.compare("compdist")==0)
            Obj.compdist(); //calling the function

        else if(command.compare("dist")==0)
        {
            int temp = Obj.dist();  //calling the appropriate function
            if(temp != -1)  //function returns -1 if strings are not attatched
                cout << temp << endl;   //printing the result
        }

        else if(command.compare("table")==0)
            Obj.table();    //calling the appropriate function

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;

        numQueries--;   //decrimenting the number of queries
    }

    return 0;   //returning 0 to exit the program
}