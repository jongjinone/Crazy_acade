#include "game_manual.h"

#define NUM_LINES 70  // Number of lines including blank lines
char* a[NUM_LINES] = {
           "Crazy Arcade: Game Manual",
           "",
           "1. Introduction",
           "Welcome to Crazy Arcade! Dive into a thrilling action game where you use water balloons to trap and defeat opponents.",
           "Are you ready to become the ultimate champion ? ",
           "",
           "2. Game Objective",
           "Eliminate opponents by trapping them with water balloons. The last player standing wins the round",
           "",
           "3. Controls",
           "Movement: Arrow keys (ก่, ก้, ก็, กๆ)",
           "Place Water Balloon: Spacebar",
           "Special Abilities: Z, X, C (if applicable)",
           "",
           "4. Characters",
           "Bomber Bob: Balanced speed and power.",
           "Speedy Sue: Fast but less powerful balloons.",
           "Strong Sam: Powerful balloons but slower.",
           "",
           "5. Power-Ups",
           "Speed Boost: Increases movement speed.",
           "Extra Balloon: Allows more balloons to be placed.",
           "Blast Radius Increase: Increases explosion radius.",
           "Shield: Temporary immunity.",
           "",
           "6. Game Modes",
           "Classic Mode: Last player standing wins.",
           "Team Battle: Last team standing wins.",
           "Time Attack: Eliminate as many opponents as possible within a time limit",
           "",
           "7. Tips and Tricks",
           "Strategic Placement: Trap opponents in confined spaces.",
           "Use Power-Ups Wisely: Gain an edge over opponents.",
           "Stay Mobile: Avoid getting trapped.",
           "Learn Your Character: Maximize effectiveness in battle.",
           "",
           "8. Troubleshooting",
           "Game Crashes: Update to the latest version and restart your computer.",
           "Connection Issues: Check and restart your internet connection.",
           "Performance Problems: Lower graphical settings.",
           "Controls Not Responding: Check keyboard connection and restart the game.",
           "",
           "Enjoy Crazy Arcade and may the best player win!"
};
int game_manual(BITMAP* buffer) {
        // Define the array of strings
       clear_to_color(buffer, makecol(0, 0, 0));

       back_icon(buffer);
        int space = 10;
        for (int i = 0; i < 43; i++) {
            textprintf_ex(buffer, font, 100, 100 + space, makecol(255, 255, 255), -1, "%s", a[i]);
            space += 10;
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        while (1) {
            if (!check_back(buffer)) break;
        }
        mouse_b = 0;
        clear_to_color(buffer, makecol(0, 0, 0));
        return 0;
 }

void print_user_record(BITMAP* buffer, USER_DATA* target_user) {
    clear_to_color(buffer, makecol(0, 0, 0));
    back_icon(buffer);
    textout_ex(buffer, font, "RECORD", MAX_WIDTH / 2-30, MAX_DEPTH / 2-70, makecol(255, 255, 255), -1);
    textout_ex(buffer, font, "SCORE", MAX_WIDTH / 2 -100, MAX_DEPTH / 2 - 20, makecol(255, 255, 255), -1);
    textout_ex(buffer, font, "DATE       TIME", MAX_WIDTH / 2-30 , MAX_DEPTH / 2 - 20, makecol(255, 255, 255), -1);

    for (int i = 0; i < 5; i++) {
        textprintf_ex(buffer, font, MAX_WIDTH / 2 - 100, MAX_DEPTH / 2 + 20 + i * 20, makecol(255, 255, 255), -1, "%s", target_user->record[i].record_num);
        textprintf_ex(buffer, font, MAX_WIDTH / 2 -30, MAX_DEPTH / 2 + 20 + i * 20, makecol(255, 255, 255), -1, "%s", target_user->record[i].record_time);
    }
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    while (1) {
        if (!check_back(buffer)) break;
    }
    mouse_b = 0;
    clear_to_color(buffer, makecol(0, 0, 0));
    rest(50);
}


