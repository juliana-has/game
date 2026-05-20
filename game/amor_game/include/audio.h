#ifndef AUDIO_H
#define AUDIO_H

// ============================================================
//  Modulo de audio — genera sonido procedural con miniaudio
//  Un solo header, sin dependencias externas adicionales.
//  Si miniaudio.h no esta presente, todas las funciones son
//  no-ops y el juego sigue funcionando sin sonido.
// ============================================================

// Eventos de sonido
static const int SND_NONE      = 0;
static const int SND_STEP      = 1;  // paso del jugador
static const int SND_CHASE     = 2;  // enemigo cerca (pulso rapido)
static const int SND_CATCH     = 3;  // te atraparon
static const int SND_PICK      = 4;  // recoger item
static const int SND_READ      = 5;  // abrir carta/celular
static const int SND_HIDE      = 6;  // entrar al armario
static const int SND_WIN       = 7;  // victoria
static const int SND_HEARTBEAT = 8;  // latido de fondo (tension)

// Inicializa el sistema de audio. Retorna true si tuvo exito.
bool audio_init();

// Libera recursos de audio
void audio_shutdown();

// Reproduce un evento de sonido (no bloqueante)
void audio_play(int soundEvent);

// Actualiza el estado continuo (latido/tension segun distancia)
// dist: distancia Manhattan al enemigo mas cercano
void audio_update(int dist);

#endif // AUDIO_H
