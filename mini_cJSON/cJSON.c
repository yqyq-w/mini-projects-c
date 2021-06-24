#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "cJSON.h"

// create new node
/*
创建空值cJSON结构体
*/
cJSON *create_cJSON_Null(char* name){
	cJSON *item = (cJSON *)malloc(sizeof(cJSON));
	item->type = cJSON_NULL;
	return item;
}

/*
创建整型cJSON结构体
*/
cJSON *create_cJSON_Number(char* name, int num){
	cJSON *item = (cJSON *)malloc(sizeof(cJSON));
	item->type = cJSON_Number;
	item->namestring = name;
	item->valueint = num;
	return item;
}

/*
创建字符串cJSON结构体
*/
cJSON *create_cJSON_String(char* name, char *str){
	cJSON *item = (cJSON *)malloc(sizeof(cJSON));
	item->type = cJSON_String;
	item->namestring = name;
	item->valuestring = str;
	return item;
}


/*
创建数组（具体类型见下）cJSON结构体
*/
cJSON *cJSON_CreateArray(void) {
	cJSON *item = (cJSON *)malloc(sizeof(cJSON));
	item->type=cJSON_Array;
	return item;
}


/*
创建整型数组cJSON结构体
*/
cJSON *create_cJSON_Array_Num(char* name, int arr[], int count){
	cJSON *item = cJSON_CreateArray();
	item->namestring = name;

	item->child = create_cJSON_Number("", arr[0]);
	cJSON *childNode = item->child;

	for (int i = 1; i < count; i++) {
		cJSON *newNode = create_cJSON_Number("", arr[i]);
		childNode->next = newNode;
		newNode->prev = childNode;

		childNode = childNode->next;
	}

	return item;
}

/*
创建字符串数组cJSON结构体
*/
cJSON *create_cJSON_Array_Str(char* name, char *arr[], int count){
	cJSON *item = cJSON_CreateArray();
	item->namestring = name;

	item->child = create_cJSON_String("", arr[0]);
	cJSON *childNode = item->child;

	for (int i = 1; i < count; i++) {
		cJSON *newNode = create_cJSON_String("", arr[i]);
		childNode->next = newNode;
		newNode->prev = childNode;

		childNode = childNode->next;
	}

	return item;
}


/*
创建JSON格式值的cJSON结构体
*/
cJSON *create_cJSON_Object(char* name, cJSON *object){
	cJSON *item = (cJSON *)malloc(sizeof(cJSON));
	item->type = cJSON_Object;
	item->namestring = name;

	item->child = object;

	return item;
}

// cJSON add To Object
/*
增加（并连接）cJSON结构体
*/
cJSON *add_item_to_object(cJSON *addAfter, cJSON *new_item) {
	if (addAfter->next != NULL) {		
		cJSON *nodeNext = addAfter->next;
		//
		new_item->next = nodeNext;
		nodeNext->prev = nodeNext;
		addAfter->next = new_item;
	}

	// addAfter->next == NULL 说明是tail
	addAfter->next = new_item;
	new_item->prev = addAfter;

	return new_item;
}

/*
增加字符串cJSON结构体
*/
cJSON *cJSON_addStringToObject(cJSON *destination, char *new_name, char* new_valuestring) {
    cJSON *string_item = create_cJSON_String(new_name, new_valuestring);
    return add_item_to_object(destination, string_item);
}

/*
增加整型cJSON结构体
*/
cJSON *cJSON_addNumberToObject(cJSON *destination, char *new_name, int new_valueint) {
	cJSON *num_item = create_cJSON_Number(new_name, new_valueint);
    return add_item_to_object(destination, num_item);
}

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
int isNull(cJSON *item) {
	if (item == NULL) return 0;

    return item->type == cJSON_NULL;
}

/*
判断是否为字符串cJSON
*/
int isString(cJSON *item) {
	if (item == NULL) return 0;

    return item->type == cJSON_String;

}

/*
判断是否为整型cJSON
*/
int isNumber(cJSON *item) {
	if (item == NULL) return 0;

    return item->type == cJSON_Number;
}



// get 获取cJSON的值
/*
获取字符串值
*/
char* getStringValue(cJSON *item) {
	if (!isString(item)) return NULL;

    return item->valuestring;
}

/*
获取整数值
*/
int getNumberValue(cJSON *item) {
	if (!isNumber(item)) return -1;

    return item->valueint;
}


// update 更新值
/*
更新字符串值
*/
cJSON *update_valueString(cJSON *item, char *str) {
	if (!isString(item)) item->type = cJSON_String;

    item->valuestring = str;

    return item;
}

/*
更新整型值
*/
cJSON *update_valueInt(cJSON *item, int num) {
	if (!isNumber(item)) item->type = cJSON_Number;

    item->valueint = num;

    return item;
}

