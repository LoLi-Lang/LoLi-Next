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

#include "gc.h"
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

namespace lolilang{

//    typeId:
//        OBJ,
//        NUM,
//        INT,
//        FLT,
//        RAT,
//        SYM,
//        KEY,
//        BOOL,
//        FN,
//        LAMBDA,
//        PROC,
//        CONS,
//        CHAR,
//        STR

    class typeClass{
        public:
        string id;  
        typeClass* parent = NULL;
        vector<typeClass*> children;
        vector<typeClass*>::iterator iteratorOfChildren;

        typeClass* newChildType(string name);
        
        typeClass();

        typeClass(string name);

        ~typeClass();
    };
    
    static vector<typeClass*> global_types;
    static vector<typeClass*>::iterator global_types_iterator;
    
    static void initGlobalTypes();
}

#endif
