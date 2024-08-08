#pragma once
#include <time.h>
#include "in_game.h"

#define MAX_BUBBLES 1000

// ��ǳ�� ����ü
typedef struct {
    int x, y;       // ��ġ
    int dx, dy;     // �̵� ����
    int active;     // Ȱ��ȭ ����
    time_t create_time;
} WaterBubble;

typedef struct {
    int x, y; // ��ǳ���� ��ġ�� ��ġ
    int size; // ��ǳ���� ������ ������
    int active; // Ȱ��ȭ ����
    time_t explode_time;
} WaterExplode;

void initializeBubbles();
void setBubble(int x, int y);
void explodeBubbles(BITMAP* buffer, int size, BITMAP* background);

// ��ǳ�� ��ü��
WaterBubble bubbles[MAX_BUBBLES];
int bubble_count;

// ��ǳ�� ���� ��ü
WaterExplode explodes[MAX_BUBBLES];
int explode_count; 
