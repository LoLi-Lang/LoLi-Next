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
        global_type_env.push_back(this);
    }

    typeClass::typeClass(string name){
        compund = false;
        id = name;
        std::cout<<"Creating "<<name<<std::endl;
        global_type_env.push_back(this);
    }

    typeClass::~typeClass(){
        for(ulong i = 0; i < children.size(); i++){
            delete children[i];
        }
        delete this;
    }

    string typeClass::to_string(){
        std::cout<<"TC tostring\t"<<std::endl;
        return this->id;
    }

    compoundType::compoundType(){
        //Empty Constructor
        compund = true;
        global_type_env.push_back(this);
    }

    compoundType::compoundType(typeClass* tc){
        compund = true;
        current = tc;
        global_type_env.push_back(this);
    }

    compoundType::compoundType(typeClass* tc, typeClass* n){
        compund = true;
        current = tc;
        next = n;
        global_type_env.push_back(this);
    }

    void compoundType::set_next(typeClass* n){
        this->next = n;
    }

    compoundType::~compoundType(){

    }

    string compoundType::to_string(){
        std::cout<<"CT tostring\t"<<std::endl;
        if(next->compund){
            return current->to_string() + " -> "+ next->to_string();
        }else{
            return current->to_string() + " -> " + next->to_string() + " ]";
        }
    }

    vector<typeClass*> initGlobalTypes(){
        typeClass* t_obj = new typeClass("Object");
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

        std::cout<<"Global Type Enviroment Size: "<<global_type_env.size()<<std::endl;
        return global_type_env;
    }
}
