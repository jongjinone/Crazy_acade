#define _CRT_SECURE_NO_WARNINGS
#include "collection.h"

int main() {

    initialize_window(MAX_WIDTH, MAX_DEPTH);
    // ���� ���۸��� ���� ������ũ�� ���� ����
    BITMAP* buffer = create_bitmap(MAX_WIDTH, MAX_DEPTH);
    int case_num;

intro:
    if (main_intro(buffer) == 0) {
        goto login;
    }
    else if(main_intro(buffer) == 1) {
        goto new_register;
    }


new_register:
    case_num = main_new_register(buffer);
    if (case_num == 0) goto intro;
    if (case_num == 1) goto intro;
    if (case_num == 2) goto new_register;


login:
    case_num = main_login(buffer);
    if (case_num == 0) goto intro;
    if (case_num == 2) goto login;

after_login:
    case_num = main_AF_login(buffer);
    if (case_num == 0) goto login;
    if (case_num == 1) goto game_start;
   // if (case_num == 2) goto login;

game_start:

    case_num = game_start(1,1);
    if (case_num == 0) goto after_login;

    destroy_bitmap(buffer);

    return 0;
}
END_OF_MAIN()

