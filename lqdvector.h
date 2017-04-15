/*
 * lqdvector.h
 *
 *  Created on: Apr 8, 2017
 *      Author: c
 */

#ifndef LQDVECTOR_H_
#define LQDVECTOR_H_
#include"lqdstl.h"
template<class T>
//class mdata {
//public:
//	mdata(const T& t, const pthread_rwlock_t& l) :
//		data(t), lock(l) {
//	}
//	T operator=(const T& t) {
//		data = t;
//		return data;
//	}
//private:
//	T data;
//	pthread_rwlock_t& l;
//};
template<class T, class alloc = lqdallocator>
class lqdvector {
public:
	typedef T value_type;
	typedef T* ptr;
	typedef T* iterator;
	typedef T& ref;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	lqdvector() :
		start(0), finish(0), end_of_storage(0) {
	}
	lqdvector(size_type n, const T& value) {
		fill_initialize(n, value);
	}
	lqdvector(long n, const T& value) {
		fill_initialize(n, value);
	}
	lqdvector(int n, const T& value) {
		fill_initialize(n, value);
	}
	~lqdvector() {
		lqddestroy(start, finish);
		deallocate();
	}
	iterator begin() {
		return start;
	}
	iterator end() {
		return finish;
	}
	size_type size() {
		return finish - start;
	}
	void push_back(const T& value) {
		if (finish != end_of_storage) {
			lqdconstruct(finish, value);
			++finish;
		} else
			insert_aux(end(), value);
	}
	void insert(iterator position, size_type n, const T& value) {
		if (size_type(end_of_storage - finish) >= n) {
			lqduninitialized_copy(finish - n, finish, finish);
			lqdcopy_backward(position, finish - n, finish);
			lqdfill_n(position, n, value);
			finish += n;
		} else {
			const size_type oldsize = size();
			const size_type newsize = oldsize + n > oldsize ? n : oldsize;
			iterator new_start = allocator::allocate(newsize);
			iterator new_finish = new_start;
			new_finish = lqduninitialized_copy(start, position, new_start);
			new_finish = lqduninitialized_fill_n(new_finish, n, value);
			new_finish = lqduninitialized_copy(position, finish, new_finish);
			lqddestroy(start, finish);
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + newsize;
		}
	}
	void insert_aux(iterator position, const T& value) {
		if (finish != end_of_storage) {
			++finish;
			lqdconstruct(finish - 1, *(finish - 2));
			lqdcopy_backward(position, finish - 2, finish - 1);
			*position = value;
		} else {
			const size_type oldsize = size();
			const size_type newsize = oldsize == 0 ? 1 : oldsize * 2;
			iterator new_start = allocator::allocate(newsize);
			iterator new_finish = new_start;
			new_finish = lqduninitialized_copy(start, position, new_start);
			lqdconstruct(new_finish, value);
			++new_finish;
			new_finish = lqduninitialized_copy(position, finish, new_finish);
			lqddestroy(start, finish);
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = start + newsize;
		}
	}
	ref operator[](size_type n) {
		return *(begin() + n);
	}
protected:
	void deallocate() {
		if (start)
			allocator::deallocate(start, end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value) {
		start = allocate_and_fill(n, value);
		end_of_storage = start + n;
		finish = end_of_storage;
	}
	iterator allocate_and_fill(size_type n, const T& value) {
		iterator result = allocator::allocate(n);
		lqduninitialized_fill_n(result, n, value);
		return result;
	}
	typedef lqdsimple_alloc<T, lqdallocator> allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
};

#endif /* LQDVECTOR_H_ */
