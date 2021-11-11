#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <time.h>
#include <random>
#include <algorithm>

#include "Room.h"
#include "User.h"
#include "BadGuy.h"
#include "SuperUser.h"
#include "SpecialList.h"
#include "SpecialList.cpp"


using namespace std;
//number of rooms
const int NUM_ROOMS = 5;

////////////////////////////////////////////////////
// sets up rooms);
void initRooms(Room rooms[]);

// sets up user and current room index
void initUser(User* players);

//User selects an action
template<class T>
void promptUserAction(vector<T*> players, int playernumber, const Room rooms[], string &strCh, vector<BadGuy> badGuy1, int NumBadGuys);

//implement Users Action
template<class T>
void implementUserAction(vector<T*> *players, int playernumber, const Room rooms[], string &strCh, vector<BadGuy> &badGuy1, int NumBadGuys, SpecialList<User> *unlucky);

//save current player information
void savePlayerData(User u);

//load saved player data
template<class T>
void loadPlayerData(vector<T*> *allUsers);

//clear player data
void ClearFile();

//Moves bad guys
template<class T>
void moveBadGuy(vector<BadGuy> &badGuy1, const Room rooms[], int NumBadGuys, vector<T*> players);

//Add players to list
template<class T>
void addPlayers(vector<T*> players, const Room rooms[], vector<BadGuy> badguy1, SpecialList<User> *unlucky, int NumBadGuys);

int main() {
    srand(time(0));

    Room rooms[NUM_ROOMS];

    //creates object of Users class to initialize class variables
    User user1("Jai'Mir Darby", 4);
    User user2;

    //creates a vector of user names
    vector<User*> players;
    
    //Creates list of unlucky players
    SpecialList<User> unlucky;

    //initialize user and rooms
    initRooms(rooms);    
    
    string loadSavedInput;
    cout << "Would you like to load your saved game? (Y/N): " << endl;
    cin >> loadSavedInput;

    if ((loadSavedInput == "Y" || loadSavedInput == "y"))
    {
        players.push_back(&user1);
        players.push_back(&user2);
        loadPlayerData(&players);
    }
    else
    {
        User * user1 = new User;
        SuperUser * user2 = new SuperUser;
        initUser(user1);
        players.push_back(user1);
        players.push_back(user2);
        
    }

    ClearFile();

    //welcome
    cout << "Welcome to my game!" << endl << "**********************" << endl;
    
    int NumBadGuys;
    do {
        cout <<"How many enemies would you like to play against? " << endl;
        cin >> NumBadGuys;
        if (NumBadGuys < 1){cout << "Sorry, you need to go against someone" << endl;}
        else if (NumBadGuys > 10){cout << "You can only go against 10 bad guys max!" << endl;}
    }while ((NumBadGuys < 1) || (NumBadGuys > 10));
    
    BadGuy* BadGuyPointer;
    BadGuyPointer = new BadGuy[NumBadGuys];
    vector<BadGuy> badGuy1;
    for (int i = 0; i < NumBadGuys; i++){
        badGuy1.push_back(*(BadGuyPointer+i));
        badGuy1[i].setRandomBadGuyName(i);
        badGuy1[i].setIndexCurrentRoom(rand()%NUM_ROOMS);
    }
    

    string UserAction;
    do {

        promptUserAction(players, User::IndNextUser, rooms, UserAction,badGuy1, NumBadGuys);
        addPlayers(players, rooms, badGuy1, &unlucky, NumBadGuys);
        implementUserAction(&players, User::IndNextUser, rooms, UserAction, badGuy1, NumBadGuys, &unlucky);
        

        for (int i = 0; i < NumBadGuys; i++){
            if((badGuy1.size() > 0) && (badGuy1[i].getBadGuyHealth() <= 0)){
                cout << badGuy1[i].getName() << " has been eliminated!" << endl << badGuy1.size() - 1 << " enemies remain!" << endl;
                badGuy1.erase(badGuy1.begin() + i);
                cout << "**********************" << endl;
                NumBadGuys --;
            }
        }

        if ((UserAction == "Q") || (UserAction == "q")) {
            string SaveData;
            cout << "Would you like to load your saved game? (Y/N): " << endl;
            cin >> SaveData;

            if ((SaveData == "Y" || SaveData == "y"))
            {
                savePlayerData(*players[User::IndNextUser]);
            }

            players.erase(players.begin() + User::IndNextUser);
        }

        if (User::IndNextUser==players.size()-1)
            moveBadGuy(badGuy1,rooms, NumBadGuys, players);

        User::setCurrentPLayer(players.size());
        
        for (int i = 0; i < players.size(); i++){
            if((players.size() > 0) && (players[i]->getHealth() <= 0)){
                cout << players[i]->getUserName() << " has been eliminated!" << endl;
                players.erase(players.begin() + i);
                cout << "**********************" << endl;
            }
        }

    } while (players.size() > 0);
    cout << "Game Over! Thank you for playing!" << endl;
    return 0;
}

