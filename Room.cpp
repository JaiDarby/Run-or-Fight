//

#include "Room.h"

#include <iostream>
using namespace std;

// Room class
//set the index of the room to the north
void Room::setIndexRoomToNorth(int indx)
{
    this->IndexOfRoomToNorth=indx;
};

//get the index of the room to the north
int Room::getIndexRoomToNorth() const
{
    return this->IndexOfRoomToNorth;
};

//set the index of the room to the south
void Room::setIndexRoomToSouth(int indx)
{
    this->IndexOfRoomToSouth=indx;
};

//get the index of the room to the south
int Room::getIndexRoomToSouth() const
{
    return this->IndexOfRoomToSouth;
};

//set the index of the room to the east
void Room::setIndexRoomToEast(int indx)
{
    this->IndexOfRoomToEast=indx;
};

//get the index of the room to the east
int Room::getIndexRoomToEast() const
{
    return this->IndexOfRoomToEast;
};

//set the index of the room to the west
void Room::setIndexRoomToWest(int indx)
{
    this->IndexOfRoomToWest=indx;
};

//get the index of the room to the West
int Room::getIndexRoomToWest() const
{
    return this->IndexOfRoomToWest;
};

//overloaded <<
ostream& operator <<(ostream& outputStream, const Room& room)
{
    outputStream<<room.Name<<endl;
    outputStream<<room.RoomDescription<<endl;
    return outputStream;
}

/////////////////////////////
