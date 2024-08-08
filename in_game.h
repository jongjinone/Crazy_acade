#pragma once

#include <allegro.h>

#define WHOLE_x 1500
#define WHOLE_y 750

#define MAX_x 1200
#define MAX_y 750

#define BACKGROUND_LV1 "./img/background1.bmp"
#define BACKGROUND_LV2 "./img/background2.bmp"
#define BACKGROUND_LV3 "./img/background3.bmp"

#define BARRIER_LV1 "./img/barrier1.bmp"
#define BARRIER_LV2 "./img/barrier2.bmp"
#define BARRIER_LV3 "./img/barrier3.bmp"

#define USER_CHARACTER_FRONT_1 "./img/1_front.bmp"
#define USER_CHARACTER_BACK_1 "./img/1_back.bmp"
#define USER_CHARACTER_RIGHT1_1 "./img/1_right1.bmp"
#define USER_CHARACTER_RIGHT2_1 "./img/1_right2.bmp"
#define USER_CHARACTER_LEFT1_1 "./img/1_left1.bmp"
#define USER_CHARACTER_LEFT2_1 "./img/1_left2.bmp"

#define USER_CHARACTER_FRONT_2 "./img/2_front.bmp"
#define USER_CHARACTER_BACK_2 "./img/2_back.bmp"
#define USER_CHARACTER_RIGHT1_2 "./img/2_right1.bmp"
#define USER_CHARACTER_RIGHT2_2 "./img/2_right2.bmp"
#define USER_CHARACTER_LEFT1_2 "./img/2_left1.bmp"
#define USER_CHARACTER_LEFT2_2 "./img/2_left2.bmp"

#define USER_CHARACTER_FRONT_3 "./img/3_front.bmp"
#define USER_CHARACTER_BACK_3 "./img/3_back.bmp"
#define USER_CHARACTER_RIGHT1_3 "./img/3_right1.bmp"
#define USER_CHARACTER_RIGHT2_3 "./img/3_right2.bmp"
#define USER_CHARACTER_LEFT1_3 "./img/3_left1.bmp"
#define USER_CHARACTER_LEFT2_3 "./img/3_left2.bmp"

#define USER_POSITION_X_LV1 0
#define USER_POSITION_Y_LV1 75

#define USER_POSITION_X_LV2 1
#define USER_POSITION_Y_LV2 150

#define USER_POSITION_X_LV3 2
#define USER_POSITION_Y_LV3 225

#define NUM_BARRIERS_LV1 0
#define NUM_BARRIERS_LV2 8
#define NUM_BARRIERS_LV3 10

#define OBJECT_WIDTH 100 // 객체의 가로 크기
#define OBJECT_HEIGHT 75 // 객체의 세로 크기

// barrier의 위치 
#define POSITIONS_LV1 { 0 }
#define POSITIONS_LV2 { 14, 23, 54, 55, 66, 67, 98, 107 }
#define POSITIONS_LV3 { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 }

// user 구조체
typedef struct {
    BITMAP* front;
    BITMAP* back;
    BITMAP* left1;
    BITMAP* left2;

    BITMAP* right1;
    BITMAP* right2;

    int pos_x; 
    int pos_y;
    int hp;       // 캐릭터의 hp
    int speed;     // 캐릭터의 speed
    int water_bubble_cnt;     // 캐릭터의 물풍선 개수
} User;

// barrier 구조체
typedef struct {
    BITMAP* img;
    int x;       // 장애물의 x좌표
    int y;     // 장애물의 y좌표
} Barrier;

Barrier* barrier;
User user;

BITMAP* background;
BITMAP* water_bubble;
BITMAP* water_explode;
BITMAP* buffer;
BITMAP* current_image;

void set_game(int level, int character, Barrier** barrier);

void set_background(int level);
void set_barrier(int level, Barrier** barrier);
void set_user_pos(int level);
void set_user_char(int character);
void set_bubbles();
int set_barrier_img(int level, Barrier* barrier);

void draw_line();

void control_character(int level, int frame_counter, int frame_delay);
void print_info(int remaining_time);
void destroy_map(int num_barriers);

int is_collision(int level, int x, int y);