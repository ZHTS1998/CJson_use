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
	 char *json_string = (char*)malloc(2000*sizeof(char));
	char ch;
	int i =0;
	char *m = (char*)malloc(sizeof(char));
	strcpy(m, ",");
	while((ch=getchar())!='\n'){
		json_string[i] = ch;
		i++;
		json_string[i] = '\0';
	}
	cJSON* cjson = cJSON_Parse(json_string); 
	
	int amount = cJSON_GetObjectItem(cjson,"amount")->valueint;
	Contacts contact_list[amount];
	cJSON *student = cJSON_GetObjectItem(cjson,"student");
	cJSON *contact1= cJSON_GetObjectItem(student,"contacts");
	int size = cJSON_GetArraySize(contact1);
	cJSON* contact = contact1->child;
	
	
	
	for(i = 0;i<size;i++){
		contact_list[i].type = 0;	
		char *id = cJSON_GetObjectItem(contact,"id")->valuestring;	
		strcpy(contact_list[i].id,id);
		char* name=cJSON_GetObjectItem(contact,"name")->valuestring;
		strcpy(contact_list[i].name,name);
		int gender=cJSON_GetObjectItem(contact,"gender")->valueint;
		contact_list[i].gender=gender;
		int j = 0;
		char *ph = (char*)malloc(30*sizeof(char));	
		cJSON *phones=cJSON_GetObjectItem(contact,"mobile_phones");
		int c = cJSON_GetArraySize(phones);
		
		for(j = 0;j<c;j++){
			char *p= (char*)malloc(15*sizeof(char));
			p=cJSON_GetArrayItem(phones,j)->valuestring;
			if(j == 1) {
			strcat(ph,m);
			strcat(ph,p);
			}
			if(j == 0)  strcpy(ph,p);
			free(p);
		}
		ph[strlen(ph)] = '\0';
		
		contact_list[i].mobile_phones = (char*)malloc(24*sizeof(char));
		strcpy(contact_list[i].mobile_phones,ph);
		contact = contact->next; 
		free(ph);		
		
	}
  	cJSON* s= cJSON_GetObjectItem(cjson,"teacher");
	cJSON* test_arr = cJSON_GetObjectItem(s,"contacts");
	
	cJSON *contact3 = test_arr->child;
	
	for(i = size;i<amount;i++){
		contact_list[i].type = 1;
		char *id=cJSON_GetObjectItem(contact3,"id")->valuestring;
		strcpy(contact_list[i].id,id);
		char *name=cJSON_GetObjectItem(contact3,"name")->valuestring;
		strcpy(contact_list[i].name,name);
		int gender=cJSON_GetObjectItem(contact3,"gender")->valueint;
		contact_list[i].gender=gender;
		int j = 0;
	
		char *ph = (char*)malloc(30*sizeof(char));
		cJSON *phones=cJSON_GetObjectItem(contact3,"mobile_phones");
		int x = cJSON_GetArraySize(phones);
		for(j = 0;j<x;j++){
			char *p= (char*)malloc(15*sizeof(char));
			p=cJSON_GetArrayItem(phones,j)->valuestring;
			if(j == 1) {
			strcat(ph,m);
			strcat(ph,p);
			}
			if(j == 0)  strcpy(ph,p);
			free(p);
		}
		
		ph[strlen(ph)] = '\0';
	 	
		contact_list[i].mobile_phones = (char*)malloc(24*sizeof(char));
		strcpy(contact_list[i].mobile_phones,ph);
		contact3 = contact3->next; 
		free(ph);
		
		 
		
	}
	for(i = 0;i<amount;i++){
		printf("%s %d %s %d %s\n",contact_list[i].id,contact_list[i].type,contact_list[i].name,contact_list[i].gender,contact_list[i].mobile_phones);
		
}
	free(m);
	free(json_string);
}


 

