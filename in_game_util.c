#include "in_game.h"

void set_game(int level, int chararcter, Barrier** barrier) {
    set_background(level);
    set_barrier(level, barrier);
    set_user_pos(level);
    set_user_char(chararcter);
    set_bubbles();
}

// 배경 이미지 로드
void set_background(int level) {

    switch (level) {
    case 1:
        background = load_bitmap(BACKGROUND_LV1, NULL);
        break;
    case 2:
        background = load_bitmap(BACKGROUND_LV2, NULL);
        break;

    case 3:
        background = load_bitmap(BACKGROUND_LV3, NULL);
        break;
    }
    if (!(background)) {
        allegro_message("Background image loading Error");
    }
}

void set_barrier(int level, Barrier** barrier) {
    int num_barriers = 0;
    int load_barrier = 0;
    int* position = NULL;

    switch (level) {
    case 1:
        num_barriers = NUM_BARRIERS_LV1;
        static const int temp_lv1[] = POSITIONS_LV1;
        position = (int*)malloc(num_barriers*sizeof(int));
        for (int i = 0; i < num_barriers; i++) {
            position[i] = temp_lv1[i];
        }

        break;

    case 2:
        num_barriers = NUM_BARRIERS_LV2;
        static const int temp_lv2[] = POSITIONS_LV2;
        position = (int*)malloc(num_barriers * sizeof(int));
        for (int i = 0; i < num_barriers; i++) {
            position[i] = temp_lv2[i];
        }
        break;

    case 3:
        num_barriers = NUM_BARRIERS_LV3;
        static const int temp_lv3[] = POSITIONS_LV3;
        position = (int*)malloc(num_barriers * sizeof(int));
        for (int i = 0; i < num_barriers; i++) {
            position[i] = temp_lv3[i];
        }
        break;

    default:
        allegro_message("Background image loading Error");
    }
    
    *barrier = (Barrier*)malloc(num_barriers * sizeof(Barrier));
    if (*barrier == NULL) {
        allegro_message("Memory allocation for barriers failed");
        return;
    }

    for (int i = 0; i < num_barriers; i++) {
        load_barrier = set_barrier_img(level, &(*barrier)[i]);

        if (load_barrier == -1) {
            allegro_message("Barrier image loading Error");
            for (int j = 0; j < i; j++) {
                destroy_bitmap((*barrier)[j].img);
            }
            free(*barrier);
            *barrier = NULL;
            return;
        }

        int row = (position[i] - 1) / 12; // 행 계산 (격자의 가로 크기 12)
        int col = (position[i] - 1) % 12; // 열 계산

        (*barrier)[i].x = col * OBJECT_WIDTH;
        (*barrier)[i].y = row * OBJECT_HEIGHT;
    }
    free(position);
}

// 캐릭터 초기 위치 설정
void set_user_pos(int level) {
    switch (level) {
    case 1:
        user.pos_x = USER_POSITION_X_LV1;
        user.pos_y = USER_POSITION_Y_LV1;
        break;
    case 2:
        user.pos_x = USER_POSITION_X_LV2;
        user.pos_y = USER_POSITION_Y_LV2;
        break;

    case 3:
        user.pos_x = USER_POSITION_X_LV3;
        user.pos_y = USER_POSITION_Y_LV3;
        break;
    }
}

// 캐릭터 이미지 로드
void set_user_char(int character) {
    user.hp = 10;
    user.speed = 1;
    user.water_bubble_cnt = 1;

    switch (character) {
    case 1:
        user.front = load_bitmap(USER_CHARACTER_FRONT_1, NULL);
        
        user.back = load_bitmap(USER_CHARACTER_BACK_1, NULL);

        user.left1 = load_bitmap(USER_CHARACTER_LEFT1_1, NULL);
        user.left2 = load_bitmap(USER_CHARACTER_LEFT2_1, NULL);

        user.right1 = load_bitmap(USER_CHARACTER_RIGHT1_1, NULL);
        user.right2 = load_bitmap(USER_CHARACTER_RIGHT2_1, NULL);
        break;

    case 2:
        user.front = load_bitmap(USER_CHARACTER_FRONT_1, NULL);

        user.back = load_bitmap(USER_CHARACTER_BACK_1, NULL);

        user.left1 = load_bitmap(USER_CHARACTER_LEFT1_1, NULL);
        user.left2 = load_bitmap(USER_CHARACTER_LEFT2_1, NULL);

        user.right1 = load_bitmap(USER_CHARACTER_RIGHT1_1, NULL);
        user.right2 = load_bitmap(USER_CHARACTER_RIGHT2_1, NULL);
        break;

    case 3:
        user.front = load_bitmap(USER_CHARACTER_FRONT_3, NULL);

        user.back = load_bitmap(USER_CHARACTER_BACK_3, NULL);

        user.left1 = load_bitmap(USER_CHARACTER_LEFT1_3, NULL);
        user.left2 = load_bitmap(USER_CHARACTER_LEFT2_3, NULL);

        user.right1 = load_bitmap(USER_CHARACTER_RIGHT1_3, NULL);
        user.right2 = load_bitmap(USER_CHARACTER_RIGHT2_3, NULL);
        break;
    }

    if(!user.back || !user.front || !user.left1 || !user.left2 || !user.right1 || !user.right2) {
        allegro_message("User images loading Error");
    }
}

