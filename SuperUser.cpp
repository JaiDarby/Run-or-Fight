#include <iostream>

using namespace std;

#include "SuperUser.h"

SuperUser::SuperUser(string nm, int indx):User(nm, indx){
	this -> setUserType(SUPERUSER);
}
SuperUser::SuperUser():User(){
	this -> setUserType(SUPERUSER);
}
void SuperUser::teleport(){
	if (User::getUserType() == 1){
		cout << User:: getUserName() << " You've teleported to a random room!" << endl;
		do {randRoom = rand()%5;} while (randRoom == User::getIndexofCurrentRoom()); //Gets a room to teleport into
		User::setIndexofCurrentRoom(randRoom); // Puts user in room
	}
}