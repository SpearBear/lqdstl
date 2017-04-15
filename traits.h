/*
 * traits.h
 *
 *  Created on: Apr 12, 2017
 *      Author: c
 */

#ifndef TRAITS_H_
#define TRAITS_H_
struct false_type {
};
struct true_type {
};
struct input_tag {
};
struct output_tag {
};
struct forward_tag: public input_tag {
};
struct bidirectional_tag: public forward_tag {
};
struct random_access_tag: public bidirectional_tag {
};
template<class category, class T, class distance = ptrdiff_t,
		class reference = T&, class pointer = T*>
struct iterator {
	typedef category iterator_category;
	typedef T value_type;
	typedef distance difference_type;
	typedef reference ref;
	typedef pointer ptr;
};
template<class iterator>
struct lqditerator_traits {
	typedef typename iterator::iterator_category iterator_category;
	typedef typename iterator::value_type value_type;
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::ref ref;
	typedef typename iterator::ptr ptr;
};
template<class T>
struct lqditerator_traits<T*> {
	typedef random_access_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& ref;
	typedef T* ptr;
};
template<class T>
struct lqditerator_traits<const T*> {
	typedef random_access_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef const T& ref;
	typedef const T* ptr;
};
template<class iterator>
typename iterator_traits<iterator>::iterator_category lqditerator_category(
		const iterator&) {
	typedef typename iterator_traits<iterator>::iterator_category category;
	return category();
}
template<class iterator>
typename lqditerator_traits<iterator>::difference_type* lqddistance_type(
		const iterator&) {
	return static_cast<typename iterator_traits<iterator>::difference_type*> (0);
}
template<class T>
struct _lqditerator_traits;
template<class inputiterator>
typename _lqditerator_traits<inputiterator>::difference_type _lqddistance(
		inputiterator first, inputiterator last, input_tag) {
	typename iterator_traits<inputiterator>::difference_type n = 0;
	while (first != last) {
		++first;
		++n;
	}
	return n;
}
template<class randomaccessiterator>
typename _lqditerator_traits<randomaccessiterator>::difference_type _lqddistance(
		randomaccessiterator first, randomaccessiterator last,
		random_access_tag) {
	return last - first;
}
template<class iterator>
typename lqditerator_traits<iterator>::difference_type lqddistance(
		iterator first, iterator last) {
	typedef typename iterator_traits<iterator>::iterator_category category;
	return _lqddistance(first, last, category());
	//return distance(first, last, iterator_category(i));
}
template<class inputiterator, class distance>
void _lqdadvance(inputiterator& i, distance n, input_tag) {
	while (n--)
		++i;
}
template<class bidirectionaliterator, class distance>
void _lqdadvance(bidirectionaliterator& i, distance n, bidirectional_tag) {
	if (n > 0)
		while (n--)
			++i;
	else
		while (n++)
			--i;
}
template<class randomaccessiterator, class distance>
void _lqdadvance(randomaccessiterator& i, distance n, random_access_tag) {
	i += n;
}
template<class iterator, class distance>
void lqdadvance(iterator& i, distance n) {
	_lqdadvance(i, n, iterator_category(i));
}
//template<class T>
//struct lqdtype_traits<T> {
//	typedef true_type has_trivial_default_constructor;
//	typedef true_type has_trivial_copy_constructor;
//	typedef true_type has_trivial_assignment_operator;
//	typedef true_type has_trivial_destructor;
//	typedef true_type is_POD_type;
//};
template<class T>
typename lqditerator_traits<T>::value_type value_type(const T&) {
	return typename lqditerator_traits<T>::value_type();
}
template<class T>
struct lqdtype_traits;
template<>
struct lqdtype_traits<char> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<signed char> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<unsigned char> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<short> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<int> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<unsigned int> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<long> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<unsigned long> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<float> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<>
struct lqdtype_traits<double> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
template<class T>
struct lqdtype_traits<T*> {
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
};
#endif /* TRAITS_H_ */
