/*
 * lqdalgorithm.h
 *
 *  Created on: Apr 13, 2017
 *      Author: c
 */

#ifndef LQDALGORITHM_H_
#define LQDALGORITHM_H_
#include"tools.h"
#include<string.h>
template<class iterator, class size_type, class T>
iterator lqdfill_n(iterator first, size_type n, const T& value) {
	for (; n > 0; ++first, --n)
		*first = value;
	return first;
}
template<class iterator>
iterator lqdcopy_backward(iterator first, iterator last, iterator result) {
	while (last != first) {
		*(result - 1) = *(last - 1);
		--result, --last;
	}
	return last;
}
template<class iterator>
iterator _lqduninitialized_copy_aux(iterator first, iterator last,
		iterator result, true_type) {
	memmove(result, first, sizeof(value_type(first)) * (last - first));
	return result + (last - first);
}
template<class iterator>
iterator _lqduninitialized_copy_aux(iterator first, iterator last,
		iterator result, false_type) {
	iterator i = result;
	for (; first != last; ++first, ++i)
		lqdconstruct(i, *first);
	return i;
}
template<class iterator, class T>
iterator _lqduninitialized_copy(iterator first, iterator last, iterator result,
		T) {
	typedef typename lqdtype_traits<T*>::is_POD_type pod;
	return _lqduninitialized_copy_aux(first, last, result, pod());
}
template<class iterator>
iterator lqduninitialized_copy(iterator first, iterator last, iterator result) {
	return _lqduninitialized_copy(first, last, result, value_type(first));
}
#endif /* LQDALGORITHM_H_ */
