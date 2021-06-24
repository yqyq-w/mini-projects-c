#ifndef cJSON_h
#define cJSON_h

#define cJSON_NULL 0
#define cJSON_Number 1
#define cJSON_String 2
#define cJSON_Array  3
#define cJSON_Object 4

/*
cJSON 结构体
*/
typedef struct cJSON {

	struct cJSON *next;
    struct cJSON *prev;

    struct cJSON *child;

    char *namestring;
	char *valuestring;
    int type;
    int valueint;

} cJSON;

// create new node
/*
创建空值cJSON结构体
*/
cJSON *create_cJSON_Null(char* name);

/*
创建整型cJSON结构体
*/
cJSON *create_cJSON_Number(char* name, int num);

/*
创建字符串cJSON结构体
*/
cJSON *create_cJSON_String(char* name, char *str);

/*
创建数组（具体类型见下）cJSON结构体
*/
cJSON *cJSON_CreateArray(void);

/*
创建整型数组cJSON结构体
*/
cJSON *create_cJSON_Array_Num(char* name, int arr[], int count);

/*
创建字符串数组cJSON结构体
*/
cJSON *create_cJSON_Array_Str(char* name, char *arr[], int count);

/*
创建JSON格式值的cJSON结构体
*/
cJSON *create_cJSON_Object(char* name, cJSON *object);

// cJSON add To Object
/*
增加（并连接）cJSON结构体
*/
cJSON *add_item_to_object(cJSON *addAfter, cJSON *new_item);

/*
增加字符串cJSON结构体
*/
cJSON *cJSON_addStringToObject(cJSON *destination, char *new_name, char* new_valuestring);
/*
增加整型cJSON结构体
*/
cJSON *cJSON_addNumberToObject(cJSON *destination, char *new_name, int new_valueint);

// addArray
/*
增加整型数组cJSON结构体
*/
/*
增加字符串数组cJSON结构体
*/
// addObject
/*
增加JSON cJSON结构体
*/


// is 判断cJSON类型
/*
判断是否为空值cJSON
*/
int isNull(cJSON *item);
/*
判断是否为字符串cJSON
*/
int isString(cJSON *item);

/*
判断是否为整型cJSON
*/
int isNumber(cJSON *item);

// get 获取cJSON的值
/*
获取字符串值
*/
char* getStringValue(cJSON *item);

/*
获取整数值
*/
int getNumberValue(cJSON *item);

// update 更新值
/*
更新字符串值
*/
cJSON *update_valueString(cJSON *item, char *str);

/*
更新整型值
*/
cJSON *update_valueInt(cJSON *item, int num);


// valide, parse, print
/*
	// 如果格式合法
	// ,个数加一
	// , 前的字符判断类型
	// 调用分类的parse 返回node

	// \",  name起止 
	// 前后node连接
	// 头尾，尾 最后一个,到}

	// 每组健值对的index
	// 按类解析
*/
int validate_string(char *string_JSON);


// 复制部分字符串 copy part of a string from the start index to end index
void substr(char *des, char *str, int start, int end);

/*
解析字符串健值对
*/
// parse name:string pair
cJSON *parse_string(char *string_JSON, int start, int end);

/*
解析整型健值对
*/
cJSON *parse_number(char *string_JSON, int start, int end);

/*
解析字符串数组健值对
*/
cJSON *parse_arr_string(char *string_JSON, int start, int end);

/*
解析整型数组健值对
*/
cJSON *parse_arr_number(char *string_JSON, int start, int end);

/*
解析JSON健值对
*/
cJSON *parse_object(char *string_JSON, int start, int end);

/*
解析空值健值对
*/
cJSON *parse_null(char *string_JSON, int start, int end);

/*
解析给定JSON字符串
*/
cJSON *cJSON_parse(char *string_JSON, int l, int r);


/*
按缩进格式打印cJSON
*/
void print_cJSON(cJSON *head, int depth);


#endif