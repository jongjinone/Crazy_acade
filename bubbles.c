#include "bubbles.h"
#include "in_game.h"
#include <allegro.h>
#include "music.h"

// x, y ��ǥ ��ĭ�� ũ��
#define x_size 100
#define y_size 75

int bubble_count = 0;
int explode_count = 0;

void initializeBubbles() {
    for (int i = 0; i < MAX_BUBBLES; i++) {
        bubbles[i].active = 0;
        explodes[i].active = 0;
    }
}

void setBubble(int x, int y) {
    if (bubble_count < MAX_BUBBLES) {
        WaterBubble* bubble = &bubbles[bubble_count++];
        // ĳ������ ��ġ�� ���� �����Ǵ� ��ǳ���� ��ġ�� ������

        bubble->x = ((x + x_size / 2 ) / x_size) * x_size;
        bubble->y = ((y + y_size / 2) / y_size) * y_size;

        bubble->active = 1;

        bubble->create_time = time(NULL);
      //  rest(10); // �߻� ���� ����
    }
}

void explodeBubbles(BITMAP* buffer, int size, BITMAP* background,SAMPLE* sample) {
    for (int i = 0; i < bubble_count; i++) {
        WaterBubble* bubble = &bubbles[i];
        if (bubble->active) {
            if (difftime(time(NULL), bubble->create_time) > 2) {
                // 2�� �� ��ǳ�� ������� ���� ��ü Ȱ��ȭ
                sample = action_music(m_pop_balloon);
                bubble->active = 0;
                WaterExplode* explode = &explodes[explode_count++];
                explode->x = bubble->x;
                explode->y = bubble->y;
                explode->size = size; // ���� ũ�� ����
                explode->active = 1;
                explode->explode_time = time(NULL);
            }
        }
    }

    // �� ���۸� ����� �ٽ� �׸���
    clear_to_color(buffer, makecol(0, 0, 0)); // �� ���۸� ���������� ����
    draw_sprite(buffer, background, 0, 0);

    // ���� Ȱ��ȭ
    for (int i = 0; i < explode_count; i++) {
        WaterExplode* explode = &explodes[i];
        if (explode->active) {
            draw_sprite(buffer, water_explode, explode->x, explode->y);
            for (int k = 1; k <= explode->size; k++) {
                int explode_x_size = k * x_size;
                int explode_y_size = k * y_size;

                int plus_x = (explode->x + explode_x_size <MAX_x) ? (explode->x + explode_x_size) : MAX_x-100;

                draw_sprite(buffer, water_explode, explode->x - explode_x_size, explode->y);
                draw_sprite(buffer, water_explode, plus_x, explode->y); //MAX_x
                draw_sprite(buffer, water_explode, explode->x, explode->y - explode_y_size);
                draw_sprite(buffer, water_explode, explode->x, explode->y + explode_y_size);
            }

            // ���� �ִϸ��̼� ���� �ð�
            if (difftime(time(NULL), explode->explode_time) > 0.7) {
                explode->active = 0;
            }
        }
    }

    // Ȱ��ȭ�� ��ǳ�� �׸���
    for (int i = 0; i < bubble_count; i++) {
        if (bubbles[i].active) {
            draw_sprite(buffer, water_bubble, bubbles[i].x, bubbles[i].y);
        }
    }
}