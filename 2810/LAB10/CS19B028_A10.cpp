#include<iostream>
#include<string>    //header file for inbuilt library string functions.
using namespace std;    //defining name space in global scope


/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP program to simulate the MineSweeper game
*    Question : CS2810 A10Q1
-------------------------------------------------------------------------------------------------*/


class cell
{
    public:
        bool revealStatus = false;  //whether a cell is revealed or not
        bool mineStatus = false;    //whether the cell has a mine or not
        int mineNeighbours = 0; //number of neighbours in the surrounding 8
};


class MineSweeper
{
    cell** mineField;   //the double pointer to represent a 2d array of mines
    int fieldSize, safeCellCount, revealCount;  //order of the square matrix

    public:    //publiic functions of the class
        MineSweeper(int fieldSize)
        {
            this->fieldSize = fieldSize;    //initialising the field size

            this->mineField = new cell*[fieldSize]; //setting up the field
            for(int i=0; i<fieldSize; i++)  //allocating the required heap memory
                this->mineField[i] = new cell[fieldSize];
        }

        ~MineSweeper()
        {
            for(int i=0; i<fieldSize; i++)  //deallocating the allocated heap memory
                delete[] mineField[i];  //deallocating the memory
            delete[] mineField; //deallocating the memory

            fieldSize = 0;  //making a null initialisation
            mineField = NULL;   //making a null initialisation
        }

        void setUp(int); //setting up the mineField
        int click(int, int);    //makes the move by a selecting a cell in the mineField
        void changeLevel(int);  //changes the order of the matrix

    private:    //private functions of the class
        void GameOver(bool);    //game Over message
};

                /******************** THE MineSweeper CLASS FUNCTIONS BEGIN HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : setUp (MineSweeper)
*    Args          : integer(int)
*    Return Type   : Nil
*    Application   : This Function sets up the mine field for the game
-------------------------------------------------------------------------------------------------*/
void MineSweeper::setUp(int minesCount)
{
    safeCellCount = (fieldSize*fieldSize) - minesCount; //getting the number of safe cells
    revealCount = 0;
    int rowIndex=0, colIndex=0; //necessary variables for processing
    int arr[] = {-1, 0, 1}; //array of Index shifts

    for(int i=0; i<minesCount; i++) //for loop to setup all the mines
    {
        int temp;
        cin >> temp;

        rowIndex = temp/fieldSize;  //getting row Index
        colIndex = temp%fieldSize;  //getting the column index
        if(!mineField[rowIndex][colIndex].mineStatus)
        {
            mineField[rowIndex][colIndex].mineStatus = true;    //marking the existance of mine in the area

            for(int k=0; k<3; k++)   //for loop for rows 
            {
                int tempRow = rowIndex + arr[k];    //getting neighbour indexes
                if(tempRow > -1 && tempRow < fieldSize) //if indexes are not going out of range
                {
                    for(int j=0; j<3; j++)  //for loop for the columns
                    {
                        int tempCol = colIndex + arr[j];    //getting neighbour indexes

                        if(tempCol > -1 && tempCol < fieldSize) //if indexes are not going out of range
                            mineField[tempRow][tempCol].mineNeighbours++;  //incrimenting the number of mine neighbous
                    }
                }
            }
        }
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : click (MineSweeper)
*    Args          : 2 integers(int)
*    Return Type   : int (number of surrounding mines)
*    Application   : This Function makes on click move on selected cell
-------------------------------------------------------------------------------------------------*/
int MineSweeper::click(int rowIndex, int colIndex)
{
    if(!mineField[rowIndex][colIndex].revealStatus)
    {
        mineField[rowIndex][colIndex].revealStatus = true;  //marking the cell as revealed
        if(mineField[rowIndex][colIndex].mineStatus)
        {
            GameOver(false);    //loosing message
            return -1;
        }
        revealCount++;  //incrimenting 

        if(revealCount == safeCellCount)
        {
            GameOver(true);    //winning message
            return -1;
        }

        if(mineField[rowIndex][colIndex].mineNeighbours == 0)
        {
            int arr[] = {-1, 0, 1}; //array of Index shifts
            for(int i=0; i<3; i++)   //for loop for rows 
            {
                int tempRow = rowIndex + arr[i];    //getting neighbour indexes

                if(tempRow > -1 && tempRow < fieldSize) //if indexes are not going out of range
                {
                    for(int j=0; j<3; j++)  //for loop for the columns
                    {
                        int tempCol = colIndex + arr[j];    //getting neighbour indexes

                        if(tempCol > -1 && tempCol < fieldSize) //if indexes are not going out of range
                            click(tempRow, tempCol);    //operating on neighbours and finding total number of mines
                    }
                }
            }
        }
    }

    if(revealCount == safeCellCount)    //if game over
        return -1;  //return -1 if game is over

    return revealCount; //return reveal count if game is still going on
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : changeLevel (MineSweeper)
*    Args          : integer(int)
*    Return Type   : Nil
*    Application   : This Function changes the size of the minefield
-------------------------------------------------------------------------------------------------*/
void MineSweeper::changeLevel(int newSize)
{
    for(int i=0; i<fieldSize; i++)  //deallocating the allocated heap memory
        delete[] mineField[i];  //deallocating the memory
    delete[] mineField; //deallocating the memory

    fieldSize = newSize;    //changing the size of the field

    mineField = new cell*[fieldSize]; //setting up the field
    for(int i=0; i<fieldSize; i++)  //allocating the required heap memory
        mineField[i] = new cell[fieldSize];
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : GameOver (MineSweeper)
*    Args          : boolean
*    Return Type   : Nil
*    Application   : This Function prints game over message
-------------------------------------------------------------------------------------------------*/
void MineSweeper::GameOver(bool flag)
{
    if(flag)
    {
        cout << "Won" << endl;  //winning message
        return;
    }

    cout << "Lost" << endl; //losing message
}
                /******************** THE MineSweeper CLASS FUNCTIONS END HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int fieldSize, mineCount, result=0;   //variables for the field setting up
    int rowIndex, colIndex;
    cin >> fieldSize >> mineCount;  //taking in the inputs

    MineSweeper game(fieldSize);    //creating a game
    game.setUp(mineCount);  //setting up the mine field

    while(cin >> rowIndex >> colIndex) //while a game terminating condition is not reached
    {
        result = game.click(rowIndex, colIndex);    //making the click
        if(result != -1)    //printing result
            cout << result << endl;
    }

    return 0;   //returning 0 to exit the program
}