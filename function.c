/*
 * @file       function.c   
 * @author     DLSZ
 * @date       2018-03-09
 */

#include "common.h"
#include "include.h"

// constrain a float value
float constrain_float(float amt, float low, float high) 
{
	if (isnan(amt)) {
		return (low+high)*0.5f;
	}
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// constrain a int16_t value
int16_t constrain_int16(int16_t amt, int16_t low, int16_t high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// constrain a int32_t value
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