int set_barrier_img(int level, Barrier* barrier) {

    switch (level) {
    case 1:
        barrier->img = load_bitmap(BARRIER_LV1, NULL);
        break;
    case 2:
        barrier->img = load_bitmap(BARRIER_LV2, NULL);
        break;

    case 3:
        barrier->img = load_bitmap(BARRIER_LV3, NULL);
        break;
    }

    // 이미지 로드
    
    if (!barrier->img) {
        return -1;
    }

    return 0;
}

void set_bubbles() {

    water_bubble = load_bitmap("./img/water_bubble.bmp", NULL);
    water_explode = load_bitmap("./img/water_explode.bmp", NULL);

    if (!water_bubble || !water_explode) {
        allegro_message("Bubble images loading Error");
    }
}

// 격자 그리기
void draw_line() {
    for (int i = 0; i <= MAX_x; i += 100) {
        line(buffer, i, 0, i, 750, makecol(255, 255, 255)); // 세로선
    }
    for (int i = 0; i <= MAX_y; i += 75) {
        line(buffer, 0, i, 1200, i, makecol(255, 255, 255)); // 가로선
    }
}

void control_character(int level, int frame_counter, int frame_delay) {
    int new_user_x = user.pos_x;
    int new_user_y = user.pos_y;

    // 이동 처리
    if (key[KEY_UP]) {
        new_user_y -= 2;
        if (new_user_y < 0) new_user_y = 0; // 위쪽 경계 체크
        current_image = user.back; // 위쪽 방향키
    }
    if (key[KEY_DOWN]) {
        new_user_y += 2;
        if (new_user_y > MAX_y - OBJECT_HEIGHT) new_user_y = MAX_y - OBJECT_HEIGHT; // 아래쪽 경계 체크
        current_image = user.front; // 아래쪽 방향키
    }
    if (key[KEY_LEFT]) {
        new_user_x -= 2;
        if (new_user_x < 0) new_user_x = 0; // 왼쪽 경계 체크
        if (frame_counter % frame_delay < frame_delay / 2) {
            current_image = user.left1;
        }
        else {
            current_image = user.left2;
        }
    }
    if (key[KEY_RIGHT]) {
        new_user_x += 2;
        if (new_user_x > MAX_x - OBJECT_WIDTH) new_user_x = MAX_x - OBJECT_WIDTH; // 오른쪽 경계 체크
        if (frame_counter % frame_delay < frame_delay / 2) {
            current_image = user.right1;
        }
        else {
            current_image = user.right2;
        }
    }
    // 충돌 검사
    if (!is_collision(level, new_user_x, new_user_y)) {
        user.pos_x = new_user_x;
        user.pos_y = new_user_y;
    }
}

void print_info(int remaining_time) {
    textprintf_ex(buffer, font, 1250, 330, makecol(255, 255, 255), -1, "HP: %d", user.hp);
    textprintf_ex(buffer, font, 1250, 360, makecol(255, 255, 255), -1, "Speed: %d", user.speed);
    textprintf_ex(buffer, font, 1250, 390, makecol(255, 255, 255), -1, "Max Bubble Count: %d", user.water_bubble_cnt);
    textprintf_ex(buffer, font, 1250, 420, makecol(255, 255, 255), -1, "Left Monsters: 1");
    textprintf_ex(buffer, font, 1250, 450, makecol(255, 255, 255), -1, "Time: %02d:%02d", remaining_time / 60, remaining_time % 60);
}

void destroy_map(int num_barriers) {
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
}


// 장애물과의 충돌 체크 함수
int is_collision(int level, int x, int y) {
    int num_barriers = (level == 1) ? NUM_BARRIERS_LV1 : (level == 2) ? NUM_BARRIERS_LV2 : NUM_BARRIERS_LV3;

    for (int i = 0; i < num_barriers; i++) {
        if (x < barrier[i].x + OBJECT_WIDTH && x + OBJECT_WIDTH > barrier[i].x &&
            y < barrier[i].y + OBJECT_HEIGHT && y + OBJECT_HEIGHT > barrier[i].y) {
            return 1; // 충돌 발생
        }
    }
    return 0; // 충돌 없음
}