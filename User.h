//
//

#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

//Enumerated datatype UserTypes
enum UserTypes {NORMAL, SUPERUSER, UNKNOWN};

class User {
private:
string name;
int indexCurrentRoom;
int UserType;
int Health;

public:
//constructors
User(){
    this->name = "Jai'Mir D.";
    this->indexCurrentRoom=4;
    this->UserType=0;
    this-> Health = 100;
}

User(string nm,int rm){
this->name=nm;
this->indexCurrentRoom=rm;
this->UserType=0;
this ->Health = 100;
}

static int IndNextUser;

virtual void teleport();

void setUserType (int type);
int getUserType () const;

//get & set name
string getUserName();
void setUserName(string  nm);
//get & set Current Room
int getIndexofCurrentRoom() const;
void setIndexofCurrentRoom(int  indexRoom);

static void setCurrentPLayer(int MaxIndex);

//set health
void setHealth(int h);
    
//get health
int getHealth() const;


//overload <<
friend ostream& operator <<(ostream& outputStream, const User& u)
{
    outputStream<<u.name;
    return outputStream;
};

//overload ==
bool operator == (User& u2) {
    return (this->indexCurrentRoom==u2.indexCurrentRoom);
};

};



#endif //USER_H
