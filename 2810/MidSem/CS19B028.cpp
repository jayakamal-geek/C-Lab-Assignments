#include<iostream>  //header for general C++ default functions.
#include<cmath>    //header file for math functions
using namespace std;    //defining name space in global scope

/*-------------------------------------------------------------------------------------------------
*    Author   : Maddula Jaya Kamal(cs19b028)
*    Code     : CPP code to Represent Vendors Supplyting to IIT Madras
*    Question : CS2810 MidSem
-------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------
*    Class Name         : Vendor
*    Application        : Used to digitally represent Vendors
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class Vendor
{
    public:
        int printerPrice, monitorPrice, cpuPrice, chairPrice, tablePrice;   //variables to represent prices of commodities
        int vendorID, iitmDiscount, discount[5], equipCount;    //variables to store unique varibles and discount
        float customerRating, avgDisc;   //variable to store rating of the vendor

        bool operator > (Vendor V2)    //operator to compare vendors on given Criteria
        {
            if(this->equipCount > V2.equipCount)   //comparing equipment count
                return true;

            if(this->equipCount == V2.equipCount)   //on equalEqip count
            {
                if(this->customerRating > V2.customerRating)   //comparing customer rating
                    return true;

                if(this->customerRating == V2.customerRating)   //on equal custom rating
                {
                    if(this->avgDisc > V2.avgDisc) //comparing average Discount
                        return true;
                }
            }

            return false;   //default return
        }
};


/*-------------------------------------------------------------------------------------------------
*    Class Name         : VendorList
*    Application        : Used to digitally manage all Vendors
*    Inheritances       : Nil
-------------------------------------------------------------------------------------------------*/
class VendorList
{
    Vendor* list, *tempList;   //array to store all the vendors in a list
    int N;  //stores the number of vendors

    public:
        VendorList(int N)   //class constructor with number of vendors as input
        {
            this->N = N;    //initialising instance variable of class
            this->list = new Vendor[N]; //allocating required heap memory
        }

        ~VendorList()   //class destructor
        {
            delete[] list;  //deallocating the heap memory
            list = NULL;    //preventing pointing stray pointers
            tempList = NULL;    //preventing pointing stray pointers
        }

        void input(void);   //class function to take inputs for vendor details
        void Sort(void);    //function for sorting all the vendors according to given constraints
        void mergeSort(int, int);   //a divide and conquer function
        void merge(int, int);   //merges sorted sub arrays
        void newVariance(void);  //function to calculate new variance
        float max(float, float);  //returns max of 2 numbers
};


                /******************** THE CLASS FUNCTIONS BEGIN HERE ********************/
float VendorList::max(float i, float j)
{    return(i>j) ? i : j;}
/*-------------------------------------------------------------------------------------------------
*    Function Name : input (VendorList)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function takes inputs of all vendors
-------------------------------------------------------------------------------------------------*/
void VendorList::input(void)
{
    for(int i=0; i<N; i++)  //for loop to take in all inputs
    {   
        int count =0;   //variable for finding number of equipments
        float sum = 0;  //variable finding average discount
        cin >> list[i].printerPrice >> list[i].monitorPrice >> list[i].cpuPrice >> list[i].chairPrice >> list[i].tablePrice;    //taking inputs of all prices
        cin >> list[i].customerRating >> list[i].iitmDiscount;  //input for customerRating and iitmDiscount

        for(int j=0; j<5; j++)
            cin >> list[i].discount[j];     //taking discounts on individual products

        cin >> list[i].vendorID;    //taking input of the vendor ID

        if(list[i].printerPrice)    //finding number of equipments
            count++;    //incrimenting count

        if(list[i].monitorPrice)    //finding number of equipments
            count++;    //incrimenting count

        if(list[i].cpuPrice)    //finding number of equipments      
            count++;    //incrimenting count

        if(list[i].chairPrice)    //finding number of equipments
            count++;    //incrimenting count

        if(list[i].tablePrice)    //finding number of equipments
            count++;    //incrimenting count

        list[i].equipCount = count; //assigning number of equipments

        for(int j=0; j<5; j++)
            sum = sum + max((float)list[i].iitmDiscount, list[i].discount[j]);    //finding total discount

        sum = sum/5;    //finding average
        list[i].avgDisc = sum;  //assigning average discount
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : Sort (VendorList)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function sorts vendors according to givenConstraints
-------------------------------------------------------------------------------------------------*/
void VendorList::Sort(void)
{
    tempList = new Vendor[N];

    for(int i=0; i<N; i++)
        tempList[i] = list[i];  //copying all elements into a new array
    mergeSort(0, N-1);  //calling a mergeSort
    delete[] tempList;  //deallocating all allotted heap memories

    for(int i=0; i<N; i++)
        cout << list[i].vendorID << " ";

    cout << endl;  //printing a new line
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : mergeSort (VendorList)
*    Args          : 2 integers(int)
*    Return Type   : Nil
*    Application   : This Function sorts array using divide and conquer
-------------------------------------------------------------------------------------------------*/
void VendorList::mergeSort(int low, int high)
{
    if(low<high)    //do only when a subbarray of length greater than 1 exists
    {
        int middle = (low+high)/2;  //calculating the middle index to split the array
        mergeSort(low, middle); //sorting the first half subarray
        mergeSort(middle+1, high);  //sorting the second half subarray
        merge(low, high);   //merging the sorted posrtions of the subArray
    }
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : merge (VendorList)
*    Args          : 2 integers(int)
*    Return Type   : Nil
*    Application   : This Function merges two sorted subArrays
-------------------------------------------------------------------------------------------------*/
void VendorList::merge(int low, int high)
{
    int i = low, j = low, k, middle = (low+high+2)/2;    //necessary variables to compute cross inversions
    k = middle;

    while(i<middle && k <= high)    //while elements from subArrays can be compared
    {
        if(list[i] > list[k])
            tempList[j++] = list[i++];  //merging into a new array

        else
            tempList[j++] = list[k++];  //merging into a new array
    }

    while(i <middle)
        tempList[j++] = list[i++];  //merging arrays

    while(k <= high)
        tempList[j++] = list[k++];  //merging arrays

    for(int m =low; m<=high; m++)
        list[m] = tempList[m];  //copying all elements into main array
}


/*-------------------------------------------------------------------------------------------------
*    Function Name : newVariance (VendorList)
*    Args          : Nil
*    Return Type   : Nil
*    Application   : This Function merges two sorted subArrays
-------------------------------------------------------------------------------------------------*/
void VendorList::newVariance(void)
{
    int medianIndex = list[N/2].vendorID;    //defining necessary variables
    long long int sum =0;

    for(int i=0; i<N; i++)
    {
        int diff = medianIndex - list[i].vendorID;  //computing the difference
        sum = sum + diff*diff;  //updating the sum
    }

    sum = ceil((float)sum/N);  //computing smallest integer greter than variance
    cout << sum;    //printing the sum
}
                /******************** THE CLASS FUNCTIONS END HERE ********************/

/*-------------------------------------------------------------------------------------------------
*    Function Name : main
*    Args          : Nil
*    Return Type   : int(0)
*    Application   : Entry point to the Program
-------------------------------------------------------------------------------------------------*/
int main()
{
    int numVendors; //variable to store number of vendors
    cin >> numVendors;  //taking input for number of vendors

    VendorList V(numVendors);   //creating a new object of class VendorList

    V.input();  //taking input for the object
    V.Sort();   //calling the member function to sort
    V.newVariance();    //calling the new variance function

    return 0;   //returning 0 to exit the code
}