// Initializes user.

void initUser(User* player) {
    //prompt and set  user name.
    cout << "What is your name? " << endl;
    string nm; //temp value.
    cin >> nm; // holds name.6
    player->setUserName(nm);
    //set room starting index
    player->setIndexofCurrentRoom(2);
}

// sets up rooms
void initRooms(Room rooms[]) {

    //init Cave
    (rooms+0)->setName("Cave");
    (rooms+0)->setIndexRoomToNorth(4);
    (rooms+0)->setIndexRoomToSouth(1);
    (rooms+0)->setIndexRoomToEast(-99);
    (rooms+0)->setIndexRoomToWest(-99);
    (rooms+0)->setRoomDescription("The cave is dark and cold, you won't want to stay here long.");

    //init Forest
    (rooms+1)->setName("Forest");
    (rooms+1)->setIndexRoomToNorth(0);
    (rooms+1)->setIndexRoomToSouth(-99);
    (rooms+1)->setIndexRoomToEast(2);
    (rooms+1)->setIndexRoomToWest(3);
    (rooms+1)->setRoomDescription("You exit south of the cave and walk into a forest of giant birch trees");

    //Room 3
    (rooms+2)->setName("Dessert");
    (rooms+2)->setIndexRoomToNorth(-99);
    (rooms+2)->setIndexRoomToSouth(-99);
    (rooms+2)->setIndexRoomToEast(-99);
    (rooms+2)->setIndexRoomToWest(1);
    (rooms+2)->setRoomDescription("Its super hot and dry, you see a camel in the distance.");
    //Room 4
    (rooms+3)->setName("Snow Mountain");
    (rooms+3)->setIndexRoomToNorth(-99);
    (rooms+3)->setIndexRoomToSouth(-99);
    (rooms+3)->setIndexRoomToEast(1);
    (rooms+3)->setIndexRoomToWest(-99);
    (rooms+3)->setRoomDescription("It's freezing, you see a snow leapard climbing in the distance.");

    //Room 5
    (rooms+4)->setName("Beach");
    (rooms+4)->setIndexRoomToNorth(-99);
    (rooms+4)->setIndexRoomToSouth(0);
    (rooms+4)->setIndexRoomToEast(-99);
    (rooms+4)->setIndexRoomToWest(-99);
    (rooms+4)->setRoomDescription("The suns beaming, you see a family of crabs at your feet.");
}

//User Action
template<class T>
void promptUserAction(vector<T*> players, int playernumber, const Room rooms[], string &strCh, vector<BadGuy> badGuy1, int NumBadGuys)
{
    //Tells User what type they are
    if (players[playernumber]->getUserType() == 1){
        cout << "-----SUPERUSER-----" << endl;
    }
    else{
        cout << "-------NORMAL-------" << endl;
    }
    // tell user where they are and describes the room
    cout << (players)[playernumber] -> getUserName() << " you are currently in " << rooms[(players)[playernumber]->getIndexofCurrentRoom()]
         << endl;
    bool Check = false; // will check if User is in room with a bad guy
    cout << "The following badguys are in a room with you: " << endl;
    //prints names of badguys who are in the room.
    for (int i = 0; i < NumBadGuys; i++){
        if ((players)[playernumber]->getIndexofCurrentRoom()==badGuy1[i].getIndexCurrentRoom()){
            cout << badGuy1[i].getName() << endl;
            Check = true;
    }
    }
    if (Check == false){cout << "There are no Bad Guys in your room. Lucky You!";} //Tells user no bad guys are in the room with them
    //prompt user for choice
    cout << "What would you like to do?" << endl << "**********************" << endl;
    cin >> strCh;
}

