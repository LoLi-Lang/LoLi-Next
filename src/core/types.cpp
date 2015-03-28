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
        compund = false;
    }

    typeClass::typeClass(string name){
        compund = false;
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
            return current->to_string() + " -> "+ ((compoundType*)next)->to_string();
        }else{
            return current->to_string() + " -> " + next->to_string();
        }
    }

    static void initGlobalTypes(){
        typeClass* t_obj = new typeClass("LoLi Object");
        typeClass* t_num = t_obj->newChildType("Number");
        typeClass* t_int = t_num->newChildType("Integer");
        typeClass* t_flt = t_num->newChildType("Float");
        typeClass* t_rat = t_num->newChildType("Ratio");
        typeClass* t_sym = t_obj->newChildType("Symbol");
        typeClass* t_key = t_obj->newChildType("Keyword");
        typeClass* t_bool = t_key->newChildType("Boolean");
        typeClass* t_fn = t_obj->newChildType("Function");
        typeClass* t_prim = t_fn->newChildType("Primitive Funtion");
        typeClass* t_lambda = t_fn->newChildType("Lambda Expression");
        typeClass* t_pair = t_obj->newChildType("Pair");
        typeClass* t_char = t_obj->newChildType("Character");
        typeClass* t_str = t_char->newListedType("String");
        
        global_types_iterator = global_types.begin();
    }
}
