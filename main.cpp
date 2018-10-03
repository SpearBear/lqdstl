/*
 * main.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */
#include"lqdstl.h"
#include<vector>
#include<list>
#include<string.h>
template<class T>
class mdata {
public:
	mdata(const T& t, const pthread_rwlock_t& l) :
		data(t), lock(l) {
	}
	T operator=(const T& t) {
		data = t;
		return data;
	}
private:
	T data;
	pthread_rwlock_t& l;
};
template<class U>
class test {
public:
	typedef mdata<U> T;
	test(T t) {

	}
};
int main() {
	mdata<int> m(3);
	m = 4;
	//	cout << m;
}
