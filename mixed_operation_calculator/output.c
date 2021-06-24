#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mix_calc.h"

int main(){
  char expression[1000];
  int src;
  FILE *fin;
  FILE *fout;

  // 输入类型
  printf("输入类型：\n1：输入表达式，2：输入文件）\n");
  scanf("%d", &src);

  if (src == 1) {
    printf("请输入表达式：");
    scanf("%s", expression);
    // 运算，标准输出
    mix_calc(expression, stdout);
  } else if (src == 2) {
    // printf("请输入文件名：");  // ./exp   // scanf("&s", fname);
    fin = fopen("./exp", "r");
    fout = fopen("./exp.out", "a+");

    // 循环读取算式、写入答案
    while (~fscanf(fin, "%s", expression)) {
      // printf("length = %d\n", (int)strlen(expression));
      mix_calc(expression, fout);
    }
  }
  return 0;
}
