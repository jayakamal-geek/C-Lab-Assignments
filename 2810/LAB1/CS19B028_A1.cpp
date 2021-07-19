#include<iostream>
#include<string>    //header file to use string class and its functions
#include<cstdlib>   //header file for pointer operations
using namespace std;
/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to manage Matrix operations using classes.
*    Question : CS2810 A1Q1
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Matrix
*    Application        : Used to represent & store matrices and perform some special operstions. 
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Matrix
{
    int order;  //an integer to store the order of the given square matrix.
    int** matrix; // double pointer to store entries of the matrix as a 2-dimensional array.

    public:
    Matrix( int order, int** matrix) //class constructor of the Matrix class to easen up initialisation.
    {
        this->matrix = matrix;  //assigning the order to the instance variable of Matrix class
        this->order = order;    //assigning the order to the instance variable of Matrix class
    }

    void SpecialSum(void);                    // A Special function defined in the question. keyword: SPSUM
    void ModMultiplication(void);             // A Special function defined in the question. Keyword: MOD
    void MatrixRightShift(Matrix, int);       // A special function defined in the question. keyword: MRS
    void SpecialMatrixAddition(Matrix, int);  // A special function defined in the question. keyword: MADD
};

/*-------------------------------------------------------------------------------------------------
*    Function Name : SpecialSum(SPSUM)
*    Args          : Nil
*    Return Type   : None
*    Application   : This function Adds row index(i) and column index(j) of each element of the 
                     matrix. If this sum is odd, it swaps the element A[i][j] with  A[j][i]. 
                     Then, it prints the sum of each row of this new matrix.
-------------------------------------------------------------------------------------------------*/
void Matrix::SpecialSum()
{
    int tempMatrix[order][order];   //temporary matrix to prevent any changes to original Matrix

    for(int i=0; i<order; i++)  //for loop to verify the asked condition
    {
        for(int j=0; j<=i; j++) //for loop only till j=i, to reduce number of operations to nearly half.
        {
            if((i+j)%2) //swapping if sum of indexes is odd
            {
                tempMatrix[i][j] = matrix[j][i];    //initialing the required matrix as asked in the question
                tempMatrix[j][i] = matrix[i][j];
            }

            else    //not changing the order if sum of indexes is even.
            {
                tempMatrix[i][j] = matrix[i][j];    //initialing the required matrix as asked in the question
                tempMatrix[j][i] = matrix[j][i];
            }
        }
    }

    for(int i=0; i<order; i++)  //for loop to find the sum of elements in each row
    {
        int sum=0; //sum variable initialised to zero
        for(int j=0; j<order; j++) //for loop to traverse across row of the Matrix
        {
            sum+=tempMatrix[i][j]; // sum = sum + tempMatrix[i][j]
        }

        if(i==order-1)
            cout << sum << endl; //printing sum and new line

        else
            cout << sum << ","; //printing sum and space
    }
}

/*-------------------------------------------------------------------------------------------------
*    Function Name : ModMultiplication(MOD)
*    Args          : Nil
*    Return Type   : None
*    Application   : If row index(i) is divisible by 3, then its key is max element of that row.
                     If i gives 1 on division by 3, then its key is minimum element of that row.  
                     else it is the average of the elements of that row. This function gives the
                     product of all keys of the matrix.
-------------------------------------------------------------------------------------------------*/
void Matrix::ModMultiplication()
{
    long long int product = 1;    //variable to save the product of keys of all rows
    for(int i=0; i<order; i++)  //for loop to traverse through rows of the matrix
    {
        int key = matrix[i][0]; //defining key of a matrix to be the first element of the row

        if(i%3==0)  //if i is divisible by row 
        {
            for(int j=1; j<order; j++) //for loop to traverse through the row to find the largest element in the row.
            {
                if(key < matrix[i][j])  //replacing key with a new element of its larger than key.(key = max element)
                {
                    key = matrix[i][j];
                }
            }
        }

        else if(i%3==1)  //if remainder is 1 when divided by i
        {
            for(int j=1; j<order; j++) //for loop to traverse through the row to find the smallest element in the row.
            {
                if(key > matrix[i][j])  //replacing key with a new element of its smaller than key.(key = min element)
                {
                    key = matrix[i][j];
                }
            }            
        }

        else
        {
            for(int j=1; j<order; j++) //for loop to traverse through the row to find the average of elements in the row.
            {
                key = key + matrix[i][j];    //finding sum of all elements
            }
            key = key/order;    //dividing the sum with order to find the average
        }

        product = product*key;  //multiplying the key of every row after finishing the operation on that row.
    }

    cout << product << endl;  //printing the product of all keys of rows of the matrix.
}

