#include "initialize_set.h"
//#include "param.h"
//#include "music.h"

enum INTRO {
    LOGIN =1, 
    NEW_REGISTER, 
    EXIT
};
void initialize_window(void) {
    
    // Allegro �ʱ�ȭ
    allegro_init();
    set_color_depth(16);
    // �׷��� ��� ���� (��: 640x480, 8��Ʈ �÷�)
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, MAX_WIDTH, MAX_DEPTH, 0, 0);

    // Ű���� ��� �����ϰ� ����
    install_keyboard();

    // ���콺 ��� �����ϰ� ����
    install_mouse();

    install_timer();

    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_volume(255, 255);

    // ������ ���콺�� ȭ�鿡 ǥ��
    show_mouse(screen);

    // ���� ���۸��� ���� ������ũ�� ���� ����

}

void draw_rec_login(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;
    rect(buffer, center_x - rect_width, center_y + rect_height, center_x + rect_width, center_y - rect_height, makecol(255, 0, 0)); // ���� ��
    rect(buffer, center_x - rect_width, center_y + 2 * rect_height, center_x + rect_width, center_y + 4 * rect_height, makecol(255, 0, 0));
    rect(buffer, center_x - rect_width, center_y + 5 * rect_height, center_x + rect_width, center_y + 7 * rect_height, makecol(255, 0, 0));

}
void print_text_login(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;

    textout_centre_ex(buffer, font, "LOGIN", center_x, center_y, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "NEW REGISTER", center_x, center_y + 3 * rect_height, makecol(255, 255, 255), -1);
    textout_centre_ex(buffer, font, "EXIT", center_x, center_y + 6 * rect_height, makecol(255, 255, 255), -1);
}
int login_menu(BITMAP* buffer) {
    int rect_width = 800 / 2;
    int rect_height = 100 / 2;
    int center_x = MAX_WIDTH / 2;
    int center_y = MAX_DEPTH / 2 - 50;
    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y - rect_height) && mouse_y < (center_y + rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y + rect_height, center_x + rect_width, center_y - rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            return LOGIN;
        }
    }
    if (mouse_x > (center_x - rect_width) && mouse_x < (center_x + rect_width)
        && mouse_y >(center_y + 2 * rect_height) && mouse_y < (center_y + 4 * rect_height)) {
        rectfill(buffer, center_x - rect_width, center_y + 2 * rect_height, center_x + rect_width, center_y + 4 * rect_height, makecol(255, 0, 0));

        if (mouse_b & 1) {
            clear_to_color(buffer, makecol(0, 0, 0));
            return NEW_REGISTER;
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

    draw_rec_login(buffer);
    print_text_login(buffer);
    return 0;
}

int main_intro(BITMAP* buffer) {

    BITMAP* logo = load_bitmap("./img/LOGO.bmp", NULL);
    SAMPLE* sample =  play_music(m_intro_bgm);
    while (1) {
        // ������ũ�� ���۸� ���������� �����
        clear_to_color(buffer, makecol(0, 0, 0));
        int case_num;

        case_num = login_menu(buffer);
        if (case_num == LOGIN) {
            off_music(sample);
            return 0;
        }
        if (case_num == NEW_REGISTER) {
            off_music(sample);
            return 1;
        }
        if (case_num == EXIT) {
            off_music(sample);
            exit(0);
        }

       // BITMAP* logo = load_bitmap("./img/LOGO.bmp", NULL);
        draw_sprite(buffer, logo, 450, 50);
        // ������ũ�� ������ ������ ȭ������ ����
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // ȭ���� ���ΰ�ħ�ϱ� ���� ��ٸ�
    }
}

