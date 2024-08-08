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
        load_barrier = set_barrier_img(&(*barrier)[i]);

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
        user.front = load_bitmap(USER_CHARACTER_FRONT_2, NULL);

        user.back = load_bitmap(USER_CHARACTER_BACK_2, NULL);

        user.left1 = load_bitmap(USER_CHARACTER_LEFT1_2, NULL);
        user.left2 = load_bitmap(USER_CHARACTER_LEFT2_2, NULL);

        user.right1 = load_bitmap(USER_CHARACTER_RIGHT1_2, NULL);
        user.right2 = load_bitmap(USER_CHARACTER_RIGHT2_2, NULL);
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

int set_barrier_img(Barrier* barrier) {

    // 이미지 로드
    barrier->img = load_bitmap("./img/barrier.bmp", NULL);
    
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

void control_character(int frame_counter, int frame_delay) {
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
        frame_counter++;
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
        frame_counter++;
    }
    user.pos_x = new_user_x;
    user.pos_y = new_user_y;
}

int check_collision(int x1, int y1, int x2, int y2) {
    if (x1 + OBJECT_WIDTH > x2 && x1 < x2 + OBJECT_WIDTH && y1 + OBJECT_HEIGHT > y2 && y1 < y2 + OBJECT_HEIGHT) {
        return 1;
    }
    return 0;
}