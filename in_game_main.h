#pragma once

#include "in_game.h"
#include "bubbles.h"
#include "user_data.h"
int game_start(int level, int character,int* score);
void game_over(BITMAP* buffer, int score);