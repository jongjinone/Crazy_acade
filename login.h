#pragma once
#include <string.h>
#include <stdlib.h>

#include "user_data.h"
#include "allegro.h"
#include "param.h"
#include "music.h"
int Enter_ID(BITMAP* buffer, char* input_ID, int text_length);
int Enter_PWD(BITMAP* buffer, char* input_ID, char* input_PWD, int text_length);
void back_icon(BITMAP* buffer);
void ID_PWD_icon(BITMAP* buffer);
int check_back(BITMAP* buffer);
int main_login(BITMAP* buffer, USER_DATA** target_user_p);
