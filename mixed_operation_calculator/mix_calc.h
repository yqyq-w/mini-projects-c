#ifndef  _MIX_CALC_H_
#define _MIX_CALC_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 定义栈结构体
typedef struct Stack {
  double *elements;
  int top_index, max_size;
} Stack;

typedef struct Stack_opr {
  int *elements;
  int top_index, max_size;
} Stack_opr;

// Stack相关方法
void init(Stack *s, int size);

int push(Stack *s, double element);

int pop(Stack *s);

double top(Stack *s);

// Stack_opr相关方法
void init_opr(Stack_opr *s, int size);

int push_opr(Stack_opr *s, int element);

int pop_opr(Stack_opr *s);

int top_opr(Stack_opr *s);

int empty_opr(Stack_opr *s);

void clear_opr(Stack_opr *s);

// 判断优先级
int precede(char a, char b);

double power(double base, double exponent);

double sqrt(double num);

// 涉及两个数字的运算
double operate(double first, double second, char operator);

// 依次出栈计算
void calc(Stack *nums, Stack_opr *oprs);

// 实现数据计算
void mix_calc(char* expression, FILE* fp);


#endif