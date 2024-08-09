#pragma once
#if 01
#include "allegro.h"

#define m_intro_bgm "./music/intro1_bgm.wav"
#define m_login_bgm "./music/login1_bgm.wav"
#define m_after_login_bgm "./music/after_login1_bgm.wav"

#define m_put_balloon "./music/put2_balloon.wav"
#define m_pop_balloon "./music/pop2_balloon.wav"

#define m_stage1_bgm "./music/stage1_bgm.wav"
#define m_stage2_bgm "./music/stage2_bgm.wav"
#define m_stage3_bgm "./music/stage3_bgm.wav"

#define m_lose "./music/lose.wav"
#define m_clear "./music/stage_clear.wav"

SAMPLE* play_music(const char* music_path);
SAMPLE* action_music(const char* music_path);
void off_music(SAMPLE*);
// WAV 파일 로드

#endif
