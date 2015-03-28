/*
 * =====================================================================================
 *
 *       Filename:  types.cpp
 *
 *    Description:  Type Class Of LoLi
 *
 *        Version:  1.0
 *        Created:  03/28/2015 02:47:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "include/types.h"

namespace lolilang{

    typeClass* typeClass::newChildType(string name){
        typeClass* tmp = new typeClass(name);
        tmp->parent = this;
        children.push_back(tmp);
        return tmp;
    }

    typeClass* typeClass::newListedType(string name){
        typeClass* tmp = new typeClass(name);
        tmp->parent = this;
        tmp->listOf = true;
        children.push_back(tmp);
        return tmp;
    }

    typeClass::typeClass(){
        //Empty Constructor
    }

    typeClass::typeClass(string name){
        id = name;
        global_types.push_back(this);
    }

    typeClass::~typeClass(){
        for(iteratorOfChildren = children.begin();
                iteratorOfChildren != children.end();
                iteratorOfChildren ++){
            delete *iteratorOfChildren;
        }
    }

    static void initGlobalTypes(){

    }
}
