#include "allegro.h"
#include "param.h"
#include "login.h"
#include "string.h"
#include "stdlib.h"
enum login {
    BACK,
    VALID,
    INVALID
};
int Enter_ID(BITMAP* buffer, char* input_ID, int text_length) {
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

        if(!check_back(buffer)) return BACK;

        //  clear_to_color(buffer, makecol(0, 0, 0));
        back_icon(buffer);
        ID_PWD_icon(buffer);
        textout_ex(buffer, font, input_ID, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }
    clear_keybuf();
    return 1;
}

int Enter_PWD(BITMAP* buffer, char* input_ID, char* input_PWD, int text_length) {
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
        if (!check_back(buffer)) return BACK;

        back_icon(buffer);
        ID_PWD_icon(buffer);
        textout_ex(buffer, font, input_ID, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
       // textout_ex(buffer, font, input_PWD, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2 + 30, makecol(255, 255, 255), -1);
        //  textprintf_ex(screen, font, 100, 100, makecol(0, 255, 0), -1, "Mouse X: %d, Mouse Y: %d",text_length , mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);
    }
    return 1;
}

void back_icon(BITMAP* buffer) {
    rectfill(buffer, 0, 0, 60, 40, makecol(255, 0, 0));
    textout_centre_ex(buffer, font, "Back ", 35, 20, makecol(255, 255, 255), -1);
}
void ID_PWD_icon(BITMAP* buffer) {
    textout_centre_ex(buffer, font, "ID : ", MAX_WIDTH / 2 - 200, MAX_DEPTH / 2, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "Password : ", MAX_WIDTH / 2 - 200, MAX_DEPTH / 2 + 30, makecol(255, 255, 255), -1);
}
int check_back(BITMAP* buffer) {
    if (mouse_b & 1 && mouse_x > 0 && mouse_x < 60 && mouse_y > 0 && mouse_y < 40) {
        clear_to_color(buffer, makecol(0, 0, 0));
        return BACK;
    }
}
int main_login(BITMAP* buffer) {
    char input_ID[20] = "";
    char input_PWD[20] = "";
    int ID_length = 0;
    int PWD_length = 0;
    while (1) {

        back_icon(buffer);
        ID_PWD_icon(buffer);
        check_back(buffer);
        
        if (!Enter_ID(buffer, input_ID, ID_length)){
            return BACK;
        }
        if (!Enter_PWD(buffer, input_ID, input_PWD, PWD_length)) {
            return BACK;
        }

        if (strcmp(input_ID,"a")==0) {
            textout_centre_ex(buffer, font, "VALID", MAX_WIDTH / 2-80, MAX_DEPTH/2+60, makecol(0, 0, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1500);
            clear_to_color(buffer, makecol(0, 0, 0));
            return VALID;
        }
        else {
            textout_centre_ex(buffer, font, "INVALID", MAX_WIDTH / 2-80, MAX_DEPTH/2+60, makecol(0, 0, 255), -1);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
            return INVALID;
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    }
}
