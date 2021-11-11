#TextBasedGamePart8 makefile

TextBasedGamePart8: TextBasedGamePart8.o User.o Room.o BadGuy.o SuperUser.o SpecialList.o
	g++ -std=c++11 TextBasedGamePart8.o User.o Room.o BadGuy.o SuperUser.o SpecialList.o -o TextBasedGamePart8

TextBasedGamePart8.o: TextBasedGamePart8.cpp User.h Room.h SuperUser.h BadGuy.h SpecialList.h
	g++ -c -std=c++11 TextBasedGamePart8.cpp

User.o: User.cpp User.h
	g++ -c -std=c++11 User.cpp

Room.o: Room.cpp Room.h
	g++ -c -std=c++11 Room.cpp

BadGuy.o: BadGuy.cpp BadGuy.h
	g++ -c -std=c++11 BadGuy.cpp

SuperUser.o: SuperUser.cpp SuperUser.h
	g++ -c -std=c++11 SuperUser.cpp

SpecialList.o: SpecialList.cpp SpecialList.h
	g++ -c -std=c++11 SpecialList.cpp
	
clean:
	rm -rf *.o TextBasedGamePart7

