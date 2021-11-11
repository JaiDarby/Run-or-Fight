//
// Created by Jai'Mir Darby on 10/24/21.
//
#include <vector>

#ifndef TEXTBASEDGAMEPART8_SPECIALLIST_H
#define TEXTBASEDGAMEPART8_SPECIALLIST_H

using namespace std;

template <class T> 
class SpecialList {
private:
    vector <T*> list;
public:
    SpecialList();
    void addToList (T* person); //adds person to vector
    bool checkList (T* person); //Displays list


};


#endif //TEXTBASEDGAMEPART7_SPECIALLIST_H
