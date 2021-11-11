
#include "BadGuy.h"
#include <iostream>
using namespace std;

BadGuy::BadGuy(string n, int in, int h) : badGuyName(n), indexCurrentRoom(in), health(h) {};


//set bad guy name
void BadGuy::setName(string n) {
    badGuyName = n;
}
//return bad guy name
string BadGuy::getName() const {
    return badGuyName;
}
//set bad guy current room
void BadGuy::setIndexCurrentRoom(int in) {
    indexCurrentRoom = in;
};
//return bad guy current room
int BadGuy::getIndexCurrentRoom() const {
    return indexCurrentRoom;
}
void BadGuy::setBadGuyHealth(int h) {
    health = h;
}
int BadGuy::getBadGuyHealth() const{
    return health;
}
void BadGuy::setRandomBadGuyName(int i){
    string BadGuyNamesList[] = {"Johnny Johnny", "Weirdo Wally", "Malcious Malcom", "Agressive Adam", "Sicko Sally", "Terrible Terrance", "Bully Bobby", "Creepo Chris", "Killer Kyle", "Maneater Manny"};
    badGuyName = BadGuyNamesList[i];
}