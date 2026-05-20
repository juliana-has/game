#include "../include/audio.h"

#ifdef _WIN32
#include <windows.h>

void audio_play(int snd) {
    switch(snd) {
        case SND_STEP:  Beep(200,  20); break;
        case SND_PICK:  Beep(520,  80); Beep(660, 80); break;
        case SND_READ:  Beep(330, 120); break;
        case SND_CHASE: Beep(880,  50); break;
        case SND_DEAD:  Beep(400,  80); Beep(200, 80); Beep(100,200); break;
        case SND_WIN:   Beep(260,100); Beep(330,100); Beep(390,100); Beep(520,300); break;
        case SND_HIDE:  Beep(180, 150); break;
        default: break;
    }
}

#else
#include <cstdio>
#include <unistd.h>

void audio_play(int snd) {
    switch(snd) {
        case SND_DEAD:
        case SND_CHASE:
            write(STDOUT_FILENO, "\a", 1);
            break;
        case SND_WIN:
            write(STDOUT_FILENO, "\a", 1);
            usleep(200000);
            write(STDOUT_FILENO, "\a", 1);
            break;
        default:
            break;
    }
}

#endif
