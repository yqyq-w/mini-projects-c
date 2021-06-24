#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "cJSON.h"

int main() {

	cJSON *head;
    cJSON *currentLast;

    // 1. parse JSON string and print 
	char test[200] = "{\"name\":\"Bob\",\"word\":\"test\",\"num\":12345,\"arrNum\":[1,11,111],\"arrStr\":[\"a\",\"ab\",\"abc\"],\"testObj\":{\"name\":\"Rob\",\"age\":10}}";  
	char wrong[50] = "{{\"name\":\"Rob\",\"age\":10}";  
    // for (int i = 0; i < strlen(test); i++) printf("%c\n", test[i]);

	printf("\n======test JSON字符串====== \n%s\n\n", test);
	printf("\n======检查test JSON的括号格式======\n%d\n\n", validate_string(test));

	// strlen - 1
	printf("======开始解析cJSON 1======\n");
	head = cJSON_parse(test, 0, strlen(test) - 1); 

	printf("======开始打印cJSON 1======\n");
	print_cJSON(head, 0);
	printf("\n======结束打印cJSON 1======\n\n");

	// 格式校验功能
	printf("\n======wrong JSON字符串====== \n%s\n", wrong);
	printf("\n======检查wrong JSON的括号格式======\n%d\n", validate_string(wrong));
	if (!validate_string(wrong)) {
		printf("JSON格式错误，无法解析\n");
	}

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

	return 0;
}





