#ifndef INC_PRINT_HPP_
#define INC_PRINT_HPP_


#include <cstdio>
#include "stdio.h"

extern "C" int _write(int le, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}


#endif /* INC_PRINT_HPP_ */
