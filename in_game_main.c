#include "in_game_main.h"

volatile int ticks = 0;

void ticker() {
    ticks++;
}

END_OF_FUNCTION(ticker)

int game_start(int level, int character)
{
    int frame_counter = 0; // 애니메이션 프레임 조정 변수
    int frame_delay = 30; // 애니메이션 프레임 간의 딜레이 설정\
    // test 주석

    int num_barriers = (level == 1) ? NUM_BARRIERS_LV1 : (level == 2) ? NUM_BARRIERS_LV2 : NUM_BARRIERS_LV3;

    set_game(level, character, &barrier);
    initializeBubbles();

    LOCK_FUNCTION(ticker);
    LOCK_VARIABLE(ticks);
    install_int_ex(ticker, BPS_TO_TIMER(60)); // 60 ticks per second

    // 백 버퍼
    buffer = create_bitmap(MAX_x, MAX_y);

    // 캐릭터 초기 이미지
    current_image = user.front;

    time_t t;
    t = time(NULL);

    // 게임 루프
    while (!key[KEY_ESC]) {
        while (ticks == 0) rest(1);
        while (ticks > 0) {
            int old_ticks = ticks;

            control_character(level, frame_counter, frame_delay);

            // 스페이스바를 눌렀을 때 위치와 생성 시간 기록
            if (key[KEY_SPACE]) {
                setBubble(user.pos_x, user.pos_y);
            }
            draw_sprite(buffer, background, 0, 0);

            // 물풍선 터트리기 (buffer, size 넘겨줘야함)
            explodeBubbles(buffer, 3, background);

            // 격자 그리기
            for (int i = 0; i <= MAX_x; i += 100) {
                line(buffer, i, 0, i, 750, makecol(255, 255, 255)); // 세로선
            }
            for (int i = 0; i <= MAX_y; i += 75) {
                line(buffer, 0, i, 1200, i, makecol(255, 255, 255)); // 가로선
            }

            draw_sprite(buffer, current_image, user.pos_x, user.pos_y); // 백 버퍼에 캐릭터 이미지 그리기

            // 장애물 그리기
            for (int i = 0; i < num_barriers; i++) {
                draw_sprite(buffer, barrier[i].img, barrier[i].x, barrier[i].y);
            }

            // 백 버퍼의 내용을 화면에 그리기
            blit(buffer, screen, 0, 0, 0, 0, MAX_x, MAX_y);

            ticks--;
            if (ticks != old_ticks) break;

            // 프레임 카운터 증가
            frame_counter++;
        }
    }

    destroy_bitmap(buffer);
    destroy_bitmap(user.back);
    destroy_bitmap(user.front);
    destroy_bitmap(user.left1);
    destroy_bitmap(user.left2);
    destroy_bitmap(user.right1);
    destroy_bitmap(user.right2);
    destroy_bitmap(background);
    destroy_bitmap(water_bubble);
    destroy_bitmap(water_explode);

    // 장애물 이미지 해제
    for (int i = 0; i < num_barriers; i++) {
        destroy_bitmap(barrier[i].img);
    }
    free(barrier);

    return 0;
}
