#include<iostream>
#include<string>    //header file for inbuilt library string functions.
#include<sstream>
using namespace std;
/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to carry out a naive implementation of vector
*    Question : CS2810 A4Q1
-------------------------------------------------------------------------------------------------*/

template <class T> class Vector
{
    size_t currentCapacity;    //Stores current total capacity of the vector.
    size_t currentSize; //Stores current number of elements in the vector.
    T* vec;     //Stores the start address of the dynamic array

    public:
        Vector(size_t c)    //class constructor to construct empty vector of capacity c
        {
            this->currentCapacity = c;     //initialising instance variables
            this->currentSize = 0;  //initialising instance variables
            this->vec = new T[c];   //creating an array of size c and storing the head pointer
        }

        Vector(size_t c, T x)   //class construcor to construct a vector of capacity c and all elements initialised to x
        {
            this->currentCapacity = c;     //initialising instance variables
            this->currentSize = c;  //initialising instance variables
            this->vec = new T[c];   //creating an array of size c and storing the head pointer

            for(size_t i=0; i<c; i++)  //for loop to carry out assigning
            {
                vec[i] = x;     //assigning value x to all elements of the vector
            }
        }

        Vector()    //class constructor to construct empty vector of capacity 1
        {
            this->currentCapacity = 1;     //initialising instance variables
            this->currentSize = 0;  //initialising instance variables
            this->vec = new T[1];   //creating an array of size c and storing the head pointer
        }

        ~Vector()   //class destructor to destroy the object and deallocate assigned memory
        {
            delete[] vec;   //deallocating all assigned heap memory
            vec = NULL; //removing stray pointer
        }
    
        void operator=(const Vector& V) //operator to copy objects
        {
            this->currentCapacity = V.currentCapacity;    //copying capacity
            this->currentSize = V.currentSize;  //copying size
            vec = new T[currentCapacity];  //getting new ptr for vec
            for (size_t i = 0; i < currentSize; i++)    //copying elements
                vec[i] = V.vec[i];
        }

        size_t capacity(void);  //function to return the current capacity of the vector
        size_t size(void);      //function to return the current capacity of the vector
        void push(T);           //function to push a new element into the dynamic array
        void pop(void);         //deletes the last element of the dynamic array
        T front();              //returns the first element of the dynamic array
        T back();               //returns the last element of the dynamic array
        T operator [] (size_t);   //returns ith element in the vector
        void sort(void);        //Sort the vector in ascending

    protected:
        void quickSort(size_t, size_t);       //implements quicksort algorithm
        size_t partition(size_t, size_t);        //Implements the partition algorithm for the sort
};


                /******************** THE VECTOR FUNCTIONS BEGIN HERE ********************/
