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
#include <iostream>

namespace lolilang{

    typeClass* typeClass::newChildType(string name){
        typeClass* tmp = new typeClass(name);
        tmp->parent = this;
        return tmp;
    }

    typeClass* typeClass::newListedType(string name){
        typeClass* tmp = new typeClass(name);
        tmp->parent = this;
        tmp->listOf = true;
        return tmp;
    }

    typeClass::typeClass(){
        //Empty Constructor
        compund = false;
    }

    typeClass::typeClass(string name){
        compund = false;
        id = name;
        std::cout<<"Creating "<<name<<std::endl;
    }

    typeClass::~typeClass(){
        for(iteratorOfChildren = children.begin();
                iteratorOfChildren != children.end();
                iteratorOfChildren ++){
            delete *iteratorOfChildren;
        }
    }

    string typeClass::to_string(){
        return this->id;
    }

    compoundType::compoundType(){
        //Empty Constructor
        compund = true;
    }

    compoundType::compoundType(typeClass* tc){
        compund = true;
        current = tc;
    }

    compoundType::compoundType(typeClass* tc, typeClass* n){
        compund = true;
        current = tc;
        next = n;
    }

    compoundType::~compoundType(){

    }

    string compoundType::to_string(){
        if(next->compund){
            return current->to_string() + " -> "+ ((compoundType*)next)->to_string(true);
        }else{
            return current->to_string() + " -> " + next->to_string() + " ]";
        }
    }

    string compoundType::to_string(bool inside){
        if(inside){
            return this->to_string();
        }else{
            return "[ " + this->to_string();
        }
    }

    void initGlobalTypes(){
        t_obj = new typeClass("Object");
        t_num = t_obj->newChildType("Number");
        t_int = t_num->newChildType("Integer");
        t_flt = t_num->newChildType("Float");
        t_rat = t_num->newChildType("Ratio");
        t_sym = t_obj->newChildType("Symbol");
        t_key = t_obj->newChildType("Keyword");
        t_bool = t_key->newChildType("Boolean");
        t_fn = t_obj->newChildType("Function");
        t_prim = t_fn->newChildType("Primitive Funtion");
        t_lambda = t_fn->newChildType("Lambda Expression");
        t_pair = t_obj->newChildType("Pair");
        t_char = t_obj->newChildType("Character");
        t_str = t_char->newListedType("String");
        
    }
}
