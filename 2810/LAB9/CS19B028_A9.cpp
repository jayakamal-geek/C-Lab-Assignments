#include<iostream>
#include<vector>    //header file to use vectors
#include<string>    //header file for inbuilt library string functions.
#include<iomanip>
using namespace std;    //defining name space in global scope


/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP program to convert currencies
*    Question : CS2810 A9Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : WorldBank
*    Application        : Used to keep track of all colours of currencies and legal exchanges
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class WorldBank
{
    vector<vector<int>> treaties;   //The vector of vector to keep track of all the treaties
    int* colorCodes;    //colour codes of currencies
    float** curConvert;   //matrix to hold the conversion values of currencies
    int numColors, numCurrencies;   //number of colors and currencies

    public: //public methods/functions of the class
        WorldBank(int numColors)    //class constructor of the class world bank
        {
            this->numColors = numColors;    //initialisiing the number of colors

            for(int i=0; i<numColors; i++)  //for loop to initialise vectors to array of vectors
            {
                vector<int> tempVector; //temporary vector
                treaties.push_back(tempVector); //initialising vector of vector
            }

            this->colorCodes = NULL;    //initialising all variables to NULL
            this->curConvert = NULL;    //initialising all variables to NULL
        }

        ~WorldBank()    //class constructor of the class world bank
        {
            for(int i=0; i<numColors; i++) //for loop to destroy the vector properly
                treaties[i].clear();    //propely clearing out all elements
            treaties.clear();   //properly clearing out all elements

            this->colorCodes = NULL;    //initialising all variables to NULL
            this->curConvert = NULL;    //initialising all variables to NULL
        }

        void initialize(pair<int, int>*, int*, float**, int, int);  //function to initialize the object whenever we need
        void compute(int, int, int);    //function to compute the translation 
};

                /******************** THE WorlDBank CLASS FUNCTIONS BEGIN HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : initialize (WorldBank)
*    Args          : integer pair, integer array, integer 2d array and 2 integers
*    Return Type   : Nil
*    Application   : This Function initialises all the object variables
-------------------------------------------------------------------------------------------------*/
void WorldBank::initialize(pair<int, int>* tempTreaty, int* tempCodes, float** tempVals, int temp, int numTreaties)
{
    curConvert = tempVals;  //initialising the pointer values of the object
    colorCodes = tempCodes; //initialising the pointer values of the object
    numCurrencies = temp;   //initialising the instance variables of the object

    for(int i=0; i<numTreaties; i++)
    {
        treaties[tempTreaty[i].first].push_back(tempTreaty[i].second);   //pushing the treaty into to the graph
        treaties[tempTreaty[i].second].push_back(tempTreaty[i].first);   //pushing the treaty into to the graph
    }

    for(int i=0; i<numColors; i++)  //same colors are considered to have treaty with them selves
        treaties[i].push_back(i);
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : compute (WorldBank)
*    Args          : 3 integers
*    Return Type   : Nil
*    Application   : This Function computes a legal transaction if one is possible
-------------------------------------------------------------------------------------------------*/
void WorldBank::compute(int start, int end, int weight)
{
    float* maxDist = new float[numCurrencies];
    for(int i=0; i<numCurrencies; i++)
        maxDist[i] = -1;    //initialising all maximum distances to -1
    maxDist[start] = 1; //initialising the maximum distance of start as 0

    for(int m=0; m<numCurrencies-1; m++)    //for loop for multiple iterations
    {
        for(int i=0; i<numCurrencies; i++)
        {
            int temp = colorCodes[i];   //getting the color code of vertex i
            for(auto j=treaties[temp].begin(); j!=treaties[temp].end(); j++)
            {
                int tempCol = *j;   //getting the color of the treaty
                for(int k=0; k<numCurrencies; k++)  //cheking the colorCodes of the other vertices
                {
                    if(k!=i)    //if both are not same currencies then do this
                    {
                        if(colorCodes[k]==tempCol)  //if the colour codes are same as the treaty colors
                        {
                            if(maxDist[i]!=-1 && (maxDist[i]*curConvert[i][k] > maxDist[k]))  //checking the value of the distance
                                maxDist[k] = maxDist[i]*curConvert[i][k];   //updating distance if a greater value is found
                        }
                    }
                }
            }
        }
    }
    
    if(maxDist[end] == -1)  //if the desired currency is not reachable
        cout << -1 << endl;

    else
    {
        if(maxDist[start] == 1) //if no incresing cycles
            cout << fixed << setprecision(3) << weight*maxDist[end] <<endl;
        
        else    //if an incresing cycle is present
            cout << "INF" << endl;
    }
    
    delete[] maxDist;   //deallocating allocated heap memory
}
                /******************** THE WorlDBank CLASS FUNCTIONS END HERE ********************/


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int numColors, numTreaties, numCurrencies, commandCount, temp1, temp2, temp3;    //all the variables needed to carry out the operations
    cin >> numColors;   //taking input for the number of colors
    cin >> numTreaties; //taking in the number of inputs for treaties

    WorldBank B(numColors); //creating an instance of the class WorldBank
    pair<int, int> treaties[numTreaties];   //array of pairs tto store treaties between colours
    for(int i=0; i<numTreaties; i++)
        cin >> treaties[i].first >> treaties[i].second; //taking input for the treaties

    cin >> numCurrencies;   //taking input for the number of currencies
    int colorCodes[numCurrencies];  //array to store the color codes of the treaties
    for(int i=0; i<numCurrencies; i++)
        cin >> colorCodes[i];   //taking in input of all color codes

    float** matrix = new float*[numCurrencies]; //allocating heap memory to store conversion values
    for(int i=0; i<numCurrencies; i++)
    {
        matrix[i] = new float[numCurrencies]; //allocating heap memory to store conversion values
        for(int j=0; j<numCurrencies; j++)
            cin >> matrix[i][j];    //taking in inputs of the conversion factors
    }

    B.initialize(treaties, colorCodes, matrix, numCurrencies, numTreaties); //calling in the initialize function

    cin >> commandCount;    //taking input for number of queries
    for(int i=0; i<commandCount; i++)
    {
        cin >> temp1 >> temp2 >> temp3; //taking in necessary arguments
        B.compute(temp1, temp2, temp3);
    }

    for(int i=0; i<numCurrencies; i++)
        delete[] matrix[i]; //deallocating the allocated heap memory
    delete[] matrix;    //deallocating the heap memory

    return 0;   //returning 0 to exit the program
}