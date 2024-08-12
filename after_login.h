#pragma once
#include "allegro.h"
#include "param.h"
#include "music.h"
#include "user_data.h"

void AF_draw_rec_login(BITMAP* buffer);
void AF_print_text_login(BITMAP* buffer);
int AF_login_menu(BITMAP* buffer);
void AF_back_icon(BITMAP* buffer);
int AF_check_back(BITMAP* buffer);
int main_AF_login(BITMAP* buffer);
