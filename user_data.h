#pragma once
#include "allegro.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct record_data {
	char record_num[10];
	char record_time[20];
} RECORD_Stru;
typedef struct User_data
{
	char ID[20];
	char pwd[20];
	RECORD_Stru record[5];
	
	struct User_data* next; // 구조체 이름과 일치하도록 수정
} USER_DATA;

void init_user_data(void);
void readfile(void);

void printall_user_data(BITMAP* buffer);
void freeall_user_data(void);
int Search(char* ID, char* pwd, USER_DATA** target_user);
int Insert(char* ID, char* pwd);

extern USER_DATA* head;

