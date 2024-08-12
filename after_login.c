#include "after_login.h"
#if 01
enum AF_login {
    BACK,
    GAMESTART,
    GAME_MANUAL,
    RECORD,
    EXIT
};
void AF_draw_rec_login(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;

    rect(buffer, center_x - rect_width, center_y -4* rect_height, center_x + rect_width, center_y -2*rect_height, makecol(255, 0, 0)); // ¿ÞÂÊ À§
    rect(buffer, center_x - rect_width, center_y + rect_height, center_x + rect_width, center_y - rect_height, makecol(255, 0, 0)); // ¿ÞÂÊ À§
    rect(buffer, center_x - rect_width, center_y + 4 * rect_height, center_x + rect_width, center_y + 2 * rect_height, makecol(255, 0, 0));
    rect(buffer, center_x - rect_width, center_y + 7 * rect_height, center_x + rect_width, center_y + 5 * rect_height, makecol(255, 0, 0));

}
void AF_print_text_login(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;

    textout_centre_ex(buffer, font, "Game Start", center_x, center_y-3*rect_height, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "Game Manual", center_x, center_y, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "Record ", center_x, center_y + 3 * rect_height, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "EXIT", center_x, center_y + 6 * rect_height, makecol(255, 255, 255), -1);
}
int AF_login_menu(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;

    if (!AF_check_back(buffer)) return BACK;

    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y - 4* rect_height) && mouse_y < (center_y -2* rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y -4* rect_height, center_x + rect_width, center_y -2* rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            return GAMESTART;
        }
    }
    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y - rect_height) && mouse_y < (center_y + rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y + rect_height, center_x + rect_width, center_y - rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            return GAME_MANUAL;
        }
    }
    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y + 2 * rect_height) && mouse_y < (center_y + 4 * rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y + 2 * rect_height, center_x + rect_width, center_y + 4 * rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            return RECORD;
        }
    }
    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y + 5 * rect_height) && mouse_y < (center_y + 7 * rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y + 5 * rect_height, center_x + rect_width, center_y + 7 * rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            destroy_bitmap(buffer);
            return EXIT;
        }
    }
    AF_back_icon(buffer);
    AF_draw_rec_login(buffer);
    AF_print_text_login(buffer);
    return -1;
}

void AF_back_icon(BITMAP* buffer) {
    rectfill(buffer, 0, 0, 60, 40, makecol(255, 0, 0));
    textout_centre_ex(buffer, font, "Back ", 35, 20, makecol(255, 255, 255), -1);
}
int AF_check_back(BITMAP* buffer) {
    if (mouse_b & 1 && mouse_x > 0 && mouse_x < 60 && mouse_y > 0 && mouse_y < 40) {
        clear_to_color(buffer, makecol(0, 0, 0));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        return BACK;
    }
    return -1;
}
int main_AF_login(BITMAP* buffer) {
    SAMPLE* sample = play_music(m_after_login_bgm);
    while (1) {
        clear_to_color(buffer, makecol(0, 0, 0));
        int case_num;
        case_num = AF_login_menu(buffer);
        if (case_num == BACK) {
            off_music(sample);
            return BACK;
        }
        if (case_num == GAMESTART) {
            off_music(sample);
            return GAMESTART;
        }
        if (case_num == GAME_MANUAL) {
            off_music(sample);
            return GAME_MANUAL;
        }
        if (case_num == RECORD) {
            off_music(sample);
            return RECORD;
        }
        if (case_num == EXIT) {
            off_music(sample);
            destroy_bitmap(buffer);
            freeall_user_data();
            exit(0);
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }
}
#endif
