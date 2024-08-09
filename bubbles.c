#include "bubbles.h"
#include "in_game.h"
#include <allegro.h>
#include "music.h"
#include <time.h>

// x, y 좌표 한칸의 크기
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
        // 캐릭터의 위치에 따라 생성되는 물풍선의 위치가 정해짐

        bubble->x = ((x + x_size / 2 ) / x_size) * x_size;
        bubble->y = ((y + y_size / 2) / y_size) * y_size;

        bubble->active = 1;

        bubble->create_time = clock();
      //  rest(10); // 발사 간격 조절
    }
}

int explodeBubbles(BITMAP* buffer, int size, BITMAP* background, SAMPLE* sample) {
    double current_time = clock();
    for (int i = 0; i < bubble_count; i++) {
        WaterBubble* bubble = &bubbles[i];
        if (bubble->active) {
            double bubble_time_diff = (double)(current_time - bubble->create_time) / CLOCKS_PER_SEC;
            if (bubble_time_diff > 2) {
                // 2초 후 물풍선 사라지고 폭발 객체 활성화
                sample = action_music(m_pop_balloon);
                bubble->active = 0;
                WaterExplode* explode = &explodes[explode_count++];
                explode->x = bubble->x;
                explode->y = bubble->y;
                explode->size = size; // 폭발 크기 설정
                explode->active = 1;
                explode->explode_time = clock();
            }
        }
    }

    // 백 버퍼를 지우고 다시 그리기
    clear_to_color(buffer, makecol(0, 0, 0)); // 백 버퍼를 검은색으로 지움
    draw_sprite(buffer, background, 0, 0);

    // 폭발 활성화
    for (int i = 0; i < explode_count; i++) {
        WaterExplode* explode = &explodes[i];
        if (explode->active) {
            draw_sprite(buffer, water_explode, explode->x, explode->y);
            for (int k = 1; k <= explode->size; k++) {
                int explode_x_size = k * x_size;
                int explode_y_size = k * y_size;

                draw_sprite(buffer, water_explode, explode->x - explode_x_size, explode->y);
                draw_sprite(buffer, water_explode, (explode->x + explode_x_size < MAX_x) ? (explode->x + explode_x_size) : MAX_x - 100, explode->y);
                draw_sprite(buffer, water_explode, explode->x, explode->y - explode_y_size);
                draw_sprite(buffer, water_explode, explode->x, explode->y + explode_y_size);

            }
            // 폭발 애니메이션 지속 시간
            double explode_time_diff = (double)(current_time - explode->explode_time) / CLOCKS_PER_SEC;
            if (explode_time_diff > 0.8) {
                explode->active = 0;
            }
        }
        int condition1;
        int condition2;

        for (int j = 0; j < 10; j++) {
            if (explode->active) {
                condition1 = explode->x - size * x_size < zombies[j].pos_x + 50 && zombies[j].pos_x + 50 < explode->x + (size + 1) * x_size &&
                    explode->y < zombies[j].pos_y + 37 && zombies[j].pos_y + 37 < explode->y + y_size;

                condition2 = explode->y - size * y_size < zombies[j].pos_y + 37 && zombies[j].pos_y + 37 < explode->y + (size + 1) * y_size &&
                    explode->x < zombies[j].pos_x + 50 && zombies[j].pos_x + 50 < explode->x + x_size;

                if (condition1 || condition2) {
                    zombies[j].hp -= USER_ATTACK;
                    if (zombies[j].hp <= 0) {
                        zombies[j].hp = 0;
                        zombies[j].active = 0;
                        int stage_finish_flag = 1;
                        for (int k = 0; k < 10; k++) {
                            if (zombies[k].active == 1) stage_finish_flag = 0;
                        }
                        if (stage_finish_flag) {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    // 활성화된 물풍선 그리기
    for (int i = 0; i < bubble_count; i++) {
        if (bubbles[i].active) {
            draw_sprite(buffer, water_bubble, bubbles[i].x, bubbles[i].y);
        }
    }
    return 0;
}