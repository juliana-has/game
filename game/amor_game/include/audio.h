#ifndef AUDIO_H
#define AUDIO_H


static const int SND_NONE      = 0;
static const int SND_STEP      = 1;  // paso del jugador
static const int SND_CHASE     = 2;  // enemigo cerca (pulso rapido)
static const int SND_CATCH     = 3;  // te atraparon
static const int SND_PICK      = 4;  // recoger item
static const int SND_READ      = 5;  // abrir carta/celular
static const int SND_HIDE      = 6;  // entrar al armario
static const int SND_WIN       = 7;  // victoria
static const int SND_HEARTBEAT = 8;  // latido de fondo (tension)


bool audio_init();

void audio_shutdown();

void audio_play(int soundEvent);

void audio_update(int dist);

#endif 
