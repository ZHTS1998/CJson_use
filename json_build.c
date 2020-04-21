#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"cJSON.h"

#define MAX_ID_LEN 8
#define MAX_NAME_LEN 9
#define MIN_NAME_LEN 5
typedef enum _type{STUDENT, TEACHER}TYPE;
typedef enum _gender{MALE, FEMALE}GENDER;
struct _contacts{
	char id[MAX_ID_LEN+1];
	char name[MAX_NAME_LEN+1];
	GENDER gender;
	TYPE type;
	char *mobile_phones;
	
};
typedef struct _contacts Contacts;

int main(){
	int contacts_size = 0;
	Contacts contact_list[10];
	char tem =' ';
	char ch;
	int x1 = 0,y1 = 0;
	int x2 = 0,y2 = 0;
	int rt1,rt2,rt3,rt4;
	int n = 0,i=0;
	char id[MAX_ID_LEN+1];
	char name[MAX_NAME_LEN+1];
	GENDER gender;
	TYPE type;
	char *mobile_phones;

	int flag = 0;
	while((ch = getchar())){
		if(ch == '\n' && tem == '\n') break;
		tem = ch;
		if(ch == ' ') {
			i = 0;
			n++;
			continue;
		}
		if(ch == '\n'){
				flag = 0;
		
			Contacts contact ;
			id[MAX_ID_LEN] = '\0';
			strcpy(contact.id , id);
			strcpy(contact.name , name);
			contact.type = type;
			contact.gender = gender;
			contact.mobile_phones = (char*)malloc(24*sizeof(char));
			strcpy(contact.mobile_phones , mobile_phones);
			
			contact_list[contacts_size] = contact;
			contacts_size++;
			if(type == 0&&gender == 0) x1++;
			if(type == 0&&gender == 1) y1++;
			if(type == 1&&gender == 0) x2++;
			if(type == 1&&gender == 1) y2++;
			n++;
			i=0;
				free(mobile_phones);
			continue;
		}
		if(n %5 ==0){
			id[i++] = ch;
			continue;
		}
		if(n%5 == 1){
			if(ch == '1')
			type = 1;
			if(ch == '0')
			type = 0;
			continue;
		}
		if(n%5== 2){
			name[i++] = ch;
			name[i] = '\0';
			continue;
		}
		if(n%5 == 3){
			if(ch == '1')
			gender = 1;
			if(ch == '0')
			gender = 0;
			continue;
		}
		if(n%5 == 4){
			if(flag == 0){
			mobile_phones = (char*)malloc(24*sizeof(char));
			flag = 1;
		}
			mobile_phones[i++] = ch;
			mobile_phones[i] = '\0';
			continue;
		}
		
	}
	if(x1+y1 == 0) rt1 = 0;
	else {rt1 = 100*x1/(x1+y1);
	if(rt1 == 66)
	rt1++;
	}
	rt2 = 100- rt1;
	if(x2+y2 == 0) rt3 = 0;
	else {rt3 = 100*x2/(x2+y2);
	if(rt3 == 66)
	rt3++;	
	}rt4 = 100 - rt3;

	

	cJSON *root = NULL;
	root = cJSON_CreateObject();
	cJSON *item = cJSON_CreateNumber(contacts_size);
	cJSON_AddItemToObject(root,"amount",item);
	

	cJSON *st = cJSON_CreateObject();
	item = cJSON_CreateNumber(x1+y1);
	cJSON_AddItemToObject(st,"amount",item);

	char str[100];
	sprintf(str,"%d%%",rt1);
	item = cJSON_CreateString(str);
	cJSON_AddItemToObject(st,"male_ratio",item);
	sprintf(str,"%d%%",rt2);
	item = cJSON_CreateString(str);
	cJSON_AddItemToObject(st,"female_ratio",item); //创建学生对象 
	
	cJSON *teacher = cJSON_CreateObject();
	item = cJSON_CreateNumber(x2+y2);
	cJSON_AddItemToObject(teacher,"amount",item);
	sprintf(str,"%d%%",rt3);
	item = cJSON_CreateString(str);
	cJSON_AddItemToObject(teacher,"male_ratio",item);
	sprintf(str,"%d%%",rt4);
	item = cJSON_CreateString(str);
	cJSON_AddItemToObject(teacher,"female_ratio",item);//创建老师对象 
	cJSON* starray_content=cJSON_CreateArray();
	cJSON* tearray_content=cJSON_CreateArray();
	
	for(i = 0;i<contacts_size;i++){
		cJSON *xtem = cJSON_CreateObject();
		cJSON* array = cJSON_CreateArray();
		item = cJSON_CreateString(contact_list[i].id);
		cJSON_AddItemToObject(xtem,"id",item);
		item = cJSON_CreateString(contact_list[i].name);
		cJSON_AddItemToObject(xtem,"name",item);
		item = cJSON_CreateNumber(contact_list[i].gender);
		cJSON_AddItemToObject(xtem,"gender",item);
		
		const char s[2] = ",";
		char *token = (char*)malloc(12*sizeof(char));
		token = strtok(contact_list[i].mobile_phones, s);
  		 while( token != NULL ) {
    		  item = cJSON_CreateString(token);
   			 cJSON_AddItemToArray(array,item);
   			   token = strtok(NULL, s);
  		 }
		

		cJSON_AddItemToObject(xtem,"mobile_phones",array);
		
		if(contact_list[i].type == 0)
			cJSON_AddItemToArray(starray_content,xtem);
		else
			cJSON_AddItemToArray(tearray_content,xtem);
			free(token);
	}
	 cJSON_AddItemToObject(st,"contacts",starray_content);
	cJSON_AddItemToObject(teacher,"contacts",tearray_content);
	cJSON_AddItemToObject(root,"student",st);
	cJSON_AddItemToObject(root,"teacher",teacher);
	char *out=cJSON_Print(root);
                printf("%s\n",out);

                cJSON_Delete(root);
                if(out!=NULL)
                {
                        free(out);
                }
	free(mobile_phones);
}

