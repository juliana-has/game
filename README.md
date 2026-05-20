# ¿Alguna vez pensaste que morirías por amor?
### Dungeon Crawler — Parcial Final · C++11

---

## Integrantes

*(Completa aquí con los nombres del grupo)*

---

## Descripción

Juego de tipo dungeon-crawler 2D en consola inspirado en *Adventure* (Atari 2600, 1980).
Controlas a **Eli**, quien debe recorrer 7 habitaciones, recoger 5 objetos y esconderse
en el armario final antes de ser atrapada. La historia gira en torno a una relación de
pareja abusiva y usa las mecánicas del juego como metáfora narrativa.

---

## Controles

| Tecla | Acción |
|---|---|
| W / A / S / D | Mover a Eli |
| E | Recoger objeto cercano |
| R | Leer / usar objeto del inventario |
| Q | Soltar objeto |

---

## Objetos coleccionables

| Símbolo | Objeto | Dónde |
|---|---|---|
| `?` | Su carta | Habitación 2 |
| `k` | Llave | Habitación 6 |
| `i` | Vela | Habitación 2 |
| `p` | Celular | Baño |
| `!` | Carta tuya | Habitación final |

---

## Leyenda del mapa

| Símbolo | Significado |
|---|---|
| `@` | Eli |
| `H` | Eli escondida en armario |
| `B` | Novio (enemigo 1) |
| `V` | Conciencia (enemigo 2) |
| `#` | Pared |
| `.` | Suelo |
| `+` | Puerta |
| `C` | Armario |

---

## Compilación

### Linux

**Requisitos:** g++, cmake o make

```bash
# Con CMake (recomendado)
mkdir build && cd build
cmake ..
make
./amor_game

# Con Make
make
./amor_game

# Manual
g++ -std=c++11 -I. main.cpp src/*.cpp -lpthread -ldl -lm -o amor_game
./amor_game
```

---

### macOS

**Requisitos:** Xcode Command Line Tools (`xcode-select --install`), cmake opcional

```bash
# Con CMake
mkdir build && cd build
cmake ..
make
./amor_game

# Con Make
make
./amor_game

# Manual
g++ -std=c++11 -I. main.cpp src/*.cpp -lpthread -ldl -lm -o amor_game
./amor_game
```

---

### Windows

**Requisitos:** MinGW-w64 (incluye g++ y mingw32-make) o Visual Studio con CMake

```bash
# Con CMake + MinGW
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
amor_game.exe

# Con Make (desde terminal MinGW)
mingw32-make
amor_game.exe

# Manual (desde terminal MinGW)
g++ -std=c++11 -I. main.cpp src/*.cpp -lwinmm -o amor_game.exe
amor_game.exe
```

> En Windows el color ANSI funciona en Windows Terminal y PowerShell modernos.
> En CMD clásico los colores pueden no mostrarse.

---

## Estructura del repositorio

```
amor_game/
├── main.cpp
├── CMakeLists.txt
├── Makefile
├── README.md
├── include/
│   ├── types.h          <- constantes, structs base, fases del juego
│   ├── map.h            <- mapa, habitaciones, puertas, armarios
│   ├── player.h         <- movimiento, inventario, armario
│   ├── enemy.h          <- IA de los dos enemigos
│   ├── items.h          <- objetos coleccionables y sus textos
│   ├── input.h          <- teclado no-bloqueante (Linux/macOS/Windows)
│   ├── renderer.h       <- renderizado ASCII con colores ANSI
│   ├── audio.h          <- sistema de sonido procedural
│   ├── narrative.h      <- diálogos, typewriter, timer, mejor marca
│   └── game.h           <- estado global y lógica principal
└── src/
    ├── map.cpp
    ├── player.cpp
    ├── enemy.cpp
    ├── items.cpp
    ├── input.cpp
    ├── renderer.cpp
    ├── audio.cpp
    ├── narrative.cpp
    └── game.cpp
```

---

## Requisitos mínimos cumplidos

- [x] **Lenguaje:** C++11
- [x] **Jugabilidad:** Personaje controlable, 7 habitaciones conectadas, colisiones funcionales
- [x] **Entidades:** 2 tipos de enemigos con comportamiento de persecución
- [x] **Mapa:** Renderizado ASCII del entorno con jugador, enemigos e ítems superpuestos
- [x] **Interacción:** Inventario de un solo espacio (recoger / soltar / leer), condición de victoria y derrota
- [x] **Arquitectura:** 10 módulos separados en `.h` y `.cpp`, punteros verificables en toda la lógica (`Item*`, `Enemy*`, `Player*`)
- [x] **Automatización:** CMake + Makefile, compilación en Windows / Linux / macOS
- [x] **Memoria:** Arreglos estáticos de entidades; `new` y `delete` ausentes del game-loop

---

## Desarrollos innovadores

---

### 1. IA diferenciada por tipo de enemigo

**¿Para qué se implementó?**
Para que los dos enemigos se sientan distintos no solo visualmente sino en su comportamiento,
y para que cada uno tenga un significado narrativo propio dentro de la historia.

**¿Por qué se consideró necesario?**
Un dungeon-crawler donde los dos enemigos se mueven exactamente igual es mecánicamente
pobre y narrativamente vacío. En este juego el novio y la conciencia representan cosas
opuestas: violencia externa vs conflicto interno. Que se comporten diferente hace que
esa diferencia se sienta en el juego, no solo se lea.

**¿Cómo se implementó?**
Dentro de `enemy_update()` en `src/enemy.cpp`, los dos tipos de enemigo siguen lógicas
completamente distintas:

