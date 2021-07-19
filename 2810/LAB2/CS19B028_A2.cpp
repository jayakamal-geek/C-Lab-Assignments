#include<iostream>
#include<bits/stdc++.h> //headerfile for limits
#include<string>    //header file for inbuilt library string functions.
using namespace std;    //
/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to manage Matrix operations using classes.
*    Question : CS2810 A2Q1
-------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
*    Class Name         : Matrix
*    Application        : Used to represent & store matrices and perform some special operstions. 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Matrix
{
    protected:
        int numRows, numColumns;   //integers to specify nummber of rows and columns.
        int** matrix;   //double pointer to store the pointer.

    public:
        void scanInput(void);   //function to take the inputs of the matrix.
        int binarySearch(int, int); //function to perform binary search for element x in Kth row.
        int* matrixSearch(int);   //function to search entire matrix for element x and return indices i,j in an int array.
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : MatrixMedian
*    Application        : Used to find Median of a Matrix
*    Inheritances       : 1(Matrix)
-------------------------------------------------------------------------------------------------*/
class MatrixMedian : public Matrix  //class derived from matrix class
{
    public:
        MatrixMedian(int numRows, int numColumns)    //class constructor of the class matrixmedian.
        {
            this->numRows = numRows;    //initialising the instance variables using constructor.
            this->numColumns = numColumns;    //initialising the instance variables using constructor.
            matrix = NULL;  //initialising double pointer to null.
        }

        int upperBound(int, int);   //function to perform binary search and find index of smallest number greater than x in kth row
        int findMedian(void);   //function to find the median of the entire matrix
};


/*-------------------------------------------------------------------------------------------------
*    Function Name : scanInput(class: Matrix)
*    Args          : Nil
*    Return Type   : None
*    Application   : This Function allots memory and takes input for the matrix.
-------------------------------------------------------------------------------------------------*/
void Matrix::scanInput()
{
    matrix = (int**)malloc(numRows*sizeof(int*));   //allocating the space required for m number of integer array(row) pointers.

    for(int i=0; i<numRows; i++)   //for loop to allot required space to rows to contain elements and to take inputs.
    {
        matrix[i] = (int*)malloc(numColumns*sizeof(int));   //alotting n spcaces in each row to contain elements.

        for(int j=0; j<numColumns; j++)  //for loop to take input of ith row.
        {
            cin >> matrix[i][j];    //taking input for the elements of the current row.
        }
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : binarySearch(class: Matrix)
*    Args          : two integers (1 element + 1 row index)
*    Return Type   : integer (column index)
*    Application   : This Function searches for element x in Kth row and returns maximum index j
                     such that a[k][j]<=x.
-------------------------------------------------------------------------------------------------*/
int Matrix::binarySearch(int x, int k)  //A binary search Function using iteration.
{
    int low = 0;    //reference points of segment of array in which search must be done.
    int high = numColumns-1;    //reference points of segment of array in which search must be done.

    if(matrix[k][0]>x)  //case when no index is found 
        return -1;  
    
    if(matrix[k][numColumns-1]<=x)  //case when every number in the row are less than x.
        return numColumns-1;
    
    while(low <= high)   //while loop to manage up to what point iteration must be done.
    {
        int middleNum = (low+high)/2;   //finding the middle number of the row.

        if(matrix[k][middleNum]<=x && x<matrix[k][middleNum+1])  //while loop to ensure that maximum value of j.
            return middleNum;

        if(matrix[k][middleNum] <= x)    //moving leftmost refernce point towards right to reduce searches.
            low = middleNum + 1;

        else
            high = middleNum - 1;  //moving rightmost reference point towards lrft to reduce number of searches.
    }

    return -1;  //return if not found
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : matrixSearch(class: Matrix)
*    Args          : integer (1 element)
*    Return Type   : array of 2 integer (row index, column index)
*    Application   : This Function searches for element x in the matrix and returns indices of its
                     first occurance in the matrix.                     
-------------------------------------------------------------------------------------------------*/
int* Matrix::matrixSearch(int x)
{
    int* coordinates = (int*)malloc(2*(sizeof(int)));   //integer array of size 2 to return row index and column index.

    for(int i=0; i<numRows; i++)    //for loop to search each row one by one for x using binary search.
    {
        coordinates[0] = i; //initialising row index.
        coordinates[1] = -1;

        int low = 0;    //reference points of segment of array in which search must be done.
        int high = numColumns-1;    //reference points of segment of array in which search must be done.

        while(low <= high)   //while loop to manage up to what point iteration must be done.
        {
            int middleNum = (low+high)/2;   //finding the middle number of the row.

            if(matrix[i][middleNum]==x)  //while loop to ensure that minimum value of j.
            {
                coordinates[1] = middleNum;
                high = middleNum-1;
            }

            if(matrix[i][middleNum] < x)    //moving leftmost refernce point towards right to reduce searches.
                low = middleNum + 1;

            else
                high = middleNum - 1;  //moving rightmost reference point towards lrft to reduce number of searches.
        }

        if(coordinates[1]!=-1)  //if coordinates are found return them.
        {
            return coordinates;
        }
    }

    coordinates[0] = -1;    //element not found so returning -1.
    coordinates[1] = -1;    //element not found so returning -1.
    return coordinates;
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : upperBound(class: MatrixMedian)
*    Args          : two integers (1 element + 1 row index)
*    Return Type   : integer (column index)
*    Application   : This Function searches for element x in Kth row and returns minimum index j
                     such that a[k][j]>x.
-------------------------------------------------------------------------------------------------*/
int MatrixMedian::upperBound(int x, int k)
{
    int val = binarySearch(x, k);   //using binarySearch function written before

    if(val==numColumns-1)   //if to check last elemen or not
        return -1;
    
    else    //if not last element return value +1
        return val+1; 
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : findMedian(class: MatrixMedian)
*    Args          : None
*    Return Type   : integer (median)
*    Application   : This Function gives the median of the matrix
-------------------------------------------------------------------------------------------------*/
int MatrixMedian::findMedian()
{
    int medianRank = (numRows*numColumns+1)/2;  //index of median among all matrix elements when sorted.
    int low = INT_MIN;  //initializing minimum value to find extremes of matrix.
    int high = INT_MAX; //initializing maximum value to find extremes of matrix.
    int count, midVal; //variable to count number of elements less than midvalue

    while(low<high-1) //number of iterations to be performed
    {
        count=0;    //setting count to zero before every iteration
        midVal = (low+high)/2; //finding average of the extremes of the current segment.

        for(int i=0; i<numRows; i++)    //for loop to find number of elements less than midval in matrix
        {
            int k = upperBound(midVal, i); //number of elements less than midvalue

            if(k==-1)   //if k==-1 then all row is less than than the midval
                k = numColumns;

            count = count + k;  //adding all number of elements
        }

        if(count < medianRank)  //if condition to narrow down the segment
            low = midVal+1;

        else
            high = midVal; //narrowing down the segment.
    }

    count = 0;
    for(int j=0; j<numRows; j++)    //for loop for final check for the median
    {
        int k = upperBound(low, j); //number of elements less than low

        if(k==-1)   //if k==-1 then all row is less than than the midval
            k = numColumns;

        count = count + k;  //adding all number of elements
    }

    if(count>=medianRank)   //returning low if low is the required median
        return low;

    return high;    //returning high, if high is the required median
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : None
*    Application   : Entry Point into the code
-------------------------------------------------------------------------------------------------*/
int main()
{
    int numRows, numColumns, q, x, k;   //variables to store all necessary inputs
    string inputCommand;    //string to store input command

    cin >> numRows >> numColumns;   //taking input for number of rows and columns

    MatrixMedian A(numRows, numColumns);    //creating an object using constructor

    A.scanInput();  //calling function to take inputs for the matrix
    cin >> q;   //taking input for number of commands
    for(int i=0; i<q; i++)  //for loop to execute all commands
    {
        cin >> inputCommand;

        if(inputCommand.compare("BS")==0)    //comparing input instruction with defined instructions
        {
            cin >> x >> k ; //taking input of necessary second argument
            cout << A.binarySearch(x, k) <<endl; //calling the appropriate function
        }

        else if(inputCommand.compare("MS")==0)    //comparing input instruction with defined instructions
        {
            cin >> x ; //taking input of necessary second argument
            int* temp = A.matrixSearch(x);  //function call.
            cout << temp[0] << " " <<temp[1] <<endl; //printing the values
        }

        else if(inputCommand.compare("Median")==0)    //comparing input instruction with defined instructions
            cout << A.findMedian() <<endl; //calling the appropriate function

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;
    }

    return 0;   //return statement to exit the program
}