// 校验、解析、打印cJSON valide, parse, print 

	// 如果格式合法
	// ,个数加一
	// , } 前的字符判断类型
	// 每组健值对的index，按类解析，\" 作为name起止 
	// 调用分类的parse 返回node
	// 前后node连接


/*
校验JSON括号格式
*/
int validate_string(char *string_JSON) {

	int res, index_l = 0;
	char left[50];

	for (int i = 0; i < strlen(string_JSON); i++) {
		if (string_JSON[i] == '{') left[index_l++] = '{';

		if (string_JSON[i] == '[') left[index_l++] = '[';

		if (string_JSON[i] == ']') {
			// printf("] left[index_l]: %c\n", left[index_l]); // printf("] left[index_l - 1]: %c\n", left[index_l - 1]);
			if (left[--index_l] !='[') {
				return 0;
			}
		}

		if (string_JSON[i] == '}') {
			if (left[--index_l] !='{') {
				return 0;
			}
		}
	
	}

	return index_l <= 0;
}


/*
复制部分字符串 copy part of a string from the start index to end index
*/
void substr(char *des, char *str, int start, int end) {
	for (int i = start; i <= end; i++) des[i - start]= str[i];
	des[end - start + 1] = '\0';
}

/*
解析字符串健值对 parse name:string pair
*/
cJSON *parse_string(char *string_JSON, int start, int end) {
	// printf("======parse_string======\n");
	// for (int k = start; k <= end; k++) printf("%c\n", string_JSON[k]);

	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);
	// printf("name: %s\n", name);

	// valuestring
	while (string_JSON[++i] != '\"' && i < end) i++;

	char *valuestring = (char *)malloc(end - i - 1);
	substr(valuestring, string_JSON, i + 1, end - 1);
	// printf("valuestring: %s\n", valuestring);

	cJSON *node = create_cJSON_String(name, valuestring);

	return node;

}

/*
解析整型健值对
*/
cJSON *parse_number(char *string_JSON, int start, int end) {

	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);
	// printf("name: %s\n", name);

	// valueint
	char *valueint_str = (char *)malloc(end - i);
	substr(valueint_str, string_JSON, i + 1, end);   // printf("valueint_str: %s\n", valueint_str);
	
	int len = strlen(valueint_str);
	double res;
	int valueint;
	for (int j = 0; j < len; j++) {  // printf("%d\n", valueint_str[j] - '0');  // printf("%lf\n", (valueint_str[j] - '0') * pow(10, len - j - 1));
		res += ((valueint_str[j] - '0') * pow(10, len - j - 1));
	}
	valueint = (int)res;
	// printf("final %d\n", valueint);

	cJSON *node = create_cJSON_Number(name, valueint);

	return node;
}

/*
解析字符串数组健值对
*/
cJSON *parse_arr_string(char *string_JSON, int start, int end) {

	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);  // printf("name: %s\n", name);

	// string array
	int j, count = 0;
	for (j = i + 1; j <= end; j++) if (string_JSON[j] == ',') count++;  // printf("%c", string_JSON[j]);

	int s, e, finish, index = 0;
	char *arr[++count];

	// for (j = i + 1; j <= end; j++) printf("%c", string_JSON[j]);
	for (j = i; j <= end; j++) {

		if (string_JSON[j] == '\"'){ 
			s = ++j;
			while (string_JSON[j] != '\"') j++;
			e = j - 1;
			// printf("\ns e :%d  %d\n", s,e);

			int len = e - s + 1;
			char *str = (char *)malloc(len + 1);
			substr(str, string_JSON, s, e); 

			// printf("str %s\n", str);
			arr[index++] = str;
		}
	}

	cJSON *node = create_cJSON_Array_Str(name, arr, count);

	return node;

}

/*
解析整型数组健值对
*/
cJSON *parse_arr_number(char *string_JSON, int start, int end) {

	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);
	// printf("name: %s\n", name);

	// number array
	int j, count = 0;
	for (j = i + 1; j <= end; j++) if (string_JSON[j] == ',') count++;  // printf("%c", string_JSON[j]);

	int s, e, index = 0;
	int arr[++count];

	for (j = i + 1; j <= end; j++) {

		if (isdigit(string_JSON[j])){
			s = j;
			while (isdigit(string_JSON[j])) j++;
			e = j - 1;
			// printf("s e :%d  %d\n", s,e);

			int len = e - s + 1;
			char *num = (char *)malloc(len + 1);
			substr(num, string_JSON, s, e);
			// printf("num %s\n", num);

			double res = 0;
			int valueint;
			for (int m = 0; m < len; m++) {
				// printf("res before %lf\n", res);
				res += ((num[m] - '0') * pow(10, len - m - 1));
				// printf("res after %lf\n", res);
			}
			valueint = (int)res; 
			arr[index++] = valueint;
		}
	}

	cJSON *node = create_cJSON_Array_Num(name, arr, count);

	return node;

}

