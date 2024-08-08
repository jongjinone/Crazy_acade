#pragma once
#include <time.h>
#include "in_game.h"

#define MAX_BUBBLES 1000

// 물풍선 구조체
typedef struct {
    int x, y;       // 위치
    int dx, dy;     // 이동 방향
    int active;     // 활성화 여부
    time_t create_time;
} WaterBubble;

typedef struct {
    int x, y; // 물풍선이 설치된 위치
    int size; // 물풍선이 터지는 사이즈
    int active; // 활성화 여부
    time_t explode_time;
} WaterExplode;

void initializeBubbles();
void setBubble(int x, int y);
void explodeBubbles(BITMAP* buffer, int size, BITMAP* background);

// 물풍선 객체들
WaterBubble bubbles[MAX_BUBBLES];
int bubble_count;

// 물풍선 폭발 객체
WaterExplode explodes[MAX_BUBBLES];
int explode_count; 
