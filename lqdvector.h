/*
 * lqdvector.h
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */

#ifndef LQDVECTOR_H_
#define LQDVECTOR_H_
#include"lqdstl.h"
template<class T, class alloc = lqdallocator>
class lqdvector {
public:
	lqdvector(int n) {
		//		T* ptr = NULL;
		//		alloc::allocate(sizeof(T), (void**) &ptr);
		//		*ptr = n;
		//		cout << *ptr;
		//		alloc::deallocate(ptr);
		cout << "in vec " << this << endl;
	}
	~lqdvector() {

	}
};

#endif /* LQDVECTOR_H_ */
