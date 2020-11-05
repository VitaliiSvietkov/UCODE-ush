#include "../inc/libmx.h"

int mx_abs(int i) {
    if (i < 0)
	    return i * -1;
    return i;  
}

