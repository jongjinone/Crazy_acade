#define _CRT_SECURE_NO_WARNINGS

#include "user_data.h"

USER_DATA* head;

enum SUCCESS_FAIL {
	SUCCESS,
	FAIL
};

void init_user_data(void)
{
	head = NULL;
}

void printall_user_data(BITMAP* buffer)
{// 버퍼를 검정색으로 초기화
	clear_to_color(buffer, makecol(0, 0, 0));

	// ESC 키가 눌릴 때까지 루프
	while (!key[KEY_ESC]) {
		// 버퍼를 검정색으로 초기화
		clear_to_color(buffer, makecol(0, 0, 0));

		int cnt = 1;

		// 데이터가 비어있는 경우 처리
		if (head == NULL)
		{
			textout_ex(buffer, font, "ERROR: The List is Empty", 10, 10, makecol(255, 0, 0), -1);
			// 버퍼의 내용을 화면에 복사
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(1000); // 오류 메시지를 잠시 표시
			continue; // 루프를 계속
		}

		USER_DATA* ptr = head;
		int space = 0;

		// 리스트의 모든 데이터를 버퍼에 출력
		while (ptr)
		{
			textprintf_ex(buffer, font, 40, 10 + space, makecol(255, 255, 255), -1, "[%d]", cnt);
			textprintf_ex(buffer, font, 40, 20 + space, makecol(255, 255, 255), -1, "ID : %s", ptr->ID);
			textprintf_ex(buffer, font, 40, 30 + space, makecol(255, 255, 255), -1, "Password : %s", ptr->pwd);
			for (int i = 0; i < 5; i++) {
				textprintf_ex(buffer, font, 40, 40 + i*10 + space, makecol(255, 255, 255), -1, "%d record : %s  , %s", i+1,ptr->record[i].record_num, ptr->record[i].record_time);
			}

			ptr = ptr->next;
			cnt++;
			space += 100;
		}

		// 버퍼의 내용을 화면에 복사
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
}
	
	
int Search(char* ID, char* pwd,USER_DATA** target_user_p)
{
	int cnt = 0;
	USER_DATA* ptr = head;

	if (ptr == NULL)
	{
		return FAIL;
	}
	while (ptr)
	{
		if (!strcmp(ptr->ID, ID) && !strcmp(ptr->pwd,pwd))
		{
			cnt++;
			*target_user_p = ptr;
			break;
		}
		ptr = ptr->next;
	}
	if (cnt) return SUCCESS;

	return FAIL;
}
void readfile(void)
{
	init_user_data();
	int i = 0;
	FILE* fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		printf("File does not exist\n");
		return;
	}

	USER_DATA* ptr = head;
	while (1)
	{
		char temp[20];
		if (fgets(temp, sizeof(temp), fp) == NULL)
		{
			break;
		}
		else
		{
			temp[strlen(temp) - 1] = '\0';
			if (i % 14 == 0 || i % 14 == 13){
				i++;
			}
			else
			{
				USER_DATA* new_node = (USER_DATA*)malloc(sizeof(USER_DATA));
				new_node->next = NULL;
				strncpy(new_node->ID, temp, sizeof(new_node->ID));
				new_node->ID[strlen(new_node->ID)]='\0';

				fgets(new_node->pwd, sizeof(new_node->pwd), fp);
				new_node->pwd[strlen(new_node->pwd) - 1] = '\0';

				for (int j = 0; j < 5; j++) {
					fgets(new_node->record[j].record_num, sizeof(new_node->record[j].record_num), fp);
					new_node->record[j].record_num[strlen(new_node->record[j].record_num) - 1] = '\0';

					fgets(new_node->record[j].record_time, sizeof(new_node->record[j].record_time), fp);
					new_node->record[j].record_time[strlen(new_node->record[j].record_time) -1] = '\0';
				}

				if (ptr == NULL)
				{
					head = new_node;
					ptr = new_node;
				}
				else
				{
					new_node->next = ptr->next;
					ptr->next = new_node;
					ptr = ptr->next;
				}
				i += 12;
			}


		}
	}
	fflush(fp);
	fclose(fp);
}

int Insert(char *ID, char* pwd)
{
	USER_DATA* ptr = head;
	USER_DATA* new_node = (USER_DATA*)malloc(sizeof(USER_DATA));
	new_node->next = NULL;

	for (int i = 0; i < 5; i++) {
		strcpy(new_node->record[i].record_num," ");
		strcpy(new_node->record[i].record_time," ");
	}
	strcpy(new_node->ID, ID);
	strcpy(new_node->pwd, pwd);

	if (head == NULL)
	{
		head = new_node;
		return FAIL;
	}
	else
	{
		if (strcmp(head->ID, new_node->ID) > 0){
			new_node->next = head;
			head = new_node;
			return SUCCESS;
		}

		while (ptr){
			if (strcmp(ptr->ID, new_node->pwd) == 0)
			{
				return FAIL;
			}
			else if (ptr->next == NULL)
			{
				ptr->next = new_node;
				break;
			}
			else if (strcmp(ptr->ID, new_node->ID) < 0 && strcmp(ptr->next->ID, new_node->ID) > 0)
			{
				new_node->next = ptr->next;
				ptr->next = new_node;
				break;
			}
			ptr = ptr->next;
		}
		return SUCCESS;
	}
}

int Save(void)
{
	FILE* fp = fopen("test.txt", "wt"); //test파일을 w(쓰기) 모드로 열기
	USER_DATA* ptr = head;
	int cnt = 1;
	if (fp == NULL)
	{
		return FAIL;
	}
	while (ptr)
	{
	//		allegro_message("%d", cnt);
		fprintf(fp, "[%d]\n", cnt);
		fprintf(fp, "%s\n", ptr->ID);
		fprintf(fp, "%s\n", ptr->pwd);
		for (int i = 0; i < 5; i++) {
			fprintf(fp, "%s\n", ptr->record[i].record_num);
			fprintf(fp, "%s\n", ptr->record[i].record_time);
		}
		fprintf(fp, "\n");
		ptr = ptr->next;
		cnt++;
	}

	fflush(fp);
	fclose(fp); //파일 포인터 닫기
	return SUCCESS;
}

void freeall_user_data(void)
{
	USER_DATA* curr;
	USER_DATA* ptr;
	curr = head;
	if (head == NULL)
	{
		printf("The List is Empty\n");
		return;
	}
	else
	{
		while (curr)
		{
			ptr = curr->next;
			free(curr);
			curr = ptr;
		}
		init_user_data();
	}
}

void update_score(USER_DATA** target_user_p, int score) {
	USER_DATA* target = *target_user_p;
	// score를 문자열로 변환하여 a에 저장

	for (int i = 3; i >=0; i--) {
		strcpy(target->record[i + 1].record_num, target->record[i].record_num);
		strcpy(target->record[i + 1].record_time, target->record[i].record_time);
	}

	sprintf(target->record[0].record_num, "%d", score);

	time_t t = time(NULL); // 현재 시간을 가져옴
	struct tm* tm_info = localtime(&t); // 현재 시간을 지역 시간으로 변환

	// 날짜와 시간을 "YYYY-MM-DD HH:MM" 형식으로 a에 저장
	strftime(target->record[0].record_time, sizeof(target->record[0].record_time), "%Y-%m-%d %H:%M", tm_info);

}