- **Novio (`ENT_BOYFRIEND`):** velocidad alta, patrulla todas las habitaciones en bucle.
  Cuando detecta al jugador dentro de un rango de 7 celdas entra en modo persecución.
  Si pierde de vista al jugador, guarda su última posición conocida en `lastKnownPlayer`
  y va hacia allí antes de volver a patrullar. Se puede despistar.

- **Conciencia (`ENT_CONSCIENCE`):** velocidad baja (el doble de lenta que el novio),
  pero rango de detección infinito y sin ruta de patrulla. Siempre sabe dónde está el
  jugador y se mueve hacia allí sin descanso. No se puede despistar, solo se puede
  llegar al armario antes de que alcance.

```cpp
// Novio: persigue en rango corto, guarda ultima posicion vista
if (d <= CHASE_RANGE) {
    e->chasing = true;
    e->lastKnownPlayer = playerPos;
    e->pos = step_toward(e->pos, playerPos);
} else if (e->chasing) {
    // Va al ultimo lugar donde vio al jugador
    e->pos = step_toward(e->pos, e->lastKnownPlayer);
} else {
    // Patrulla normal
    e->pos = step_toward(e->pos, e->patrol[e->patrolIdx]);
}

// Conciencia: siempre sabe donde estas, sin rango minimo
e->lastKnownPlayer = playerPos;
e->pos = step_toward(e->pos, playerPos);
```

---

### 2. Sistema de sonido procedural multiplataforma

**¿Para qué se implementó?**
Para agregar tensión sonora al juego sin depender de archivos de audio externos,
usando generación de sonido matemática en tiempo real.

**¿Por qué se consideró necesario?**
El silencio absoluto reduce el impacto emocional del juego. Un dungeon-crawler
de terror necesita retroalimentación sonora para que la persecución se sienta
amenazante. Usar archivos `.mp3` o `.wav` requeriría decoders y licencias;
generar el sonido proceduralmente resuelve ambos problemas.

**¿Cómo se implementó?**
El audio usa únicamente APIs nativas de cada sistema operativo, sin librerías externas:

- **Windows:** `Beep(frecuencia, duración)` de `windows.h`, que es nativo del SO y
  no requiere instalar nada. Corre en un hilo separado del sistema y no bloquea el juego.
- **Linux:** `ioctl` con `KIOCSOUND` sobre `/dev/tty` para emitir tonos directamente
  al altavoz del sistema. Si no hay acceso al dispositivo, cae en el bell del terminal (`\a`).
- **macOS:** bell del terminal (`\a`) que activa el sonido de alerta del sistema.

Cada evento tiene su propia frecuencia y duración:
- **Pasos:** tono grave corto (180 Hz, 25ms)
- **Recoger ítem:** dos notas ascendentes Do → Mi (523 Hz → 659 Hz)
- **Persecución:** tono agudo (880 Hz) cuando el enemigo está cerca
- **Muerte:** descenso brusco de 400 → 200 → 100 Hz
- **Victoria:** acorde ascendente Do-Mi-Sol-Do
- **Latido:** pulso grave (80 Hz) que `game_tick` dispara con mayor frecuencia
  cuanto más cerca está el enemigo

---

### 3. Narrativa integrada a la mecánica

**¿Para qué se implementó?**
Para que la historia no sea texto decorativo sino parte del diseño del juego:
cada mecánica tiene un significado dentro de la narrativa.

**¿Por qué se consideró necesario?**
La mayoría de dungeon-crawlers de parcial tienen una historia de una línea que
no afecta nada. Aquí la historia sobre violencia en pareja determina el diseño
de niveles, el comportamiento de los enemigos, el orden de los eventos y los
textos de cada pantalla. El juego comunica algo, no solo entretiene.

**¿Cómo se implementó?**
En `src/narrative.cpp` se implementaron tres sistemas:

- **Diálogos por habitación:** cada cuarto tiene una línea para la primera
  visita y otra para visitas posteriores con la conciencia activa. Los 8 mensajes
  de la conciencia están ordenados para contar una historia progresiva, no son
  aleatorios.

- **Dos pantallas de muerte distintas:** `game.cpp` registra en `killedBy`
  qué enemigo atrapó al jugador. El renderer muestra textos diferentes:
  el novio produce una muerte violenta (*"Te atrapó. Como tantas otras veces."*),
  la conciencia produce parálisis (*"No pudiste seguir ignorándome."*).

- **Efecto typewriter:** `narrative_typewriter()` imprime carácter por carácter
  con pausas variables según puntuación (pausa 6x en `.`, `?`, `!` y 3x en `,`)
  para crear ritmo narrativo en todas las pantallas de texto.

---

### 4. Contador de tiempo con mejor marca persistente

**¿Para qué se implementó?**
Para agregar rejugabilidad y una capa de reto más allá de simplemente ganar.

**¿Por qué se consideró necesario?**
Una vez que el jugador aprende el mapa el juego pierde tensión. El timer convierte
cada partida en un reto contra uno mismo y demuestra manejo de I/O en C++.

**¿Cómo se implementó?**
`timer_start()` guarda el timestamp al inicio del juego usando `clock_gettime`
en Unix y `QueryPerformanceCounter` en Windows. El tiempo transcurrido se muestra
en formato `mm:ss` en el HUD en cada frame. Al ganar, `score_save_if_better()`
compara el tiempo actual con el contenido de `bestscore.txt` y lo sobreescribe
si es mejor. La siguiente partida carga ese valor y lo muestra junto al timer.

