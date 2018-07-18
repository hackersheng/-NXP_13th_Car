#ifndef _FUNCTION_H
#define _FUNCTION_H

/*
 * Include 一些自定义函数的头文件
 */

///////////////////  函数外部声明   ///////////////////////////
//extern
// constrain a float value
extern float constrain_float(float amt, float low, float high);
// constrain a int16_t value
extern int16_t constrain_int16(int16_t amt, int16_t low, int16_t high); 
// constrain a int32_t value
extern int32_t constrain_int32(int32_t amt, int32_t low, int32_t high);






///////////////////  变量外部声明   ///////////////////////////




#endif  //__FUNCTION_H__