/*
 * lqdstl.h
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */

#ifndef LQDSTL_H_
#define LQDSTL_H_
#include"tools.h"
#include"lqdallocator.h"
#include"lqdvector.h"
void testallcator() {
}
void testconstruct() {
	lqdvector<int>* ptr = NULL, v(3);
	lqdallocator::allocate(100, (void**) &ptr);
	cout << ptr << endl;
	lqdconstruct(ptr, lqdvector<int> (3));
}
#endif /* LQDSTL_H_ */
