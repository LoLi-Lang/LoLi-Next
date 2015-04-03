/*
 * =====================================================================================
 *
 *       Filename:  types.h
 *
 *    Description:  Typeclass of LoLi
 *
 *        Version:  1.0
 *        Created:  02/13/2015 07:51:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>
#include <string>

using namespace std;

namespace lolilang{

    class typeClass{
        public:
            string id;  
            typeClass* parent;
            typeClass** children;
            bool listOf;
            bool compund;

            typeClass* newChildType(string name);

            typeClass* newListedType(string name);

            typeClass();

            typeClass(string name);

            ~typeClass();

            string to_string();
    };

    class compoundType : public typeClass{
        public:
            typeClass* current;
            typeClass* next;

            compoundType();

            compoundType(typeClass* tc);

            compoundType(typeClass* tc, typeClass* n);

            ~compoundType();

            string to_string();
            string to_string(bool inside);

    };

    static typeClass* t_obj;
    static typeClass* t_num;
    static typeClass* t_int;
    static typeClass* t_flt;
    static typeClass* t_rat;
    static typeClass* t_sym;
    static typeClass* t_key;
    static typeClass* t_bool;
    static typeClass* t_fn;
    static typeClass* t_prim;
    static typeClass* t_lambda;
    static typeClass* t_pair;
    static typeClass* t_char;
    static typeClass* t_str;

    void initGlobalTypes();
}

#endif
