# 105 实现输出功能

## 1 output.c

### 1 main函数

**返回值类型**:  int

**描述1**: 对于从标准输入中读取的单个数学表达式，直接输出到标准输出中

```c
// 输入类型
  printf("输入类型：\n1：输入表达式，2：输入文件）\n");
  scanf("%d", &src);

  if (src == 1) {
    printf("请输入表达式：");
    scanf("%s", expression);
    // 运算，标准输出
    mix_calc(expression, stdout);
  }
```

**描述2**: 对于从文件中读取的数学表达式，输出到原文件名.out中

```c
  } else if (src == 2) {
    fin = fopen("./exp", "r");
    fout = fopen("./exp.out", "a+");

    // 循环读取算式、写入答案
    while (~fscanf(fin, "%s", expression)) {
      mix_calc(expression, fout);
    }
  }
```

**描述3**: 支持表达式异常错误处理

```shell
length = 3
@-1 = error, sqrt不支持负数!

length = 5
1+2/0 = error, divide 0
```



## 2 mix_calc.h & mix_calc.c

```c
符号优先级（从高到低）:
第1级: (
第2级: @ （开方）
第3级: ^ （幂次）
第4级: * /
第5级: + -
第6级: )
```

### 1 Stack

**描述**: 存放数字的栈

| 相关方法名称 | 参数                     | 返回值类型 |
| ------------ | ------------------------ | ---------- |
| init         | Stack *s, int size       | void       |
| push         | Stack *s, double element | int        |
| pop          | Stack *s                 | int        |
| top          | Stack *s                 | double     |
| empty        | Stack *s                 | int        |
| clear        | Stack *s                 | void       |

### 2 Stack_opr

**描述**: 存放计算符号的栈

| 相关方法名称 | 参数                      | 返回值类型 |
| ------------ | ------------------------- | ---------- |
| init_opr     | Stack_opr *s, int size    | void       |
| push_opr     | Stack_opr *s, int element | int        |
| pop_opr      | Stack_opr *s              | int        |
| top_opr      | Stack_opr *s              | int        |
| empty_opr    | Stack_opr *s              | int        |
| clear_opr    | Stack_opr *s              | void       |

### 3 precede函数

**描述**: 判断计算符号优先级

**返回值类型**:  int

| 参数名称 | 参数说明         | 类型 |
| -------- | ---------------- | ---- |
| a        | 当前读取到的符号 | char |
| b        | 当前栈顶的符号   | char |

### 4 sqrt函数

**描述**: 实现开平方操作

**返回值类型**:  double

| 参数名称 | 参数说明         | 类型   |
| -------- | ---------------- | ------ |
| num      | 被开平方根的正数 | double |

### 5 power函数

**描述**: 实现幂次操作 

**返回值类型**:  double

| 参数名称 | 参数说明 | 类型   |
| -------- | -------- | ------ |
| base     | 底数     | double |
| exponent | 指数     | double |

### 6 operate函数

**描述**: 涉及两个数字的运算

**返回值类型**:  double

| 参数名称 | 参数说明           | 类型   |
| -------- | ------------------ | ------ |
| first    | 第一个出栈的数字   | double |
| second   | 第二个出栈的数字   | double |
| operator | 当前栈顶的运算符号 | char   |

### 7 calc函数

**描述**: 依次出栈计算

**返回值类型**:  double

| 参数名称 | 参数说明   | 类型        |
| -------- | ---------- | ----------- |
| nums     | 数字栈指针 | Stack *     |
| oprs     | 符号栈指针 | Stack_opr * |

### 8 mix_calc函数

**描述**: 实现数据计算

**返回值类型**:  void

| 参数名称   | 参数说明        | 类型  |
| ---------- | --------------- | ----- |
| expression | 字符指针        | char* |
| fp         | 文件/输出流指针 | FILE* |

## **示例1** 从表达式输入

```shell
# 输入表达式
yiqingwang@yqw output函数功能 % gcc output.c
yiqingwang@yqw output函数功能 % ./a.out     
输入类型：
1：输入表达式，2：输入文件）
1
请输入表达式：1+2/0
1+2/0 = error, divide 0
```

## **示例2 **从文件输入

```shell
# 输入文件
yiqingwang@yqw output函数功能 % ./a.out     
输入类型：
1：输入表达式，2：输入文件）
2

# exp.out文件中写入答案
length = 3
@-1 = error, sqrt不支持负数!

length = 7
2*(1+2) = 6.0000

length = 4
@9^4 = 81.0000

length = 5
1+2/0 = error, divide 0

length = 5
1+3/2 = 2.5000

length = 4
2+-1 = 1.0000

length = 4
-1*3 = -3.0000

length = 14
1+2*(1+2)/@5^3 = 1.5367
```

@author：wyq

