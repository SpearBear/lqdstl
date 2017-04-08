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
class lqdallocator {
public:
	//directly get space
	int allcat(int size, void** ptr) {
		*ptr = malloc(size);
		if (!ptr)
			return 0;
		return 1;
	}
private:

};
#endif /* LQDALLOCATOR_H_ */