/*
解析JSON健值对
*/
cJSON *parse_object(char *string_JSON, int start, int end) {

	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);
	// printf("name: %s\n", name);
	// for (int j = i; j <= end; j++) printf("%c", string_JSON[j]);

	cJSON *child = cJSON_parse(string_JSON, i, end);
	cJSON *node = create_cJSON_Object(name, child);

	return node;

}

/*
解析空值健值对
*/
cJSON *parse_null(char *string_JSON, int start, int end) {
	// name
	int i = start;
	while (string_JSON[i] != ':' && i < end) i++;

	char *name = (char *)malloc(i - start - 1);
	substr(name, string_JSON, start + 1, i - 2);
	// printf("name: %s\n", name);

	cJSON *node = create_cJSON_Null(name);

	return node;

}

/*
解析给定JSON字符串
*/
cJSON *cJSON_parse(char *string_JSON, int l, int r) {
	// printf("r : %d\n", r);
	int start, end = 0;  
	cJSON *head = NULL;
	cJSON *current = NULL;

	for (int i = l; i <= r; i++) {  // printf("before i = %d\n", i);
		// 确定每个健值对的起止解析位置
		if (string_JSON[i] == '\"') {
			start = i;
			// printf("start = %d\n", start);

			while (string_JSON[i] != ',' && i < r) {
				i++;
				// arr
				if (string_JSON[i] == '[') {
					while (string_JSON[i] != ']') { 
						i++;
					}
					i++;
					break;
				}

				// obj
				if (string_JSON[i] == '{') {
					while (string_JSON[i] != '}') { 
						i++;
					}
					i++;
					break;
				}
				// printf("string_JSON[i] = %c\n", string_JSON[i]); // printf("in loop i++ = %d\n", i);
			}
			end = i - 1;
			// printf("end %d = %c\n", end, string_JSON[end]);

			cJSON *newNode;
			switch (string_JSON[end]) {
				case '0':
            	case '1':
            	case '2':
            	case '3':
            	case '4':
            	case '5':
            	case '6':
            	case '7':
            	case '8':
            	case '9':
            		// number
            		newNode = parse_number(string_JSON, start, end);
            		break;
				case '\"':
					// string
					newNode = parse_string(string_JSON, start, end);
					break;
				case ']':
					// array
					if (string_JSON[end - 1] == '\"') newNode = parse_arr_string(string_JSON, start, end);
					else newNode = parse_arr_number(string_JSON, start, end);
					break;
				case '}':
					// object
					newNode = parse_object(string_JSON, start, end);
					break;
				case ':':
					// null
					newNode = parse_null(string_JSON, start, end);
			}
			// link new cJSON nodes
			if (head == NULL) {
				head = newNode;
				current = head;
			} else {
				current->next = newNode;
				newNode->prev = current;
				current = current->next;
			}
		}
	}
	return head;
}

/*
按缩进格式打印cJSON
*/
void print_cJSON(cJSON *head, int depth) {
	if (head == NULL) printf("%s\n", "null");

	/* 输出depth * 4个空格 */
	// if (head->headOrTail) 
	printf("%*s\n%*s", depth * 4, "{", (depth + 1) * 4, ""); 

	while (head != NULL) {

		switch(head->type){
			case cJSON_NULL:
				printf("%s: %s", head->namestring, NULL);
				break;
			case cJSON_String:
				printf("%s: %s", head->namestring, head->valuestring);
				break;
			case cJSON_Number:
				printf("%s: %d", head->namestring, head->valueint);
				break;
			case cJSON_Array:
				printf("%s: ", head->namestring);
				cJSON * arrNode = head->child;
				printf("\n%*c", (depth + 2) * 4, '[');

				if (arrNode != NULL && arrNode->type == cJSON_Number) {
					printf("%d", arrNode->valueint);
					while ((arrNode = arrNode->next) != NULL) {
						printf(", %d", arrNode->valueint);
					}

				} else if (arrNode != NULL && arrNode->type == cJSON_String) {
					printf("%s", arrNode->valuestring);
					while ((arrNode = arrNode->next) != NULL) {
						printf(", %s", arrNode->valuestring);
					}

				}
				
				printf("%c", ']');

				break;
			case cJSON_Object:
				printf("%s: \n", head->namestring);
				print_cJSON(head->child, depth + 2);
		}

		head = head->next;
		if (head != NULL) printf(",\n%*s", (depth + 1) * 4, "");
		else printf("\n");
	}

	// if (head->headOrTail) 
	printf("%*s", depth * 4, "}"); 
		
}
