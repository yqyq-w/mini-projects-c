# C语言JSON处理项目

​																																													@yqw

## 1 main.c

### 1 main函数

**返回值类型**:  int

#### **描述1**:  

对JSON字符串进行解析和按一定格式打印；支持解析值为<u>*整数、字符串、整数数组、字符串数组、JSON格式*</u>的健值对

```c
	cJSON *head;

  // 1. parse JSON string and print 
	char test[200] = "{\"name\":\"Bob\",\"word\":\"test\",\"num\":12345,\"arrNum\":[1,11,111],\"arrStr\":[\"a\",\"ab\",\"abc\"],\"testObj\":{\"name\":\"Rob\",\"age\":10}}";  

	printf("\n======test JSON字符串====== \n%s\n\n", test);
	printf("\n======检查test JSON的括号格式======\n%d\n\n", validate_string(test));

	// strlen - 1
	printf("======开始解析cJSON 1======\n");
	head = cJSON_parse(test, 0, strlen(test) - 1); 

	printf("======开始打印cJSON 1======\n");
	print_cJSON(head, 0);
	printf("\n======结束打印cJSON 1======\n\n");

```

#### **终端运行结果1**: 

```shell
======test JSON字符串====== 
{"name":"Bob","word":"test","num":12345,"arrNum":[1,11,111],"arrStr":["a","ab","abc"],"testObj":{"name":"Rob","age":10}}


======检查test JSON的括号格式======
1

======开始解析cJSON 1======
======开始打印cJSON 1======
{
    name: Bob,
    word: test,
    num: 12345,
    arrNum: 
       [1, 11, 111],
    arrStr: 
       [a, ab, abc],
    testObj: 
       {
            name: Rob,
            age: 10
       }
}
======结束打印cJSON 1======
```



#### **描述2**:  

支持自行创建和修改JSON􏲚􏲛􏲜􏲝对象

```c
  cJSON *currentLast;  

	// 2. add, modify and print cJSON
	printf("\n\n======自行创建和添加cJSON======\n");
	int arrNum[3] = {11, 22, 33};
	char *arrStr[] = {"Apple", "Banana", "Cherry"};
	cJSON *j1 = create_cJSON_String("str", "Alice");
	cJSON *j2 = create_cJSON_Number("num", 15);
	cJSON *j3 = create_cJSON_Array_Str("arrStr", arrStr, 3);
	cJSON *j4 = create_cJSON_Array_Num("arrNum", arrNum, 3);

	j1->next = j2;
	j2->next = j3;
	j3->next = j4;
	j4->prev = j3;
	j3->prev = j2;
	j2->prev = j1;
	currentLast = j4;
	printf("\n======开始打印cJSON 2======\n");
	print_cJSON(j1, 0);
	printf("\n======结束打印cJSON 2======\n\n");

	cJSON *j5 = cJSON_addNumberToObject(currentLast, "testAddNum", 29);
	printf("\n======新创建的数据对======\n%s %d\n", j5->namestring,getNumberValue(j5));
	// currentLast == j5
	printf("\n======开始打印cJSON 3======\n");
	print_cJSON(j1, 0);
	printf("\n======结束打印cJSON 3======\n\n");
```

#### **终端运行结果2**: 

```shell
======自行创建和添加cJSON======

======开始打印cJSON 2======
{
    str: Alice,
    num: 15,
    arrStr: 
       [Apple, Banana, Cherry],
    arrNum: 
       [11, 22, 33]
}
======结束打印cJSON 2======


======新创建的数据对======
testAddNum 29

======开始打印cJSON 3======
{
    str: Alice,
    num: 15,
    arrStr: 
       [Apple, Banana, Cherry],
    arrNum: 
       [11, 22, 33],
    testAddNum: 29
}
======结束打印cJSON 3======
```



#### **描述3**: 

对JSON字符串进行基础的括号格式

