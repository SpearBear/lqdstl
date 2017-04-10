/*
 * main.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */
#include"lqdstl.h"
#include<vector>
int main() {
	//	testallocator();
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	locker l(lock);
}
