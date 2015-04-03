/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  Test Set of LoLi.core
 *
 *        Version:  1.0
 *        Created:  03/28/2015 02:06:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/types.h"

#include <iostream>

#include	<stdlib.h>

using namespace lolilang;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] ){
    initGlobalTypes();
    for(vector<typeClass*>::iterator i = global_types->begin(); i != global_types->end(); i++){
        std::cout<<*i<<std::endl;
    }
    return 0;
}