```c
char wrong[50] = "{\"name\":\"Rob\",\"age\":10}}";  

// 格式校验功能
printf("\n======wrong JSON字符串====== \n%s\n", wrong);
printf("\n======检查wrong JSON的括号格式======\n%d\n", validate_string(wrong));
if (!validate_string(wrong)) {
	printf("JSON格式错误，无法解析\n");
}
```

#### **终端运行结果3**: 

```shell
======wrong JSON字符串====== 
{"name":"Rob","age":10}}

======检查wrong JSON的括号格式======
0
JSON格式错误，无法解析
```



## 2 cJSON.h & cJSON.c

### 1 cJSON结构体

**描述**: 存放健值对信息

| 参数类型       | 参数名称    | 参数描述               |
| -------------- | ----------- | ---------------------- |
| struct cJSON * | next        | 指向下一个健值对       |
| struct cJSON * | prev        | 指向前一个健值对       |
| struct cJSON * | child       | 指向数组或JSON格式的值 |
| char *         | namestring  | 健名                   |
| char *         | valuestring | 字符串值               |
| int            | type        | 值的类型               |
| int            | valueint    | 整型值                 |

```c
types:
cJSON_NULL 0
cJSON_Number 1
cJSON_String 2
cJSON_Array 3
cJSON_Object 4
```



### 2 创建新的cJSON节点 create new node

#### 2.1 create_cJSON_Null

**描述**: 创建空值cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明 | 类型  |
| -------- | -------- | ----- |
| name     | 健名     | char* |

#### 2.2 create_cJSON_Number

**描述**: 创建整型cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明 | 类型  |
| -------- | -------- | ----- |
| name     | 健名     | char* |
| num      | 整型值   | int   |

#### 2.3 create_cJSON_String

**描述**: 创建字符串cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明 | 类型  |
| -------- | -------- | ----- |
| name     | 健名     | char* |
| str      | 字符串值 | char* |

#### 2.4 cJSON_CreateArray

**描述**: 创建数组（具体类型见下）cJSON结构体

**返回值类型**:  cJSON *

**参数说明: **void



#### 2.5 create_cJSON_Array_Num

**描述**: 创建整型数组cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明     | 类型  |
| -------- | ------------ | ----- |
| name     | 健名         | char* |
| arr      | 整型数组值   | int[] |
| count    | 数组元素个数 | int   |

#### 2.6 create_cJSON_Array_Str

**描述**: 创建字符串数组cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明     | 类型     |
| -------- | ------------ | -------- |
| name     | 健名         | char*    |
| arr      | 字符串数组值 | char *[] |
| count    | 数组元素个数 | int      |

#### 2.7 create_cJSON_Object

**描述**:创建值为JSON格式的cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明 | 类型    |
| -------- | -------- | ------- |
| name     | 健名     | char*   |
| object   | JSON值   | cJSON * |



### 3 添加cJSON节点   add To Object

#### 3.1 add_item_to_object

**描述**: 增加（并连接）cJSON结构体

**返回值类型**:  cJSON *

| 参数名称 | 参数说明           | 类型    |
| -------- | ------------------ | ------- |
| addAfter | 新节点添加位置说明 | cJSON * |
| new_item | 要添加的cJSON节点  | cJSON * |

#### 3.2 cJSON_addStringToObject

**描述**: 增加字符串cJSON结构体

**返回值类型**:  cJSON *

| 参数名称        | 参数说明               | 类型    |
| --------------- | ---------------------- | ------- |
| destination     | 新节点添加位置说明     | cJSON * |
| new_name        | 待添加新节点的健名     | char *  |
| new_valuestring | 待添加新节点的字符串值 | char *  |

#### 3.3 cJSON_addNumberToObject

**描述**: 增加整型cJSON结构体

**返回值类型**:  cJSON *

| 参数名称     | 参数说明             | 类型    |
| ------------ | -------------------- | ------- |
| destination  | 新节点添加位置说明   | cJSON * |
| new_name     | 待添加新节点的健名   | char *  |
| new_valueint | 待添加新节点的整型值 | int     |



### 4 判断cJSON值的类型 is

#### 4.1 isNull

**描述**: 判断是否为空值cJSON

**返回值类型**:  int

