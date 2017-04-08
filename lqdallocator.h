/*
 * lqdallocator.h
 *
 *  Created on: Apr 7, 2017
 *      Author: c
 */

#ifndef LQDALLOCATOR_H_
#define LQDALLOCATOR_H_
#include"tools.h"
#include<stdlib.h>
struct addrnode {

};
template<class T1, class T2>
void lqdconstruct(T1* ptr, const T2& t) {
	new (ptr) T2(t);
}
class lqdallocator {
public:
	//directly get space
	static void allocate(int size, void** ptr) {
		*ptr = malloc(size);
		//		if (!ptr)
	}
	static void deallocate(void* ptr) {
		free(ptr);
	}
private:

};
#endif /* LQDALLOCATOR_H_ */
