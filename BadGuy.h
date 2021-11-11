#ifndef BADGUY_H
#define BADGUY_H
#include <iostream>
using namespace std;

class BadGuy {

private:
    string badGuyName;
    int indexCurrentRoom;
    int health;

public:
    BadGuy(){
        badGuyName = "Filler";
        indexCurrentRoom = 0;
        health = 100;
    };
    
    BadGuy(string n, int in, int h);

    //set user's name
    void setName(string n);

    //return user's name
    string getName() const;

    //set room
    void setIndexCurrentRoom(int in);

    //return index current room
    int getIndexCurrentRoom() const;
    
    //set health
    void setBadGuyHealth(int h);
    
    //get health
    int getBadGuyHealth() const;
    
    //set random name
    void setRandomBadGuyName(int i);

};
#endif //BADGUY_H

