#pragma once
#include <allegro.h>
#include "param.h"
#include "music.h"

void initialize_window(void);
void draw_rec_login(BITMAP* buffer);
void print_text_login(BITMAP* buffer);
int login_menu(BITMAP* buffer);
int main_intro(BITMAP* buffer);
