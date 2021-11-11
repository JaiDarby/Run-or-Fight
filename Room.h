//
//
#ifndef GAMESTART_ROOM_H
#define GAMESTART_ROOM_H

#include <iostream>
using namespace std;

class Room {
private:
        string Name;
        string RoomDescription;
        int IndexOfRoomToNorth;
        int IndexOfRoomToSouth;
        int IndexOfRoomToEast;
        int IndexOfRoomToWest;
        public:
        // return the name of the room
        string getName()  const{
            return this->Name;
        };

        //set the name of the room
        void setName(string nm) {
            this->Name = nm;
        };

        // return the description of the room
        string getRoomDescription()  const{
            return this->RoomDescription;
        };

        //set the Description of the room
        void setRoomDescription(string desc) {
            this->RoomDescription = desc;
        };
        //set the index of the room to the north
        void setIndexRoomToNorth(int indx);
        //get the index of the room to the north
        int getIndexRoomToNorth() const;

        //set the index of the room to the south
        void setIndexRoomToSouth(int indx);
        //get the index of the room to the south
        int getIndexRoomToSouth() const;

        //set the index of the room to the east
        void setIndexRoomToEast(int indx);
        //get the index of the room to the east
        int getIndexRoomToEast() const;

        //set the index of the room to the west
        void setIndexRoomToWest(int indx);
        //get the index of the room to the West
        int getIndexRoomToWest() const;

        //overload <<
        friend ostream& operator <<(ostream& outputStream, const Room& room);

};

#endif //GAMESTART_ROOM_H
