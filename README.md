Compilación
Windows
Requisitos: MinGW-w64 con g++ instalado (https://www.msys2.org)
Paso 1 — Instalar MSYS2 si no lo tienes:
Descarga e instala desde https://www.msys2.org, luego abre la terminal MSYS2 y ejecuta:
pacman -S mingw-w64-x86_64-gcc
Paso 2 — Abrir Windows PowerShell (busca "PowerShell" en el menú inicio)
Paso 3 — Navegar a la carpeta del proyecto:
cd "C:\ruta\a\la\carpeta\game"
Paso 4 — Compilar:
g++ -std=c++11 -I. main.cpp src/map.cpp src/player.cpp src/enemy.cpp src/items.cpp src/game.cpp src/audio.cpp -o game.exe
Paso 5 — Ejecutar:
.\game.exe

Linux
Requisitos: g++ instalado (sudo apt install g++ en Ubuntu/Debian)
Paso 1 — Abrir una terminal y navegar a la carpeta del proyecto:
bashcd ruta/a/la/carpeta/game_simple
Paso 2 — Compilar:
bashg++ -std=c++11 -I. main.cpp src/map.cpp src/player.cpp src/enemy.cpp src/items.cpp src/game.cpp src/audio.cpp -lpthread -lm -o game
Paso 3 — Ejecutar:
bash./game

macOS
Requisitos: Xcode Command Line Tools (xcode-select --install en la terminal)
Paso 1 — Abrir una terminal y navegar a la carpeta del proyecto:
bashcd ruta/a/la/carpeta/game_simple
Paso 2 — Compilar:
bashg++ -std=c++11 -I. main.cpp src/map.cpp src/player.cpp src/enemy.cpp src/items.cpp src/game.cpp src/audio.cpp -lpthread -lm -o game
Paso 3 — Ejecutar:
bash./game
