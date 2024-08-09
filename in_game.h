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

#define USER_ZOMBIE_FRONT_1 "./img/character_zombie_front.bmp"
#define USER_ZOMBIE_BACK_1 "./img/character_zombie_back.bmp"
#define USER_ZOMBIE_RIGHT1_1 "./img/character_zombie_right1.bmp"
#define USER_ZOMBIE_RIGHT2_1 "./img/character_zombie_right2.bmp"
#define USER_ZOMBIE_LEFT1_1 "./img/character_zombie_left1.bmp"
#define USER_ZOMBIE_LEFT2_1 "./img/character_zombie_left2.bmp"

#define USER_ZOMBIE_FRONT_2 "./img/character_zombie_front.bmp"
#define USER_ZOMBIE_BACK_2 "./img/character_zombie_back.bmp"
#define USER_ZOMBIE_RIGHT1_2 "./img/character_zombie_right1.bmp"
#define USER_ZOMBIE_RIGHT2_2 "./img/character_zombie_right2.bmp"
#define USER_ZOMBIE_LEFT1_2 "./img/character_zombie_left1.bmp"
#define USER_ZOMBIE_LEFT2_2 "./img/character_zombie_left2.bmp"

#define USER_ZOMBIE_FRONT_3 "./img/character_zombie_front.bmp"
#define USER_ZOMBIE_BACK_3 "./img/character_zombie_back.bmp"
#define USER_ZOMBIE_RIGHT1_3 "./img/character_zombie_right1.bmp"
#define USER_ZOMBIE_RIGHT2_3 "./img/character_zombie_right2.bmp"
#define USER_ZOMBIE_LEFT1_3 "./img/character_zombie_left1.bmp"
#define USER_ZOMBIE_LEFT2_3 "./img/character_zombie_left2.bmp"

#define MOSTER_AMOUNT_LV1 3
#define MOSTER_AMOUNT_LV2 5
#define MOSTER_AMOUNT_LV3 7

#define USER_POSITION_X_LV1 0
#define USER_POSITION_Y_LV1 75

#define USER_POSITION_X_LV2 1
#define USER_POSITION_Y_LV2 150

#define USER_POSITION_X_LV3 2
#define USER_POSITION_Y_LV3 225

#define NUM_BARRIERS_LV1 0
#define NUM_BARRIERS_LV2 8
#define NUM_BARRIERS_LV3 10

#define USER_ATTACK 3

#define OBJECT_WIDTH 100 // ��ü�� ���� ũ��
#define OBJECT_HEIGHT 75 // ��ü�� ���� ũ��

// barrier�� ��ġ 
#define POSITIONS_LV1 { 0 }
#define POSITIONS_LV2 { 14, 23, 54, 55, 66, 67, 98, 107 }
#define POSITIONS_LV3 { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 }

// zombie �ʱ� HP
#define ZOMBIE_HP_LV1 3
#define ZOMBIE_HP_LV2 5
#define ZOMBIE_HP_LV3 10

// zombie �ʱ� Speed
#define ZOMBIE_SPEED_LV1 1
#define ZOMBIE_SPEED_LV2 2
#define ZOMBIE_SPEED_LV3 3

// zombie �ʱ� ��ġ
#define ZOMBIE_POS_LV1 { 15, 55, 91 }
#define ZOMBIE_POS_LV2 { 23, 67, 89, 42, 110 }
#define ZOMBIE_POS_LV3 { 12, 78, 56, 33, 102, 5, 90 }

// user ����ü
typedef struct {
    BITMAP* front;
    BITMAP* back;
    BITMAP* left1;
    BITMAP* left2;

    BITMAP* right1;
    BITMAP* right2;

    int pos_x; 
    int pos_y;
    int hp;       // ĳ������ hp
    int speed;     // ĳ������ speed
    int water_bubble_cnt;     // ĳ������ ��ǳ�� ����
} User;

typedef struct {
    BITMAP* front;
    BITMAP* back;
    BITMAP* left1;
    BITMAP* left2;

    BITMAP* right1;
    BITMAP* right2;
    BITMAP* current_zombie_image;
    
    int pos_x;
    int pos_y;
    int hp;       // ������ hp
    int speed;     // ������ speed
    int active;
    int attack;

} Zombie;

// barrier ����ü
typedef struct {
    BITMAP* img;
    int x;       // ��ֹ��� x��ǥ
    int y;     // ��ֹ��� y��ǥ
} Barrier;

Barrier* barrier;
User user;

Zombie zombies[10];

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
void set_zombie_pos(int level);

// ���� �̹��� �޾ƿ���
void set_zombie_char(Zombie* zombie, int character);
void set_bubbles();
int set_barrier_img(int level, Barrier* barrier);
void move_zombies(int level, int* direction, int frame_counter, int frame_delay);

void draw_line();

void control_character(int level, int frame_counter, int frame_delay);
void print_info(int remaining_time);
void destroy_map(int num_barriers);

int is_collision(int level, int x, int y);