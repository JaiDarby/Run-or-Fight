//
// Created by Jai'Mir Darby on 10/24/21.
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "SpecialList.h"

using namespace std;

// Constructor
template<class T>
SpecialList<T>::SpecialList() {} 

//Mutator
template<class T>
void SpecialList<T>::addToList(T* person) {
    //Only will add if user is not already in list
    if(find(list.begin(),list.end(),person)==list.end()){
        list.push_back(person);
    }
}

template<class T>
bool SpecialList<T>::checkList(T *person){
    //checks if user is in list
    if(find(list.begin(),list.end(),person)==list.end()){return false;} // If they aren't returns false
    else{return true;} // If they are returns true
}