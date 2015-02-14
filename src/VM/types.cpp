/*
 * =====================================================================================
 *
 *       Filename:  types.cpp
 *
 *    Description:  Type Class
 *
 *        Version:  1.0
 *        Created:  02/13/2015 11:48:58 PM
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

    typeClass::typeClass(){
        //Empty Constructor
    }

    typeClass::typeClass(string name){
        id = name;
    }

    typeClass::~typeClass(){
        for(iteratorOfChildren = children.begin();
                iteratorOfChildren != children.end();
                iteratorOfChildren ++){
            delete *iteratorOfChildren;
        }
    }
    

}

