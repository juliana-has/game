#ifndef INPUT_H
#define INPUT_H
void input_init();
void input_restore();
bool input_kbhit();
char input_getch();
char input_getch_blocking();
static const char KEY_UP    = 'w';
static const char KEY_DOWN  = 's';
static const char KEY_LEFT  = 'a';
static const char KEY_RIGHT = 'd';
static const char KEY_PICK  = 'e';
static const char KEY_USE   = 'r';
static const char KEY_DROP  = 'q';
static const char KEY_ENTER = '\n';
#endif
