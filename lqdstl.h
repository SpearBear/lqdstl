/*
 * lqdstl.h
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */

#ifndef LQDSTL_H_
#define LQDSTL_H_
#include<iostream>
#include"lqdallocator.h"
using namespace std;
void testallcator() {
	lqdallocator la;
	int* ptr = NULL;
	la.allcat(sizeof(int), (void**) &ptr);
	cout << ptr;
}
#endif /* LQDSTL_H_ */
