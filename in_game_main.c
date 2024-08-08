#include "in_game_main.h"

volatile int ticks = 0;

void ticker() {
    ticks++;
}

END_OF_FUNCTION(ticker)

int game_start(int level, int character)
{
    int frame_counter = 0; // 애니메이션 프레임 조정 변수
    int frame_delay = 30; // 애니메이션 프레임 간의 딜레이 설정
    int elapsed_time;
    int remaining_time;

    int num_barriers = (level == 1) ? NUM_BARRIERS_LV1 : (level == 2) ? NUM_BARRIERS_LV2 : NUM_BARRIERS_LV3;

    set_game(level, character, &barrier);
    initializeBubbles();

    LOCK_FUNCTION(ticker);
    LOCK_VARIABLE(ticks);
    install_int_ex(ticker, BPS_TO_TIMER(60)); // 60 ticks per second

    // 백 버퍼
    buffer = create_bitmap(WHOLE_x, WHOLE_y);

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

            draw_line();

            draw_sprite(buffer, current_image, user.pos_x, user.pos_y); // 백 버퍼에 캐릭터 이미지 그리기

            // 장애물 그리기
            for (int i = 0; i < num_barriers; i++) {
                draw_sprite(buffer, barrier[i].img, barrier[i].x, barrier[i].y);
            }

            // 화면 상단에 정보 출력
            time_t current_time = time(NULL);
            elapsed_time = (int)difftime(current_time, t);
            remaining_time = 180 - elapsed_time;

            if (remaining_time <= 0 || user.hp==0) { // 남은 시간이 0 이하일 경우 게임 종료
                remaining_time = 0;
                break; // 게임 루프를 종료합니다.
            }
            print_info(remaining_time);

            // 백 버퍼의 내용을 화면에 그리기
            blit(buffer, screen, 0, 0, 0, 0, WHOLE_x, WHOLE_y);

            ticks--;
            if (ticks != old_ticks) break;

            // 프레임 카운터 증가
            frame_counter++;
        }
        if (remaining_time == 0 || user.hp == 0) {
            break;
        }
    }

    destroy_map(num_barriers);

    return 0;
}
