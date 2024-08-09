#include "music.h"
SAMPLE* play_music(const char* music_path) {
    SAMPLE* sample = load_sample(music_path);
    if (!sample) {
        allegro_message("WAV 파일을 로드할 수 없습니다.");
        return -1;
    }

    // WAV 파일 재생
    play_sample(sample, 255, 128, 1000, 1);
    return sample;
}
SAMPLE* action_music(const char* music_path) {
    SAMPLE* sample = load_sample(music_path);
    if (!sample) {
        allegro_message("WAV 파일을 로드할 수 없습니다.");
        return -1;
    }

    // WAV 파일 재생
    play_sample(sample, 255, 128, 1000, 0);
    return sample;
}
void off_music(SAMPLE* sample) {
    destroy_sample(sample);
}