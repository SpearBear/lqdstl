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
#include"traits.h"
#include"locker.h"
#include"lqdalgorithm.h"
union addrnode {
	//????
	addrnode* next;
	char data[1];
};
template<class iterator, class size_type, class T>
iterator _lqduninitialized_fill_n_aux(iterator start, size_type n,
		const T& value, true_type) {
	return lqdfill_n(start, n, value);
}
template<class iterator, class size_type, class T>
iterator _lqduninitialized_fill_n_aux(iterator start, size_type n,
		const T& value, false_type) {
	iterator i = start;
	for (; n > 0; --n, ++i)
		lqdconstruct(i, value);
	return i;
}
template<class iterator, class size_type, class T, class T1>
iterator _lqduninitialized_fill_n(iterator start, size_type n, const T& value,
		T1) {
	typedef typename lqdtype_traits<T1*>::is_POD_type pod;
	return _lqduninitialized_fill_n_aux(start, n, value, pod());
}
template<class iterator, class size_type, class T>
iterator lqduninitialized_fill_n(iterator start, size_type n, const T& value) {
	return _lqduninitialized_fill_n(start, n, value, value_type(start));
}

template<class T1, class T2>
void lqdconstruct(T1* ptr, const T2& t) {
	new (ptr) T1(t);
}

template<class T>
void lqddestroy(T* p) {
	p->~T();
}
template<class iterator, class T>
void _lqddestroy(iterator first, iterator last, T) {
	typedef typename lqdtype_traits<T*>::has_trivial_destructor destructor;
	_lqddestroy_aux(first, last, destructor());
}
template<class iterator>
void _lqddestroy_aux(iterator first, iterator last, true_type) {
}
template<class iterator>
void _lqddestroy_aux(iterator first, iterator last, false_type) {
	while (first != last) {
		first->~iterator();
		++first;
	}
}
template<class iterator>
void lqddestroy(iterator first, iterator last) {
	_lqddestroy(first, last, value_type(first));
}

template<class T, class alloc>
class lqdsimple_alloc {
public:
	static T* allocate(size_t n) {
		//		cout << "n: " << n << " " << n * sizeof(T) << endl;
		return 0 == n ? 0 : (T*) alloc::allocate(n * sizeof(T));
	}
	static T* allocate(void) {
		return (T*) alloc::allocate(sizeof(T));
	}
	static void deallocate(T* p, size_t n) {
		//if	(0 != n)
		//			alloc::deallocate::(p, n * sizeof(T));
	}
	static void deallocate(T* p) {
		alloc::deallocate(p, sizeof(T));
	}
};
//template<bool thread = false>
class lqdallocator {
public:
	//get space with pool
	static void deallocate(size_t n, void* p) {
		if (n > 128)
			deallocate(p);
		locker l(lock);
		addrnode** addr = nodeaddr(round_up(n));
		((addrnode*) p)->next = *addr;
		*addr = (addrnode*) p;
	}
	static void* allocate(size_t n) {
		if (n > MAXSIZE)
			return _allocate(n);
		locker l(lock);
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
		return list + n / 8 - 1;
	}
	static void showpoolinfo() {
		cout << "start: " << (unsigned long) start << endl;
		cout << "end: " << (unsigned long) end << endl;
		cout << "left " << (unsigned long) (end - start) << endl;
	}
	static void showpoolinfo(size_t n) {
		showpoolinfo();
		cout << "index " << round_up(n) / 8 << " starts from: "
				<< (unsigned long) (char*) *nodeaddr(round_up(n)) << endl;
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
	static pthread_mutex_t lock;
};
char* lqdallocator::start = 0;
char* lqdallocator::end = 0;
size_t lqdallocator::cap = 0;
addrnode* lqdallocator::list[NFREELISTS] = { 0 };
pthread_mutex_t lqdallocator::lock = PTHREAD_MUTEX_INITIALIZER;
#endif /* LQDALLOCATOR_H_ */
