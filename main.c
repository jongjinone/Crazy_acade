#define _CRT_SECURE_NO_WARNINGS
#include "collection.h"


int main() {

    initialize_window(MAX_WIDTH, MAX_DEPTH);
    // 더블 버퍼링을 위한 오프스크린 버퍼 생성
    BITMAP* buffer = create_bitmap(MAX_WIDTH, MAX_DEPTH);
    int case_num;
    readfile();
    //printall_user_data(buffer);

    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_volume(255, 255);

    // WAV 파일 로드
    SAMPLE* sample;
    

intro:
    sample = load_sample("./music/login_bgm.wav");
    if (!sample) {
        allegro_message("WAV 파일을 로드할 수 없습니다.");
        return -1;
    }

    // WAV 파일 재생
    play_sample(sample, 255, 128, 1000, 0);


    if (main_intro(buffer) == 0) {
        destroy_sample(sample);
        goto login;
    }
    else if(main_intro(buffer) == 1) {
        destroy_sample(sample);
        goto new_register;
    }


new_register:
    case_num = main_new_register(buffer);
    if (case_num == 0) goto intro;
    if (case_num == 1) {
      //  printall_user_data(buffer);
        goto intro;
    }
    if (case_num == 2) goto new_register;


login:
    sample = load_sample("./music/after_login_bgm.wav");
    if (!sample) {
        allegro_message("WAV 파일을 로드할 수 없습니다.");
        return -1;
    }

    // WAV 파일 재생
    play_sample(sample, 255, 128, 1000, 0);

    case_num = main_login(buffer);
    if (case_num == 0) {
        destroy_sample(sample);
        goto intro;
    }
    if (case_num == 2) {
        destroy_sample(sample);
        goto login;
    }

after_login:
    case_num = main_AF_login(buffer);
    if (case_num == 0) goto login;
    if (case_num == 1) goto game_start;
    if (case_num == 2) {
        game_manual(buffer);
        goto after_login;
    }


game_start:

    case_num = game_start(1,1);
    if (case_num == 0) goto after_login;

    destroy_bitmap(buffer);

    return 0;
}
END_OF_MAIN()