//implement Users Action
template<class T>
void implementUserAction(vector<T*> *players, int playernumber, const Room rooms[], string &strCh, vector<BadGuy> &badGuy1, int NumBadGuys, SpecialList<User> *unlucky) {
    if (strCh == "O" || strCh == "o") {
        // user has selected to check if there are other users in the same room
        // checks if the room indexes of players are the same
        cout << "The following users are in the same room: " << endl;
        int countInRoom = 0;
        for (int i = 0; i < players->size(); i++) {
            if ((i!=User::IndNextUser)&&((*players)[i] == (*players)[playernumber])) {
                cout << (*players)[i] << endl;
                countInRoom++;
            }
            if (countInRoom == 0)
                cout << "No other users in this room." << endl;
        }
    } else if ((strCh == "N") || (strCh == "n")) {
//user has selected to move north

// is it possible to move north from the room the user
//is currently in

        int indxRoomNorth = rooms[(*players)[playernumber]->getIndexofCurrentRoom()].getIndexRoomToNorth();
        if (indxRoomNorth != -99) {
            (*players)[playernumber]->
                    setIndexofCurrentRoom(indxRoomNorth);
            cout << (*players)[playernumber] -> getUserName() << ", you are now in "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************" <<
                 endl;

        } else {
            cout << (*players)[playernumber] -> getUserName() << ", you can not move north from "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************"<<endl;
        }
    } else if ((strCh == "S") || (strCh == "s")) {
//user has selected to move south

// is it possible to move south from the room the user
//is currently in
        int indxRoomSouth = rooms[(*players)[playernumber]->getIndexofCurrentRoom()].getIndexRoomToSouth();
        if (indxRoomSouth != -99) {
            (*players)[playernumber]->
                    setIndexofCurrentRoom(indxRoomSouth);
            cout << (*players)[playernumber]-> getUserName() << ", you are now in "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************" <<endl;

        } else {

            cout << (*players)[playernumber]-> getUserName() << ", you can not move south from "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************"<<endl;
        }
    } else if ((strCh == "E") || (strCh == "e")) {
//user has selected to move east

// is it possible to move east from the room the user
//is currently in
        int indxRoomEast = rooms[(*players)[playernumber]->getIndexofCurrentRoom()].getIndexRoomToEast();
        if (indxRoomEast != -99) {
            (*players)[playernumber]->
                    setIndexofCurrentRoom(indxRoomEast);
            cout << (*players)[playernumber]-> getUserName() << ", you are now in "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************" <<endl;
        } else {
            cout << (*players)[playernumber]-> getUserName() << ", you can not move east from "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************"<<endl;
        }
    } else if ((strCh == "W") || (strCh == "w")) {
//user has selected to move west

// is it possible to move west from the room the user
//is currently in
        int indxRoomWest = rooms[(*players)[playernumber]->getIndexofCurrentRoom()].getIndexRoomToWest();
        if (indxRoomWest != -99) {
            (*players)[playernumber]->
                    setIndexofCurrentRoom(indxRoomWest);
            cout << (*players)[playernumber]-> getUserName() << ", you are now in "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]
                 << endl << "**********************" <<endl;

        } else {
            cout << (*players)[playernumber]-> getUserName() << ", you can not move west from "
                 << rooms[(*players)[playernumber]->getIndexofCurrentRoom()]<< endl << "**********************"
                 <<endl;
        }
    } else if ((strCh == "Q") || (strCh == "q")) {
//user has selected to quit
        cout << (*players)[playernumber] -> getUserName() << " Thank you for playing..." <<
             endl;
    } 
    else if((strCh == "Z")||(strCh == "z")){
        if (unlucky->checkList((*players)[playernumber]) == false){
            cout << "You are calm, hopefully it stays that way!" << endl << "**********************"<<endl;
        }
        else {
            cout << "You are paranoid, try to calm down!"<< endl << "**********************"<<endl;
        }
    }
    else if((strCh=="C")||(strCh=="c")){
        //player teleports
        (*players)[playernumber] -> teleport();
        //tells player new room
        cout << "You are now in " << rooms[(*players)[playernumber]->getIndexofCurrentRoom()] << endl << "**********************"
        <<endl;
    }
    else if((strCh == "A") || (strCh == "a")){
        bool Check = false; // will check if User is in room with a bad guy
        for (int i = 0; i < NumBadGuys; i++){
            if ((*players)[playernumber]->getIndexofCurrentRoom()==badGuy1[i].getIndexCurrentRoom()){
                Check = true;
            }
        }
        if (Check == true)
            {
                //get damage that is being done 1-20
                int attack;
                attack = rand()%21;
                //Allow user to pick which Badguy to attack
                cout << "You can attack the following Bad Guys: " << endl;
                for (int i = 0; i < NumBadGuys; i++){
                    if ((*players)[playernumber]->getIndexofCurrentRoom()==badGuy1[i].getIndexCurrentRoom()){
                        cout << badGuy1[i].getName() << "(" << badGuy1[i].getBadGuyHealth() << "/100)[" << i << "]" <<endl;
                    }
                }
                int BadGuyChoice; //Selction of who the User wants to attack
                do{
                    cout << "What Bad Guy would you like to attack?" << endl;
                    cin >> BadGuyChoice;
                } while ((*players)[playernumber]->getIndexofCurrentRoom()!=badGuy1[BadGuyChoice].getIndexCurrentRoom());
                //sets new health
                badGuy1[BadGuyChoice].setBadGuyHealth(badGuy1[BadGuyChoice].getBadGuyHealth()-attack);
                //Tells player how much damage they've done
                cout << "You hit " << badGuy1[BadGuyChoice].getName() << " right in the kisser!" << endl << "They took " << attack << " damage." << endl << "They have " << badGuy1[BadGuyChoice].getBadGuyHealth() << "/100 health remaining." << endl << "**********************" << endl;
            }
        else {cout << "There is nobody to attack." << endl << "**********************" << endl;} //If badguy isn't in room tells user he isn't
    }
    else if((strCh == "X") || (strCh == "x")){
        if ((*players)[playernumber] -> getUserType() == 1){
            bool Check = false; // will check if User is in room with a bad guy
            for (int i = 0; i < NumBadGuys; i++){
                if ((*players)[playernumber]->getIndexofCurrentRoom()==badGuy1[i].getIndexCurrentRoom()){
                    Check = true;
                }
            }
            if (Check == true)
            {
                cout << "You at remaining." << endl << "**********************" << endl;        cout << "You ate some Spinach and your muscles grew!" << endl;
            //get damage that is being done 1-20
            int attack;
            attack = rand()%21;
            //double attack
            attack = attack*2;
            //Allow user to pick which Badguy to attack
            cout << "You can attack the following Bad Guys: " << endl;
            for (int i = 0; i < NumBadGuys; i++){
                if ((*players)[playernumber]->getIndexofCurrentRoom()==badGuy1[i].getIndexCurrentRoom()){
                    cout << badGuy1[i].getName() << "(" << badGuy1[i].getBadGuyHealth() << "/100)[" << i << "]" <<endl;
                }
            }
            int BadGuyChoice; //Selction of who the User wants to attack
            do{
                cout << "What Bad Guy would you like to attack?" << endl;
                cin >> BadGuyChoice;
            } while ((*players)[playernumber]->getIndexofCurrentRoom()!=badGuy1[BadGuyChoice].getIndexCurrentRoom());
            //sets new health
            badGuy1[BadGuyChoice].setBadGuyHealth(badGuy1[BadGuyChoice].getBadGuyHealth()-attack);
            //Tells player how much damage they've done
            cout << "You hit " << badGuy1[BadGuyChoice].getName() << " right in the nose!" << endl << "They took " << attack << " damage." << endl << "They have " << badGuy1[BadGuyChoice].getBadGuyHealth() << "/100 health remaining." << endl << "**********************" << endl;
            } else {cout << "There is nobody to attack." << endl << "**********************" << endl;}
    }else {cout << "You aren't a Super User!"<< endl << "**********************" << endl;}
    }
    else {
//user has selected an invalid option
        cout << strCh << " is not a valid option." << endl << "**********************" <<
             endl;
    }
}

