#include "allegro.h"
#include "param.h"
#include "new_register.h"
#include "user_data.h"
#include "music.h"
#include <string.h>
#include <stdlib.h>

enum login {
    BACK,
    VALID,
    INVALID
};

int New_Enter_ID(BITMAP* buffer, char* input_ID, int text_length) {
    clear_keybuf();
    key[KEY_ENTER] = 0;
    while (!key[KEY_ENTER]) {

        clear_to_color(buffer, makecol(0, 0, 0));
        if (keypressed()) {
            int new_key = readkey();
            char ascii = new_key & 0xff;
            int scancode = new_key >> 8;

            // 백스페이스 처리
            if (scancode == KEY_BACKSPACE && text_length > 0) {
                input_ID[--text_length] = '\0';
            }
            else if (ascii >= 32 && ascii <= 126) { // 일반 문자 입력
                input_ID[text_length++] = ascii;
                input_ID[text_length] = '\0';
            }
        }

        if (!new_check_back(buffer)) return BACK;

        //  clear_to_color(buffer, makecol(0, 0, 0));
        new_back_icon(buffer);
        new_ID_PWD_icon(buffer);
        textout_ex(buffer, font, input_ID, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }
    clear_keybuf();
    return 1;
}

int New_Enter_PWD(BITMAP* buffer, char* input_ID, char* input_PWD, int text_length) {
    clear_keybuf();
    key[KEY_ENTER] = 0;
    while (!key[KEY_ENTER]) {
        clear_to_color(buffer, makecol(0, 0, 0));
        if (keypressed()) {
            int new_key = readkey();
            char ascii = new_key & 0xff;
            int scancode = new_key >> 8;

            // 백스페이스 처리
            if (scancode == KEY_BACKSPACE && text_length > 0) {
                input_PWD[--text_length] = '\0';
            }
            else if (ascii >= 32 && ascii <= 126) { // 일반 문자 입력
                input_PWD[text_length++] = ascii;
                input_PWD[text_length] = '\0';
            }
        }
        if (!new_check_back(buffer)) return BACK;

        new_back_icon(buffer);
        new_ID_PWD_icon(buffer);
        textout_ex(buffer, font, input_ID, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }
    return 1;
}

void new_back_icon(BITMAP* buffer) {
    rectfill(buffer, 0, 0, 60, 40, makecol(255, 0, 0));
    textout_centre_ex(buffer, font, "Back ", 35, 20, makecol(255, 255, 255), -1);
}
void new_ID_PWD_icon(BITMAP* buffer) {
    textout_ex(buffer, font, "New ID : ", MAX_WIDTH / 2 - 200, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
    textout_ex(buffer, font, "New Password : ", MAX_WIDTH / 2 - 200, MAX_DEPTH / 2 + 30, makecol(255, 255, 255), -1);
    textout_ex(buffer, font, "Confirm New Password : ", MAX_WIDTH / 2 - 200, MAX_DEPTH / 2 + 60, makecol(255, 255, 255), -1);
}

int new_check_back(BITMAP* buffer) {
    if (mouse_b & 1 && mouse_x > 0 && mouse_x < 60 && mouse_y > 0 && mouse_y < 40) {
        clear_to_color(buffer, makecol(0, 0, 0));
        return BACK;
    }
}

int main_new_register(BITMAP* buffer) {
    char input_ID[20] = "";
    char input_PWD[20] = "";
    char check_PWD[20] = "";
    int ID_length = 0;
    int PWD_length = 0;
    int CHECK_PWD_length = 0;

    SAMPLE* sample = play_music(m_login_bgm);

    while (1) {

        new_back_icon(buffer);
        new_ID_PWD_icon(buffer);
        new_check_back(buffer);

        if (!New_Enter_ID(buffer, input_ID, ID_length)) {
            off_music(sample);
            return BACK;
        }
        if (!New_Enter_PWD(buffer, input_ID, input_PWD, PWD_length)) {
            off_music(sample);
            return BACK;
        }
        if (!New_Enter_PWD(buffer, input_ID, check_PWD, PWD_length)) {
            off_music(sample);
            return BACK;
        }

        if (strcmp(input_PWD, check_PWD) == 0) {
            textout_centre_ex(buffer, font, "Password Confirmed", MAX_WIDTH / 2 - 80, MAX_DEPTH / 2 + 90, makecol(0, 0, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1500);
            if (Insert(input_ID, input_PWD)) {
                textout_centre_ex(buffer, font, "Data ALready Exist", MAX_WIDTH / 2 - 80, MAX_DEPTH / 2 + 130, makecol(0, 0, 255), -1);
                off_music(sample);
                return INVALID;
            }
            if (Save()) {
                textout_centre_ex(buffer, font, "Cannot Open File", MAX_WIDTH / 2 - 80, MAX_DEPTH / 2 + 130, makecol(0, 0, 255), -1);
                off_music(sample);
                return INVALID;
            }
            clear_to_color(buffer, makecol(0, 0, 0));
            off_music(sample);
            return VALID;
        }
        else {
            textout_centre_ex(buffer, font, "Password Mismatch", MAX_WIDTH / 2 - 80, MAX_DEPTH / 2 + 90, makecol(0, 0, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
            off_music(sample);
            return INVALID;
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    }
}