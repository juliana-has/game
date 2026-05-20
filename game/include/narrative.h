#ifndef NARRATIVE_H
#define NARRATIVE_H
#include "types.h"
static const int MAX_MSG_LEN  = 128;
static const int MAX_DIALOGUE = 32;
struct Message {
    char  text[MAX_MSG_LEN];
    int   ticksLeft;
    bool  active;
};
void narrative_typewriter(const char *text, int delay_ms);
void narrative_typewriter_centered(const char *text, int delay_ms, int width);
const char* narrative_room_dialogue(int roomId, const bool *visited,
                                    bool conscienceActive);
void timer_start();
int  timer_elapsed_seconds();
long long timer_elapsed_ms();
void timer_format(char *buf, int elapsed_seconds);
int  score_load_best();
void score_save_if_better(int seconds);
#endif
