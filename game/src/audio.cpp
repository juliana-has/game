#include "../include/audio.h"
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
bool  audio_init()     { return true; }
void  audio_shutdown() {}
void audio_play(int soundEvent) {
    switch (soundEvent) {
        case SND_STEP:      Beep(180,  30);  break;
        case SND_PICK:      Beep(523,  80);
                            Beep(659,  80);  break;
        case SND_READ:      Beep(330, 150);  break;
        case SND_HIDE:      Beep(196, 200);  break;
        case SND_CHASE:     Beep(880,  60);  break;
        case SND_CATCH:     Beep(400,  80);
                            Beep(200,  80);
                            Beep(100, 200);  break;
        case SND_WIN:       Beep(261, 100);
                            Beep(329, 100);
                            Beep(392, 100);
                            Beep(523, 300);  break;
        case SND_HEARTBEAT: Beep(80,   40);  break;
        default: break;
    }
}
void audio_update(int dist) {
    (void)dist;
}
#else
#include <cstring>
#include <unistd.h>
#ifdef __linux__
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
static void linux_beep(int freq_hz, int dur_ms) {
    int fd = open("/dev/tty", O_RDWR);
    if (fd >= 0) {
        if (freq_hz > 0)
            ioctl(fd, KIOCSOUND, (int)(1193180 / freq_hz));
        else
            ioctl(fd, KIOCSOUND, 0);
        usleep(dur_ms * 1000);
        ioctl(fd, KIOCSOUND, 0);
        close(fd);
    } else {
        write(STDOUT_FILENO, "\a", 1);
        usleep(dur_ms * 1000);
    }
}
#else
static void linux_beep(int freq_hz, int dur_ms) {
    (void)freq_hz;
    write(STDOUT_FILENO, "\a", 1);
    usleep(dur_ms * 1000);
}
#endif
bool audio_init()     { return true; }
void audio_shutdown() {}
void audio_play(int soundEvent) {
    switch (soundEvent) {
        case SND_STEP:
            linux_beep(180, 25);
            break;
        case SND_PICK:
            linux_beep(523, 70);
            linux_beep(659, 70);
            break;
        case SND_READ:
            linux_beep(330, 130);
            break;
        case SND_HIDE:
            linux_beep(196, 180);
            break;
        case SND_CHASE:
            linux_beep(880, 55);
            break;
        case SND_CATCH:
            linux_beep(400, 70);
            linux_beep(200, 70);
            linux_beep(100, 180);
            break;
        case SND_WIN:
            linux_beep(261, 90);
            linux_beep(329, 90);
            linux_beep(392, 90);
            linux_beep(523, 250);
            break;
        case SND_HEARTBEAT:
            linux_beep(80, 35);
            break;
        default:
            break;
    }
}
void audio_update(int dist) {
    (void)dist;
}
#endif
