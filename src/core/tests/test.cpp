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
#include <stdlib.h>

using namespace lolilang;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] ){
    auto tmp = initGlobalTypes();
    std::cout<<global_type_env.size()<<std::endl;
    for(ulong i = 0; i < global_type_env.size(); i++){
        std::cout<<i<<"\t"<<global_type_env[i]->to_string()<<std::endl;
    }
    compoundType* testCT = new compoundType(t_obj);
    testCT->set_next(new compoundType(t_int, t_sym));
    std::cout<<testCT->to_string()<<std::endl;
    return 0;
}
