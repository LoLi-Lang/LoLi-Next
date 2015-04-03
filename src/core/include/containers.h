/*
 * =====================================================================================
 *
 *       Filename:  containers.h
 *
 *    Description:  Containers of LoLi
 *
 *        Version:  1.0
 *        Created:  04/02/2015 05:17:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Z.Shang (), shangzhanlin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __CONTAINERS_H__
#define __CONTAINERS_H__

#include <iostream>
#include <string>

namespace lolilang{
    template <typename T> class loliList{
        private:
            T obj;
            loliList<T> nextObj;

        public:
            static loliList<T> __END = new loliList<T>(NULL);

            loliList<T>(){
                obj = NULL;
                nextObj = __END;
            };

            loliList<T>(T initObj){
                obj = initObj;
                nextObj = __END;
            };

            bool has_next(){
                return nextObj != __END;
            }
            
            T next(){
                if(this->has_next()){
                    return this->nextObj;
                }else{
                    throw "List underflow";
                }
            }

            void push_back(T obj){
                if(this->has_next()){
                    this->next()->push_back(obj);
                }else{
                    this->nextObj = obj;
                }
            }

            ~loliList<T>(){
                if(this->has_next()){
                    delete this->next();
                }else{
                    delete this;
                }
            }
    };
}

#endif
