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
#include<pthread.h>
#include"locker.h"
union addrnode {
	//????
	addrnode* next;
	char data[1];
};
template<class T1, class T2>
void lqdconstruct(T1* ptr, const T2& t) {
	new (ptr) T1(t);
}
template<class T>
void lqddestroy(T* p) {
	p->~T();
}
//template<bool thread = false>
class lqdallocator {
public:
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	//get space with pool
	static void* allocate(size_t n) {
		{
			//			locker(lock);
			if (n > MAXSIZE)
				return allocate(n);
			addrnode** addr = nodeaddr(n);
			addrnode* result = *addr;
			if (*addr == 0) {
				//			not enough space
				void* r = refill(round_up(n));
				return r;
			}
			*addr = (*addr)->next;
			return result;
		}
	}
	static char* chunkaddr(size_t n, int& nodes) {
		char* result;
		size_t total = n * nodes;
		size_t left = end - start;
		addrnode** addr;
		if (left >= total) {
			result = start;
			start = start + total;
			return result;
		} else if (left >= n) {
			nodes = left / n;
			total = nodes * n;
			result = start;
			start = start + total;
			return result;
		} else {
			size_t needy = 2 * total + (cap >> 4);
			if (left > 0) {
				addr = nodeaddr(left);
				((addrnode*) start)->next = *addr;
				*addr = (addrnode*) start;
			}
			start = (char*) malloc(needy);
			end = start + needy;
			cap += needy;
			result = start;
			start = start + total;
			return result;
		}
	}
	static void* refill(size_t n) {
		int nodes = 20;
		char* chunk = chunkaddr(n, nodes), *tchunk;
		addrnode **addr, *result, *cur, *next;
		if (nodes == 1)
			return chunk;
		addr = nodeaddr(n);
		result = (addrnode*) chunk;
		tchunk = chunk + n;
		*addr = next = (addrnode*) tchunk;
		for (int i = 1;; i++) {
			cur = next;
			next = (addrnode*) ((char*) next + n);
			if (i == nodes - 1) {
				cur->next = 0;
				break;
			} else {
				cur->next = next;
			}
		}
		return result;
	}
	//directly get space
	static void* _allocate(size_t n) {
		void* ptr = malloc(n);
		//if
		return ptr;
	}
	static void deallocate(void* ptr) {
		free(ptr);
	}
	static void* reallocate(void* p, size_t size) {
		void* result = realloc(p, size);
		return result;
	}
	static size_t round_up(size_t size) {
		return size % ALIGN == 0 ? size : (size / ALIGN + 1) * ALIGN;
	}
	static addrnode** nodeaddr(size_t n) {
		return list + n / 8;
	}
	static void showpoolinfo() {
		cout << "start: " << (unsigned long) start << endl;
		cout << "end: " << (unsigned long) end << endl;
		cout << "left " << (unsigned long) (end - start) << endl;
	}
	static void showpoolinfo(int index) {
		showpoolinfo();
		cout << "index " << round_up(index) << " starts from: "
				<< (unsigned long) (char*) *nodeaddr(index) << endl;
	}
private:
	enum {
		ALIGN = 8
	};
	enum {
		MAXSIZE = 128
	};
	enum {
		NFREELISTS = MAXSIZE / ALIGN
	};
	static char* start;
	static char* end;
	static size_t cap;
	static addrnode* list[NFREELISTS];
};
char* lqdallocator::start = 0;
char* lqdallocator::end = 0;
size_t lqdallocator::cap = 0;
addrnode* lqdallocator::list[NFREELISTS] = { 0 };
#endif /* LQDALLOCATOR_H_ */
