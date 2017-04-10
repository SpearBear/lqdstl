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
struct tnode {
	char c;
	int i;
	tnode(int j = 0, char x = 95) :
		c(x), i(j) {
	}
	~tnode() {
		lqdallocator::deallocate(this);
	}
};
void testallocator() {
	tnode* p = NULL;
	for (int i = 0; i < 45; i++) {
		p = (tnode*) lqdallocator::allocate(sizeof(tnode));
		lqdconstruct(p, i);
		//		cout << p->i << " " << p->c << endl;
	}
	lqdallocator::showpoolinfo(sizeof(tnode));
}
void testalloc() {
	lqdallocator::showpoolinfo();
	for (int i = 0; i < 5; i++) {
		void* addr = lqdallocator::allocate(sizeof(tnode));
		lqdallocator::showpoolinfo(sizeof(tnode));
		cout << "get: " << (unsigned long) addr << endl;
	}
}
void testrefill() {
	lqdallocator::showpoolinfo();
	void* addr = lqdallocator::refill(sizeof(tnode));
	lqdallocator::showpoolinfo(sizeof(tnode));
	cout << "get: " << (unsigned long) addr;
}
void testchunk() {
	int nodes = 10;
	lqdallocator::chunkaddr(8, nodes);
	lqdallocator::showpoolinfo();
}
void testallcator() {
}
void testconstruct() {
	tnode* p = NULL;
	p = (tnode*) lqdallocator::_allocate(130);
	lqdconstruct(p, 3);
	cout << p->i << " " << p->c;
	lqddestroy(p);
}
#endif /* LQDSTL_H_ */
