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

#define USER_CHARACTER_FRONT_1 "./img/1_front.bmp"
#define USER_CHARACTER_FRONT_ATTACKED_1 "./img/1_front_attacked.bmp"
#define USER_CHARACTER_BACK_1 "./img/1_back.bmp"
#define USER_CHARACTER_BACK_ATTACKED_1 "./img/1_back_attacked.bmp"
#define USER_CHARACTER_RIGHT1_1 "./img/1_right1.bmp"
#define USER_CHARACTER_RIGHT1_ATTACKED_1 "./img/1_right1_attacked.bmp"
#define USER_CHARACTER_RIGHT2_1 "./img/1_right2.bmp"
#define USER_CHARACTER_RIGHT2_ATTACKED_1 "./img/1_right2_attacked.bmp"
#define USER_CHARACTER_LEFT1_1 "./img/1_left1.bmp"
#define USER_CHARACTER_LEFT1_ATTACKED_1 "./img/1_left1_attacked.bmp"
#define USER_CHARACTER_LEFT2_1 "./img/1_left2.bmp"
#define USER_CHARACTER_LEFT2_ATTACKED_1 "./img/1_left2_attacked.bmp"

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
#define NUM_BARRIERS_LV3 22

#define USER_ATTACK 3 
#define USER_HP 200

#define OBJECT_WIDTH 100 // 객체의 가로 크기
#define OBJECT_HEIGHT 75 // 객체의 세로 크기

// barrier의 위치 
#define POSITIONS_LV1 { 0 }
#define POSITIONS_LV2 { 14, 23, 54, 55, 66, 67, 98, 107 }
#define POSITIONS_LV3 { 16, 17, 18, 19, 20, 21, 22, 38, 47, 50, 59, 62, 71, 74, 83, 100, 101, 102, 103, 104, 105, 106 }

// zombie 초기 HP
#define ZOMBIE_HP_LV1 3
#define ZOMBIE_HP_LV2 5
#define ZOMBIE_HP_LV3 10

// zombie 초기 Speed
#define ZOMBIE_SPEED_LV1 1
#define ZOMBIE_SPEED_LV2 2
#define ZOMBIE_SPEED_LV3 3

//zombie 초기 attack
#define ZOMBIE_ATTACK_LV1 1
#define ZOMBIE_ATTACK_LV2 2
#define ZOMBIE_ATTACK_LV3 3

// zombie 초기 위치
#define ZOMBIE_POS_LV1 { 15, 55, 91 }
#define ZOMBIE_POS_LV2 { 27, 68, 89, 42, 110 }
#define ZOMBIE_POS_LV3 { 5, 23, 33, 56, 78, 90, 119 }

// user 구조체
typedef struct {
    BITMAP* front;
    BITMAP* front_attacked;
    BITMAP* back;
    BITMAP* back_attacked;
    BITMAP* left1;
    BITMAP* left1_attacked;
    BITMAP* left2;
    BITMAP* left2_attacked;
    BITMAP* right1;
    BITMAP* right1_attacked;
    BITMAP* right2;
    BITMAP* right2_attacked;

    int pos_x; 
    int pos_y;
    int hp;       // 캐릭터의 hp
    int speed;     // 캐릭터의 speed
    int water_bubble_cnt;     // 캐릭터의 물풍선 개수
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
    int hp;       // 몬스터의 hp
    int speed;     // 몬스터의 speed
    int active;
    int attack;

} Zombie;

// barrier 구조체
typedef struct {
    BITMAP* img;
    int x;       // 장애물의 x좌표
    int y;     // 장애물의 y좌표
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

// 좀비 이미지 받아오기
void set_zombie_char(Zombie* zombie, int character);
void set_bubbles();
int set_barrier_img(int level, Barrier* barrier);
void move_zombies(int level, int* direction, int frame_counter, int frame_delay);

void draw_line();

void control_character(int level, int frame_counter, int frame_delay);
void print_info(int remaining_time, int* score);
void destroy_map(int num_barriers);

int is_collision(int level, int x, int y);
int count_zombie();

// 점수 계산
void calScore(int level, int remaining_time, int* score);