void savePlayerData(User u) {
    ofstream outputFile;
    outputFile.open("PlayerData.txt", ios::app);
    if (outputFile.fail())
    {
        cout << "Error: could not open PlayerData.txt" << endl;
        exit(1);
    }

    outputFile << u.getUserName() <<endl<< u.getIndexofCurrentRoom() << endl;

    outputFile.close();
}
template<class T>
void loadPlayerData(vector<T*> *allUsers) {
    ifstream inputFile;
    inputFile.open("PlayerData.txt");
    if (inputFile.fail())
    {
        cout << "Error: could not open PlayerData.txt" << endl;
        exit(1);
    }
    int i = 0;
    string strName;
    int roomNum;
    while (inputFile >> strName >> roomNum)
    {
        (allUsers->at(i))->setUserName(strName);
        (allUsers->at(i))->setIndexofCurrentRoom(roomNum);
        i++;
    }

    inputFile.close();
}

//clears the player data text file that holds the saved game data
void ClearFile() {
    ifstream Fileempty;
    string filepath = "PlayerData.txt";

    Fileempty.open(filepath.c_str(), ifstream::out | ifstream::trunc);
    if (!Fileempty.is_open() || Fileempty.fail())
    {
        Fileempty.close();
        cout << "Error: failed to clear last saved game" << endl;
    }
    Fileempty.close();
}

