#pragma once
#if 01
#include "allegro.h"

#define m_intro_bgm "./music/intro_bgm.wav"
#define m_login_bgm "./music/login_bgm.wav"
#define m_after_login_bgm "./music/after_login_bgm.wav"
#define m_put_balloon "./music/put_balloon.wav"
#define m_pop_balloon "./music/pop_balloon.wav"

SAMPLE* play_music(const char* music_path);
SAMPLE* action_music(const char* music_path);
void off_music(SAMPLE*);
// WAV 파일 로드

//extern SAMPLE* sample;
#endif