| 参数名称 | 参数说明              | 类型    |
| -------- | --------------------- | ------- |
| item     | 待判断类型的cJSON节点 | cJSON * |

#### 4.2 isString

**描述**: 判断是否为字符串cJSON

**返回值类型**:  int

| 参数名称 | 参数说明              | 类型    |
| -------- | --------------------- | ------- |
| item     | 待判断类型的cJSON节点 | cJSON * |

#### 4.3 isNumber

**描述**: 判断是否为整型cJSON

**返回值类型**:  int

| 参数名称 | 参数说明              | 类型    |
| -------- | --------------------- | ------- |
| item     | 待判断类型的cJSON节点 | cJSON * |

 

### 5 获取cJSON的值 get

#### 5.1 getStringValue

**描述**: 获取字符串值

**返回值类型**:  int

| 参数名称 | 参数说明          | 类型    |
| -------- | ----------------- | ------- |
| item     | 待取值的cJSON节点 | cJSON * |

#### 5.2 getNumberValue

**描述**: 获取整数值

**返回值类型**:  int

| 参数名称 | 参数说明          | 类型    |
| -------- | ----------------- | ------- |
| item     | 待取值的cJSON节点 | cJSON * |



### 6  更新cJSON的值 update

#### 6.1 update_valueString

**描述**: 更新字符串值

**返回值类型**:  int

| 参数名称 | 参数说明          | 类型    |
| -------- | ----------------- | ------- |
| item     | 待更新的cJSON节点 | cJSON * |
| str      | 新的字符串值      | char *  |

#### 6.2 update_valueInt

**描述**: 更新整型值

**返回值类型**:  int

| 参数名称 | 参数说明          | 类型    |
| -------- | ----------------- | ------- |
| item     | 待更新的cJSON节点 | cJSON * |
| num      | 新的整型值        | int     |



### 7 JSON的校验、解析、打印操作 valide, parse, print

```c
// 如果格式合法
// ,个数加一
// , 前的字符判断类型
// 调用分类的parse 返回node
// \",  name起止 
// 前后node连接
// 头尾，尾 最后一个,到}
// 每组健值对的index
// 按类解析
```

#### 7.1 validate_string

**描述**: 校验JSON字符串的括号格式 {}[]

**返回值类型**:  int

| 参数名称    | 参数说明           | 类型   |
| ----------- | ------------------ | ------ |
| string_JSON | 待校验的JSON字符串 | Char * |

#### 7.2 substr

**描述**:  复制部分字符串 copy part of a string from the start index to end index

**返回值类型**:  void

| 参数名称 | 参数说明         | 类型   |
| -------- | ---------------- | ------ |
| des      | 复制到哪个字符串 | char * |
| str      | 复制于哪个字符串 | char * |
| start    | 复制开始下标位置 | int    |
| end      | 复制结束下标位置 | Int    |

#### 7.3 parse_string 

**描述**:  解析字符串健值对 parse name:string pair

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.4 parse_number

**描述**:  解析整型健值对

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.5 parse_arr_string

**描述**: 解析字符串数组健值对

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.6 parse_arr_number

**描述**: 解析整型数组健值对

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.7 parse_object

**描述**:  解析JSON健值对

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.8 parse_null

**描述**: 解析空值健值对

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| start       | 解析开始下标位置 | int    |
| end         | 解析结束下标位置 | int    |

#### 7.9 cJSON_parse

**描述**: 解析给定JSON字符串

**返回值类型**:  cJSON *

| 参数名称    | 参数说明         | 类型   |
| ----------- | ---------------- | ------ |
| string_JSON | 待解析JSON字符串 | char * |
| l           | 解析开始下标位置 | int    |
| r           | 解析结束下标位置 | int    |

#### 7.10 print_cJSON

**描述**: 按缩进格式打印cJSON

**返回值类型**:  void

| 参数名称 | 参数说明          | 类型    |
| -------- | ----------------- | ------- |
| head     | 待打印cJSON头节点 | cJSON * |
| depth    | 缩进深度          | int     |





