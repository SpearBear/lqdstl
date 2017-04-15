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
#include"lqdalgorithm.h"
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
template<class container>
void printer(container c) {
	typename container::iterator i = c.begin();
	for (; i != c.end(); ++i)
		cout << *i;
	cout << endl;
}
void testiterator() {
}
void testvector() {
	lqdvector<int> v(1, 0);
	lqdallocator::showpoolinfo(40);
	v.insert(v.begin(), 1, 1);
	v.insert(v.begin(), 1, 2);
	printer(v);
	//	cout << v[2] << endl;
	cout << v.size() << endl;
	lqdallocator::showpoolinfo();
}
void testlqdun_copy() {
	int* p = new int[10];
	for (int i = 0; i < 5; i++)
		p[i] = i + 1;
	lqduninitialized_copy(p, p + 5, p + 5);
	for (int i = 0; i < 10; i++)
		cout << p[i];
}
void testcopy_backward() {
	int* p = new int[10];
	for (int i = 0; i < 9; i++)
		p[i] = 0;
	int* t = lqdcopy_backward(p, p + 8, p + 9);
	*t = 2;
	for (int i = 0; i < 10; i++)
		cout << p[i];
}
void testdestroy() {
	int *p1, *p2;
	p1 = p2 = 0;
	lqddestroy(p1, p2);
	//	cout << value_type(p1);
}
void testdealloc() {
	int n = 5;
	tnode* p = (tnode*) lqdallocator::allocate(n);
	lqdallocator::showpoolinfo(n);
	lqdallocator::deallocate(n, p);
	lqdallocator::showpoolinfo(n);
}
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
void testconstruct() {
	tnode* p = NULL;
	p = (tnode*) lqdallocator::_allocate(130);
	lqdconstruct(p, 3);
	cout << p->i << " " << p->c;
	lqddestroy(p);
}
#endif /* LQDSTL_H_ */