/*-------------------------------------------------------------------------------------------------
*    Function Name : MatrixRightShift(MRS)
*    Args          : Another Matrix and an integer for shift
*    Return Type   : None
*    Application   : Perform right shift operation on both the matrices(k times).
                     Print the sum of these shifted matrices.
-------------------------------------------------------------------------------------------------*/
void Matrix::MatrixRightShift(Matrix B, int k)
{
    int j1, i1;
    int tempMatrix[order][order];   //A matrix to store the sum of matrices after shift

    for(int i=0; i<order; i++)  //For loop to traverse across the matrix(row index)
    {
        for(int j=0; j<order; j++)  //For loop to traverse across the matrix(column index)
        {
            j1 = (j+k)%order;   //function to shift the value of j
            i1 = (i+(j+k)/order)%order; //functiion to shift the value of i.

            tempMatrix[i1][j1] = matrix[i][j] + B.matrix[i][j]; //finding the sum ater shift.
        }
    }

    for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
    {
        for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
        {
            cout << tempMatrix[i][j] << " ";   //prints the elements of matrix which is the sum of matrices after shift
        }

        cout << endl; //printing every row in a new line.
    }
}

/*-------------------------------------------------------------------------------------------------
*    Function Name : SpecialMatrixAddition
*    Args          : Another Matrix and an integer for selection
*    Return Type   : None
*    Application   : If x = 1, then perform a transformation on the elements of 1st matrix such 
                     that A[i][j] gets swapped with A[j][i]. Then, add it to the 2nd matrix B and 
                     print the resulting matrix. If x is 2 perform the swap on 2nd matrix.
-------------------------------------------------------------------------------------------------*/
void Matrix::SpecialMatrixAddition(Matrix B, int x)
{
    int tempMatrix[order][order];   //temporary matrix to store the sum after making swap operaation

    if(x==1)    //checking on which matrix swap needs to be performed.
    {
        for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
        {
            for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
            {
                tempMatrix[i][j] = matrix[j][i] + B.matrix[i][j];   //finding sum by swapping elements of Matrix 1. 
            }
        }
    }

    else if(x==2)    //checking on which matrix swap needs to be performed.
    {
        for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
        {
            for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
            {
                tempMatrix[i][j] = matrix[i][j] + B.matrix[j][i];   //finding sum by swapping elements of Matrix 2. 
            }
        }        
    }

    else
        cout << "Invalid Input" << endl;  //Invalid Input of x!=1 and X!=2.

    for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
    {
        for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
        {
            cout << tempMatrix[i][j] << " ";   //prints the elements of matrix which is the sum of matrices after shift
        }

        cout << endl; //printing every row in a new line.
    }
}
/***************Class functions End here***************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : None
*    Application   : Entry Point into the code
-------------------------------------------------------------------------------------------------*/
int main()
{
    int q, order, key;   //variables for number of instructions and order of the matrix and key for deciding shift or selection.
    cin >> q;  //taking input for number of instructions.
    cin >>order;   //taking input for the order of matrix.
    string inputCommand;    //string to take in the entered command.

    int **tempMatrix1 = (int**)malloc(order*sizeof(int*));  //allocating necessary memory to the 2-d pointer array
    int **tempMatrix2 = (int**)malloc(order*sizeof(int*));  //allocating necessary memory to the 2-d pointer array
    for(int i=0; i<order; i++)
    {
        tempMatrix1[i] = (int*)malloc(order*sizeof(int));   //allocating necessary memory to the 2-d pointer array
        tempMatrix2[i] = (int*)malloc(order*sizeof(int));   //allocating necessary memory to the 2-d pointer array
    }
    
    for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
    {
        for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
        {
            cin >> tempMatrix1[i][j];  //taking input for matrix1
        }
    }

    for(int i=0; i<order; i++)  //for loop to traverse across the matrix(row index)
    {
        for(int j=0; j<order; j++)  //for loop to traverse across the matrix(column index)
        {
            cin >> tempMatrix2[i][j];  //taking input for matrix2
        }
    }

    Matrix A(order, tempMatrix1), B(order, tempMatrix2);    //creating objects through the taken inputs.

    for(int i=0; i<q; i++)  //for loop to perform all instructions  
    {
        cin >> inputCommand;    //taking the input command.

        if(inputCommand.compare("SPSUM")==0)    //comparing input instruction with defined instructions
            A.SpecialSum(); //calling the appropriate function

        else if(inputCommand.compare("MOD")==0)    //comparing input instruction with defined instructions
            A.ModMultiplication(); //calling the appropriate function

        else if(inputCommand.compare("MRS")==0)    //comparing input instruction with defined instructions
        {
            cin >> key ; //taking input of necessary second argument
            A.MatrixRightShift(B, key); //calling the appropriate function
        }

        else if(inputCommand.compare("MADD")==0)    //comparing input instruction with defined instructions
        {
            cin >> key; //taking input of necessary second argument
            A.SpecialMatrixAddition(B, key); //calling the appropriate function
        }

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;
    }

    return 0;   //exit call to exit the program after succesful compilation.
}