template <class T>
void moveBadGuy(vector<BadGuy> &badGuy1, const Room rooms[], int NumBadGuys, vector<T*> players)
{
    vector<int>playerIndex;
    bool Check = false; // will check if BadGuy is in room with a User
    for (int x = 0; x < NumBadGuys; x++){
        for (int i = 0; i < players.size(); i++){
            playerIndex.clear();
            Check = false;
            if ((players)[i]->getIndexofCurrentRoom()==badGuy1[x].getIndexCurrentRoom()){
                playerIndex.push_back(i);
                Check = true;
            }
         }
        if (Check == false){
            int indx = rand()%5;
            badGuy1[x].setIndexCurrentRoom(indx);
            cout<<badGuy1[x].getName()<<" is now in "<< rooms[indx].getName() << endl << "**********************" <<endl;

        }
        else {
            int attack;
            attack = rand()%21;

            int playerToAttack = rand()%playerIndex.size();
            (players)[playerToAttack]->setHealth(attack);
            
            cout << badGuy1[x].getName() << " attacked " << players[playerToAttack] -> getUserName() << " for " << attack << ". They now have " << players[playerToAttack] -> getHealth() << "/100 health!." << endl << "**********************" <<endl;
            
        }
     }
}

//
template <class T>
void addPlayers(vector<T*> players, const Room rooms[], vector<BadGuy> badguy1, SpecialList<User> *unlucky, int NumBadGuys){
    
    for (int x = 0; x < players.size(); x++){
        int BadGuysInRoom = 0;
        for (int i = 0; i < NumBadGuys; i++){
            //Gets number of enemies in room
            if ((players)[x]->getIndexofCurrentRoom()==badguy1[i].getIndexCurrentRoom()){
                BadGuysInRoom ++;
            }
        }
        //Checks if players have more than one enemy with them
        if (BadGuysInRoom > 1){
            unlucky->addToList((players)[x]);// Adds players to Special players to Special List
        }

    }
}