#include<iostream>
/*-------------------------------------------------------------------------------------------------
*    Author : Maddula Jaya Kamal(cs19b028)
*    Code : CPP code to manage B.tech and dual degree students.
*    Question : Lab0 Sem4
-------------------------------------------------------------------------------------------------*/
class Faculty   //class to represent faculty
{
    public:
    string name; //name of the faculty
    bool status;    //status to indicate visiting or permanent faculty.

    Faculty(string name, bool status) //class constructor of the faculty class
    {
        this->name = name;  //initialising the name of the faculty.
        this->status = status;  //initialising the status of the faculty. 
    }
};

class BTech     //the class to represent B.Tech students.
{
public:
    string r, hostel;  //rollnumber  //hostel name
    Faculty facAd, BTPGuide;   //faculty advisor
    float cgpa; //cgpa

    BTech(string r, string hostel, Faculty facAd, float cgpa)    //class constructor of the B.Tech class. 
    {
        this->r = r;    //initialising roll number
        this->hostel = hostel;  //initialising hostel
        this-> facAd = facAd;   //initialising faculty advisor
        this->cgpa = cgpa;  //initialising cgpa
    }
    string GetHostel(void); //method to get the hostel name of the student.
    Faculty GetFacad(void); //method to get the name of the faculty advisor of the student
    void ChangeHostel(string);  //method to change the hostel of the student
    Faculty GetBTPGuide();  //
    void SetBTPGuide(Faculty);
};

class DualDegree    //the class to represent Dual Degree students.
{
public:
    string r, hostel;  //rollnumber  //hostel name
    Faculty facAd, DDPGuide, TASupervisor;   //faculty advisor
    float cgpa; //cgpa

    DualDegree(string r, string hostel, Faculty facAd, float cgpa)    //class constructor of the B.Tech class. 
    {
        this->r = r;    //initialising roll number
        this->hostel = hostel;  //initialising hostel
        this-> facAd = facAd;   //initialising faculty advisor
        this->cgpa = cgpa;  //initialising cgpa
    }
    string GetHostel(void); //method to get the hostel name of the student.
    Faculty GetFacad(void); //method to get the name of the faculty advisor of the student
    void ChangeHostel(string);  //method to change the hostel of the student
    Faculty GetDDPGuide();  //method to get the project guide of the DD student
    Faculty GetTASupervisor();  //method to get the TA supervisor of the DD student.
    void SetDDPGuide(Faculty);  //method to assign a project guide to a DD student
    void SetTASupervisor(Faculty);  //method to assign a TA supervisor to a DD student.
};

string BTech::GetHostel()
{
    return hostel;  //returns the hostel name
}