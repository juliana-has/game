#ifndef AUDIO_H
#define AUDIO_H
static const int SND_NONE      = 0;
static const int SND_STEP      = 1;
static const int SND_CHASE     = 2;
static const int SND_CATCH     = 3;
static const int SND_PICK      = 4;
static const int SND_READ      = 5;
static const int SND_HIDE      = 6;
static const int SND_WIN       = 7;
static const int SND_HEARTBEAT = 8;
bool audio_init();
void audio_shutdown();
void audio_play(int soundEvent);
void audio_update(int dist);
#endif
