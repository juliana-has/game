#include "../include/input.h"
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
static DWORD originalMode = 0;
void input_init() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hIn, &originalMode);
    DWORD newMode = originalMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hIn, newMode);
}
void input_restore() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hIn, originalMode);
}
bool input_kbhit() {
    return (_kbhit() != 0);
}
char input_getch() {
    return (char)_getch();
}
char input_getch_blocking() {
    return (char)_getch();
}
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
static struct termios originalTermios;
void input_init() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}
void input_restore() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
}
bool input_kbhit() {
    char c;
    int n = (int)read(STDIN_FILENO, &c, 1);
    if (n == 1) {
        ungetc(c, stdin);
        return true;
    }
    return false;
}
char input_getch() {
    int c = fgetc(stdin);
    if (c == EOF) return 0;
    return (char)c;
}
char input_getch_blocking() {
    struct termios blocking = originalTermios;
    blocking.c_lflag &= ~(ICANON | ECHO);
    blocking.c_cc[VMIN]  = 1;
    blocking.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &blocking);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    char c = (char)getchar();
    input_init();
    return c;
}
#endif
