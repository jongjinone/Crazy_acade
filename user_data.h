#pragma once
#include "allegro.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void init_user_data(void);
void readfile(void);

void printall_user_data(BITMAP* buffer);
void freeall_user_data(void);
int Search(char* ID, char* pwd);
int Insert(char* ID, char* pwd);


// ����ü �̸��� USER_DATA�� �����Ͽ� typedef�� ��ġ��ŵ�ϴ�.

typedef struct record_data {
	char record_num[10];
	char record_time[20];
} RECORD_Stru;
typedef struct User_data
{
	char ID[20];
	char pwd[20];
	RECORD_Stru record[5];
	
	struct User_data* next; // ����ü �̸��� ��ġ�ϵ��� ����
} USER_DATA;


extern USER_DATA* head;