/*-------------------------------------------------------------------------------------------------
*    Function Name : capacity (Vector)
*    Args          : Nil
*    Return Type   : size_t
*    Application   : This Function returns the current capacity of the vector
-------------------------------------------------------------------------------------------------*/
template<class T>
size_t Vector<T>::capacity()
{
    return currentCapacity;    //returning the required value
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : size (Vector)
*    Args          : Nil
*    Return Type   : size_t
*    Application   : This Function returns the current size of the vector
-------------------------------------------------------------------------------------------------*/
template<class T>
size_t Vector<T>::size()
{
    return currentSize;    //returning the required value
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : push (Vector)
*    Args          : T (template type variable)
*    Return Type   : Nil
*    Application   : This Function inserts new element into the queue an resizes it when needed
-------------------------------------------------------------------------------------------------*/
template<class T>
void Vector<T>::push(T newElem)
{
    //cout << newElem <<endl; //debugging statement
    if(currentSize<currentCapacity)   //if the current size is less than the capacity of dynamic array
    {
        vec[currentSize] = newElem; //add the new element at the end
        currentSize++;  //incrimenting the current size
    }

    else    //if array is full then resize it
    {
        T* tempVec = new T[2*currentCapacity];     //getting a new array of double capacity

        for(size_t i=0; i<currentCapacity; i++)   //for loop to copy all elements into the new array
        {
            tempVec[i] = vec[i];    //copying elements one by one
        }
        delete[] vec;   //freeing the old pointers allocated heap memory
        tempVec[currentSize] = newElem; //adding a last element at the end
        currentSize++;  //incrimenting the current size
        vec = tempVec;  //assigning vec the pointer to new heap memory
        currentCapacity = 2*currentCapacity; 
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : pop (Vector)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function deletes the last element in the dynamic array
-------------------------------------------------------------------------------------------------*/
template<class T>
void Vector<T>::pop()
{
    if(currentSize)     //if array isnt empty
        currentSize--;  //reduce the current size
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : front (Vector)
*    Args          : Nil
*    Return Type   : T (template type)
*    Application   : This Function gives the first element of the dynamic array
-------------------------------------------------------------------------------------------------*/
template<class T>
T Vector<T>::front()
{
    if(currentSize)     //if array isnt empty
        return vec[0];  //return element at the zero index

    return -1;  //return -1 if array is empty
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : back (Vector)
*    Args          : Nil
*    Return Type   : T (template type)
*    Application   : This Function gives the last element of the dynamic array
-------------------------------------------------------------------------------------------------*/
template<class T>
T Vector<T>::back()
{
    if(currentSize)     //if array isnt empty
        return vec[currentSize-1];  //return element at the last index

    return -1;  //return -1 if array is empty
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : [] (operator)(Vector)
*    Args          : size_t
*    Return Type   : T (template type)
*    Application   : This Function gives the element at a particular index of the dynamic array
-------------------------------------------------------------------------------------------------*/
template<class T>
T Vector<T>::operator[] (size_t index)
{
    if(currentSize && index<currentSize)    //if array is non empty and index is assigned
        return vec[index];  //return the element at index i

    return -1;  //if index i is not assigned or vector is empty
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : sort (Vector)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This function sorts the array using quick sort and prints sorted array
-------------------------------------------------------------------------------------------------*/
template<class T>
void Vector<T>::sort()
{
    quickSort(0, currentSize-1);    //calling the sort

    for(size_t i=0; i<currentSize; i++)    //for loop to traverse across vector
        cout << vec[i] << " ";  //printing element by element

    cout << endl;   //printing a new line after printing the array
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : sort (Vector)
*    Args          : 2 size_t s(bound of region of array)
*    Return Type   : Nil
*    Application   : This function sorts the selected part of array using recursion
-------------------------------------------------------------------------------------------------*/
template<class T>
void Vector<T>::quickSort(size_t low, size_t high)
{
    if(low<high)    //while a valid region exists
    {
        size_t partitionVal = partition(low, high);    //getting a partition using a predefined pivot

        quickSort(partitionVal+1, high);   //calling recursion for rest of the array
        quickSort(low, partitionVal);    //calling recursion for rest of the array
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : sort (Vector)
*    Args          : 2 size_t s(bound of region of array)
*    Return Type   : size_t
*    Application   : This function provides partition using 1st element as pivot
-------------------------------------------------------------------------------------------------*/
template<class T>
size_t Vector<T>::partition(size_t low, size_t high)
{
    T pivot = vec[low];     //fixing the pivot
    T temp;     //temporary variable to carry out swapping
    size_t countr = high+1, countl = low-1;  //counter for helping trvaersal   

    while(1)    //while true repeat this
    {
        do{
            countl++;   //incriment the left index 
        }while(vec[countl] < pivot);    //as long as element is less than pivot

        do{
            countr--;   //decrimenting the right index
        }while(vec[countr] > pivot);    //as long as element is greater than pivot

        if(countl >= countr)    //only way to exit the while loop
        {
            return countr;
        }

        temp = vec[countr];     //sequence of steps to swap the numbers
        vec[countr] = vec[countl];
        vec[countl] = temp;
    }
}
                /******************** THE VECTOR FUNCTIONS END HERE ********************/


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    int instructionsNum, temp2=-1;
    size_t temp1=0;   //initialising all necessary inputs
    string command;    //temporary string to store commands
    Vector<int> V;
    
    getline(cin, command);  //taking the entire line as an input
    stringstream str_strm; //using string stream to break the first input line
    
    str_strm << command;    //splitting words
    str_strm >> command >> temp1 >> temp2;  //seperating the stream of strings

    if(temp1>0) //if there exists a value for temp1 then
    {
        if(temp2!=-1)   //if there exists a value for temp2 then 
        {
            Vector<int> V1(temp1, temp2);   //calling class constructor with 2 arguments
            V = V1; //copy object operator
        }

        else    //if temp2 is not given as input
        {
            Vector<int> V1(temp1);   //calling class constructor with 1 argument
            V =V1;  //copy object operator
        }
    }

    cin >> instructionsNum;
    while(instructionsNum)
    {
        cin >> command;
        if(command.compare("push")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp2; //taking input of necessary argument
            //cout << temp1 <<endl;
            V.push(temp2);  //calling the respective function 
        }

        else if(command.compare("pop")==0)    //comparing input instruction with defined instructions
            V.pop();  //calling the respective function 

        else if(command.compare("front")==0)    //comparing input instruction with defined instructions
            cout << V.front() << endl;  //calling the respective function 

        else if(command.compare("back")==0)    //comparing input instruction with defined instructions
            cout << V.back() << endl;  //calling the respective function    

        else if(command.compare("capacity")==0)       //comparing input instruction with defined instructions
            cout << V.capacity() << endl;  //calling the respective function 

        else if(command.compare("size")==0)       //comparing input instruction with defined instructions
            cout << V.size() << endl;  //calling the respective function 

        else if(command.compare("sort")==0)       //comparing input instruction with defined instructions
            V.sort();  //calling the respective function 

        else if(command.compare("element")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp2; //taking input of necessary argument
            cout << V[temp2] <<endl;  //calling the respective function 
        }

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;

        instructionsNum--;      //decrimenting instruction count to denote number of instructions left
    }

    return 0;   //returning 0 to exit the program
}