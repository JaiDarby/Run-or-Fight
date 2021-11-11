//
//

#include <iostream>
using namespace std;

#include "User.h"

//////////////////////////////
//get & set name
string User::getUserName()
{
    return this->name;
}

void User::setUserName(string  nm)
{
this->name = nm;
}

void User::setUserType(int type){
    this -> UserType = type;
}

int User:: getUserType() const {
    return this -> UserType;
}

//////////////////////////////
//get & set Current Room
int User::getIndexofCurrentRoom()  const
{
    return this->indexCurrentRoom;
}

void User::setIndexofCurrentRoom(int  indexRoom)
{
    this->indexCurrentRoom = indexRoom;
}
int User::IndNextUser=0;

void User::setCurrentPLayer(int Size)
{
    IndNextUser++;
    if (IndNextUser>=Size)
        IndNextUser=0;
}

void User::teleport(){
    if (User::getUserType() != 1){
        cout << User::getUserName() << " you are not a Super User." << endl << "**********************" <<endl;

    }
}

int User::getHealth() const {
    return this ->Health;
}

void User::setHealth(int h){
    this->Health = Health - h;
}