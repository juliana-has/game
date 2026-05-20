#ifndef AUDIO_H
#define AUDIO_H

const int SND_STEP  = 1;
const int SND_PICK  = 2;
const int SND_READ  = 3;
const int SND_CHASE = 4;
const int SND_DEAD  = 5;
const int SND_WIN   = 6;
const int SND_HIDE  = 7;

void audio_play(int snd);

#endif
