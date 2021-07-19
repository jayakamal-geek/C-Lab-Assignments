#include<iostream>
#include<string>    //header file for inbuilt library string functions.
using namespace std;    //defining name space in global scope

/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to Represent and manage operations at BloomBrain
*    Question : CS2810 A5Q1
-------------------------------------------------------------------------------------------------*/

class Room
{
    public:
    bool occupied = true;   //initially maeking all rooms as occupied
    int seraphic;   //variable to store seraphic of person in that room
};

/*-------------------------------------------------------------------------------------------------
*    Class Name         : BloomBrain
*    Application        : Used to digitally represent and manage mental health care center  
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class BloomBrain
{
    Room* room;  //array of class Room representing rooms
    int roomCount, occupiedCount;    //count total rooms

    public:
        BloomBrain(int roomCount)   //class constructor
        {
            this->roomCount = roomCount; //total number of available rooms
            this->room = new Room[roomCount];    //getting an array of required size to represent room
            this->occupiedCount = roomCount;
        }

        ~BloomBrain()
        {
            delete[] room;  //deallocating the heap memory to while destroying class to prevent memory leaks
        }

        long long update(int*);   //function to return number of quality talks possible 
        void join(int);     //allots the highest unoccupied room to new entry
        void leave(int);    //a function to vacate the required room
        int occupied(void); //returns the number of rooms occupied at a particular point of time
        int play(void);     //determines the minimum required seraphic number of the guru
        int* maxSum(int, int);   //returns max sum in a given sub array using recursion
        long long talkCount(int, int, int*, int*); //recursive function to compute number of talks at a lower complexity
        long long merger(int, int, int*, int*);   //finding cross inversions
        int max(int, int);  //returns max of 2 numbers
};


                /******************** THE CLASS FUNCTIONS BEGIN HERE ********************/

