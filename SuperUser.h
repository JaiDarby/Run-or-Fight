#include <iostream>

using namespace std;

#ifndef TEXTBASEDGAME_SUPERUSER_H
#define TEXTBASEDGAME_SUPERUSER_H

#include "User.h"

//Super User as derived class of user
class SuperUser : public User {
public:
	//super user constructors
	SuperUser();
	SuperUser(string nm, int indx);
	//teleport
	void teleport();
	int randRoom; // will get room for user to teleport to
	
	
	
	
	
};

#endif