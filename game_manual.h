#pragma once

#include "allegro.h"
#include "user_data.h"
#include "param.h"
#include "login.h"

int game_manual(BITMAP* buffer);
void print_user_record(BITMAP* buffer, USER_DATA* target_user);