int BloomBrain::max(int i, int j)
{    return(i>j) ? i : j;}
/*-------------------------------------------------------------------------------------------------
*    Function Name : update (BloomBrain)
*    Args          : An array of integers(int)
*    Return Type   : Integer(long long)
*    Application   : This Function returns the number of possible quality talks
-------------------------------------------------------------------------------------------------*/
long long BloomBrain::update(int* seraphic)
{
    int count = 0;
    int* tempArr = new int[roomCount];
    long long talks = 0;

    for(int i=0; i<roomCount; i++)  //copying all the data into the class array
    {
        if(room[i].occupied)
        {        
            room[i].seraphic = seraphic[i];  //copying seraphic values from input into the class
            tempArr[count] = seraphic[i];   //getting occupied elements into new Array
            count++;    //incrimenting the count
        }
    }
    talks = talkCount(0, count-1, tempArr, seraphic);
    delete[] tempArr;   //deallocating heap memory to prevent memory leaks
    return talks;   //returning the total number of quality talks
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : talkCount (BloomBrain)
*    Args          : 2 Integers(int) and 2 integer pointers(int*)
*    Return Type   : Integer(long long)
*    Application   : This Function returns the number of inversions in a given part of array
-------------------------------------------------------------------------------------------------*/
long long BloomBrain::talkCount(int low, int high, int* tempArr, int* seraphic)
{
    int middle;
    long long count=0;

    if(low<high)
    {
        middle = (low+high)/2;  //computing the middle number

        count = count + talkCount(low, middle, tempArr, seraphic); //adding value of left half
        count = count + talkCount(middle+1, high, tempArr, seraphic);  //adding value of right half
        count = count + merger(low, high, tempArr, seraphic);  //adding cross inversions
    }

    return count;   //returning the total number of inversions
}

/*-------------------------------------------------------------------------------------------------
*    Function Name : merger (BloomBrain)
*    Args          : 2 Integers(int) and 2 integer pointers(int*)
*    Return Type   : Integer(long)
*    Application   : This Function returns the number of cross inversions
-------------------------------------------------------------------------------------------------*/
long long BloomBrain::merger(int low, int high, int* tempArr, int* seraphic)
{
    int i = low, j = low, k, middle = (low+high+2)/2;    //necessary variables to compute cross inversions
    long long count = 0; //to count number of cross inversions
    k = middle;

    while(i<middle && k <= high)
    {
        if(tempArr[i] <= tempArr[k])
        {
            seraphic[j] = tempArr[i];   //merging arrays into new array
            j++;    //inrimenting j
            i++;    //incrimenting k
        }

        else
        {
            seraphic[j] = tempArr[k];    //merging arrays into new array
            j++;    //incrimenting j
            k++;    //incrimenting k
            count = count + middle - i; //incrimenting cross count
        }
    }

    while(i < middle)
    {
        seraphic[j] = tempArr[i];   //merging arrays into new array
        j++;    //inrimenting j
        i++;    //incrimenting k
    }

    while(k<=high)
    {
        seraphic[j] = tempArr[k];
        j++;    //incrimenting j
        k++;    //incrimenting k     
    }

    for(int i=low; i<=high; i++)
        tempArr[i] = seraphic[i];   //copying back the sorted array
        
    return count;
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : join (BloomBrain)
*    Args          : Integer(int)
*    Return Type   : Integer(int)
*    Application   : This Function allots highest unoccupied room to the newcomer
-------------------------------------------------------------------------------------------------*/
void BloomBrain::join(int seraphic)
{
    for(int i=roomCount-1; i>-1; i--)   //for loop to check for an unoccupied room
    {
        if(!room[i].occupied)    //if an unoccupied room is found
        {
            room[i].seraphic = seraphic; //allott that room by copying new seraphic numbers
            room[i].occupied = true;    //marking the room as occupied
            occupiedCount++;    //incrimenting the occupied rooms count
            break;  //exit the loop
        }
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : occupied (BloomBrain)
*    Args          : Nil
*    Return Type   : Integer(int)
*    Application   : This Function returns the number of rooms occupied at any time
-------------------------------------------------------------------------------------------------*/
int BloomBrain::occupied()
{
    return occupiedCount;   //returning number of rooms occupied
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : leave (BloomBrain)
*    Args          : Integer(int)
*    Return Type   : Nil
*    Application   : This Function vacates the required room and marks it as unoccupied
-------------------------------------------------------------------------------------------------*/
void BloomBrain::leave(int index)
{
    room[index].occupied = false;   //marking a room as unoccupied after vacating it
    room[index].seraphic = 0;   //erasing value
    occupiedCount--;
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : play (BloomBrain)
*    Args          : Nil
*    Return Type   : Integer
*    Application   : This Function returns the minimum required seraphic number of guru
-------------------------------------------------------------------------------------------------*/
int BloomBrain::play()
{
    int* tempResults = maxSum(0, roomCount-1);  //calling the maximum sum of elements of a subarray
    return tempResults[3];
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : maxSum (BloomBrain)
*    Args          : 2 integers(int)
*    Return Type   : Integer pointer(int*)
*    Application   : Divide and conquer function for finding max sum of sub array
-------------------------------------------------------------------------------------------------*/
int* BloomBrain::maxSum(int low, int high)
{
    int* tempResults = new int[4];  //temporary results
    int middle = (low + high)/2;    //bifurcation of array

    if(high == low)   //if array size is 1
    {
        tempResults[0] = room[low].seraphic;    //base case returns
        tempResults[1] = room[low].seraphic;    //base case returns
        tempResults[2] = room[low].seraphic;    //base case returns
        tempResults[3] = room[low].seraphic;    //base case returns
        return tempResults;
    }

    int* tempResults1 = maxSum(low, middle);  //calling the function for one hallf of the subarray
    int* tempResults2 = maxSum(middle+1, high);  //calling the function for one hallf of the subarray

    tempResults[0] = tempResults1[0] + tempResults2[0]; //making necessary computations //sum
    tempResults[1] = max(tempResults1[1], tempResults1[0] + tempResults2[1]); //making necessary computations //sufMax
    tempResults[2] = max(tempResults1[2] + tempResults2[0], tempResults2[2]); //making necessary computations //prefMax
    tempResults[3] = max(max(tempResults1[3], tempResults2[3]), tempResults1[2] + tempResults2[1]); //making necessary computations //answer

    return tempResults; //returning the results
}

                /******************** THE CLASS FUNCTIONS END HERE ********************/


/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Proram
-------------------------------------------------------------------------------------------------*/
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int size, query, temp;  //all variables required to functions and take input
    string command;

    cin >> size;    //taking input for the size
    BloomBrain A(size); //creating a new integer array to take inputs for updates
    int* seraphic = new int[size];  //creating a temporary array to take inputs of seraphic values

    cin >> query;   //getting number of queries

    while(query)    //while loop to execute instructions
    {
        cin >> command; //taking string input of the command

        if(command.compare("update")==0)    //comparing input instruction with defined instructions
        {
            for(int i=0; i<size; i++)   //for loop to take an array input
                cin >> seraphic[i]; //taking input of necessary argument

            cout << A.update(seraphic) << endl;  //calling the respective function    
        }

        else if(command.compare("join")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp; //taking input of necessary argument
            A.join(temp);  //calling the respective function 
        }

        else if(command.compare("occupied")==0)    //comparing input instruction with defined instructions
            cout << A.occupied() << endl;  //calling the respective function    

        else if(command.compare("leave")==0)    //comparing input instruction with defined instructions
        {
            cin >> temp; //taking input of necessary argument
            A.leave(temp);  //calling the respective function
        }

        else if(command.compare("play")==0)    //comparing input instruction with defined instructions
            cout << A.play() << endl;  //calling the respective function 

        else //failsafe to prevent program misbehaviour on passing undefined arguments
            cout << "Invalid Command" << endl;

        query--;    //decrimenting the number of instructions to be performed
    }

    return 0;   //returning 0 to exit the program
}