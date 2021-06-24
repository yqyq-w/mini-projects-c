#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mix_calc.h"

#define ERROR 0
#define OK 1
/*
符号优先级（从高到低）:
第1级: (
第2级: @
第3级: ^
第4级: * /
第5级: + -
第6级: )
*/

// Stack相关方法
void init(Stack *s, int size) {
  s->elements = (double *)malloc(sizeof(double) * size);
  s->max_size = size;
  s->top_index = -1;
}

int push(Stack *s, double element) {
  // 边界 >= s->max_size - 1
  if (s->top_index >= s->max_size - 1) return ERROR;
  s->top_index++;
  s->elements[s->top_index] = element;
  return OK;
}

int pop(Stack *s) {
  if (s->top_index < 0) return ERROR;
  s->top_index--;
  return OK;
}

double top(Stack *s) {
  return s->elements[s->top_index];
}

int empty(Stack *s) {
  if (s->top_index < 0) return 1;
  return 0;
}

void clear(Stack *s) {
  free(s->elements);
  free(s);
}

// Stack_opr相关方法
void init_opr(Stack_opr *s, int size) {
  s->elements = (int *)malloc(sizeof(int) * size);
  s->max_size = size;
  s->top_index = -1;
}

int push_opr(Stack_opr *s, int element) {
  // 边界 >= s->max_size - 1
  if (s->top_index >= s->max_size - 1) return ERROR;
  s->top_index++;
  s->elements[s->top_index] = element;
  return OK;
}

int pop_opr(Stack_opr *s) {
  if (s->top_index < 0) return ERROR;
  s->top_index--;
  return OK;
}

int top_opr(Stack_opr *s) {
  return s->elements[s->top_index];
}

int empty_opr(Stack_opr *s) {
  if (s->top_index < 0) return 1;
  return 0;
}

void clear_opr(Stack_opr *s) {
  free(s->elements);
  free(s);
}

// 判断优先级
int precede(char a, char b) {
  // if (a == ')') return 0;
  if (a == '(') return 1;
  if (a == '^') return 1;
  if ((a == '*' || a == '/') && (b == '+' || b == '-')) return 1;
  return 0;
}

double power(double base, double exponent) {
  // corner cases 底数为零或一
  if (base == 0 || base == 1) return base;
  // 零次方
  if (exponent == 0) return 1.0;

  double outcome = 1.0;
  // 次方正负分类讨论 
  if (exponent < 0) outcome /= power(base, -exponent);
  else { 
    while (exponent--) {
      outcome *= base;
    }
  }
  return outcome;
}

double sqrt(double num) {
  // 二分计算近似平方根，误差小于1e-7终止循环
  double l = 0, r = num, mid;
  while (num - mid * mid > 1e-7 || mid * mid - num > 1e-7) {
    // >> 位运算只能整数; 更新上下限
    mid = (l + r) / 2.0; 
    if (mid * mid > num) r = mid;
    if (mid * mid < num) l = mid;
  }
  return mid;
}


// 涉及两个数字的运算
double operate(double first, double second, char operator) {
  if (operator == '+') return first + second;
  else if (operator == '-') return second - first;    
  else if (operator == '*') return first * second;
  else if (operator == '/') return second / first;
  else return power(second, first); 
}


// 依次出栈计算
void calc(Stack *nums, Stack_opr *oprs) {
  double a = top(nums);
  pop(nums);
  double b = top(nums);    
  pop(nums);
  // 新答案入栈
  push(nums, operate(a, b, top_opr(oprs)));
  pop_opr(oprs);
}

// 实现数据计算
void mix_calc(char* expression, FILE* fp) {
  int len = strlen(expression);

  Stack *nums = (Stack *)malloc(sizeof(Stack));
  init(nums, len);
  Stack_opr *oprs = (Stack_opr *)malloc(sizeof(Stack_opr));
  init_opr(oprs, len);
    
    
  int i = 0;
  int last_pos = 0;
  int temp_pos = 0;
  while (i < len) {
    if (isdigit(expression[i])) {
    // 字符转为数字，8 + ‘0’; 数字化转为字符, expression[i] - '0'  // 将字符串转换为双精度浮点数(double)，double atof (const char* str); // push(nums,atof(buffer[i]));
      push(nums, expression[i] - '0');
      i++;
    } else {
      temp_pos = i;
      // 判断是否负数
      if (expression[i] == '-' && temp_pos - last_pos <= 1) {
        push(nums, -(expression[++i] - '0'));
        i++;
        last_pos = temp_pos;
        continue;
      }
      last_pos = temp_pos;
      // 分类讨论
      if (expression[i] == ')') {
        while (top_opr(oprs) != '(') {
          calc(nums, oprs);
        }
        pop_opr(oprs);
        i++;
      } else if (expression[i] == '@') {
        if (expression[++i] == '-') {
          // printf("%s = %s\n", expression,"error,sqrt不支持负数!\n");
          fprintf(fp, "%s = %s\n", expression,"error, sqrt不支持负数!\n");
          return;
        }
        push(nums, sqrt(expression[i] - '0'));
        i++;
      } else if (empty_opr(oprs) || top_opr(oprs) == '(' || precede(expression[i], top_opr(oprs))) {
        if (expression[i] == '/' && expression[i+1] == '0'){
          // printf("%s = %s\n", expression, "error, divide 0\n");
          fprintf(fp, "%s = %s\n", expression, "error, divide 0\n");
          return;
        }
        push_opr(oprs, expression[i]);
        i++;
      } else {
        calc(nums, oprs);
      }
    }
    // printf("第%d次后：%.4lf\n", i, top(nums)); printf("第%d次后：%c\n", i, top(oprs));
  }
    
  while (!empty_opr(oprs)) {
    calc(nums, oprs);
  }

  // printf("%s = %.4lf\n\n", expression, top(nums));
  fprintf(fp, "%s = %.4lf\n\n", expression, top(nums));
  clear(nums);
  clear_opr(oprs);
}
