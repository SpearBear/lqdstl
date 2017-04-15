/*
 * locker.h
 *
 *  Created on: Apr 10, 2017
 *      Author: c
 */

#ifndef LOCKER_H_
#define LOCKER_H_
#include<pthread.h>
class locker {
public:
	locker(pthread_mutex_t& l) :
		lock(l) {
		pthread_mutex_lock(&lock);
	}
	~locker() {
		pthread_mutex_unlock(&lock);
	}
private:
	pthread_mutex_t& lock;
};
class wrlocker {
public:
	wrlocker(pthread_rwlock_t& l) :
		lock(l) {
		pthread_rwlock_wrlock(&lock);
	}
	~wrlocker() {
		pthread_rwlock_unlock(&lock);
	}
private:
	pthread_rwlock_t& lock;
};
class rdlocker {
public:
	rdlocker(pthread_rwlock_t& l) :
		lock(l) {
		pthread_rwlock_rdlock(&lock);
	}
	~rdlocker() {
		pthread_rwlock_unlock(&lock);
	}
private:
	pthread_rwlock_t& lock;
};
#endif /* LOCKER_H_ */
