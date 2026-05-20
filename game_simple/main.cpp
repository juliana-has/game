#include <cstdio>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
static void plat_init(){}
static void plat_restore(){}
static void sleep_ms(int ms){Sleep(ms);}
static int  kb_hit(){return _kbhit();}
static char kb_get(){return (char)_getch();}
static char kb_block(){return (char)_getch();}
static void go_home(){COORD c={0,0};SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);}
static void hide_cur(){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(h,&ci);
    ci.bVisible=FALSE;
    SetConsoleCursorInfo(h,&ci);
}
static void clr_screen(){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c={0,0}; DWORD w;
    CONSOLE_SCREEN_BUFFER_INFO i;
    GetConsoleScreenBufferInfo(h,&i);
    DWORD sz=(DWORD)i.dwSize.X*(DWORD)i.dwSize.Y;
    FillConsoleOutputCharacter(h,' ',sz,c,&w);
    FillConsoleOutputAttribute(h,i.wAttributes,sz,c,&w);
    SetConsoleCursorPosition(h,c);
}
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
static struct termios orig_t;
static void plat_init(){
    tcgetattr(STDIN_FILENO,&orig_t);
    struct termios t=orig_t;
    t.c_lflag&=~(ICANON|ECHO);
    t.c_cc[VMIN]=0; t.c_cc[VTIME]=0;
    tcsetattr(STDIN_FILENO,TCSANOW,&t);
    int f=fcntl(STDIN_FILENO,F_GETFL,0);
    fcntl(STDIN_FILENO,F_SETFL,f|O_NONBLOCK);
}
static void plat_restore(){
    int f=fcntl(STDIN_FILENO,F_GETFL,0);
    fcntl(STDIN_FILENO,F_SETFL,f&~O_NONBLOCK);
    tcsetattr(STDIN_FILENO,TCSANOW,&orig_t);
}
static void sleep_ms(int ms){usleep(ms*1000);}
static int kb_hit(){char c;int n=(int)read(STDIN_FILENO,&c,1);if(n==1){ungetc(c,stdin);return 1;}return 0;}
static char kb_get(){int c=fgetc(stdin);return c==EOF?0:(char)c;}
static char kb_block(){
    plat_restore();
    struct termios t=orig_t;
    t.c_lflag&=~(ICANON|ECHO);
    t.c_cc[VMIN]=1; t.c_cc[VTIME]=0;
    tcsetattr(STDIN_FILENO,TCSANOW,&t);
    char c=(char)getchar();
    plat_init();
    return c;
}
static void go_home(){printf("\033[H");fflush(stdout);}
static void hide_cur(){printf("\033[?25l");fflush(stdout);}
static void clr_screen(){printf("\033[2J\033[H");fflush(stdout);}
#endif

#include "include/types.h"
#include "include/map.h"
#include "include/player.h"
#include "include/enemy.h"
#include "include/items.h"
#include "include/game.h"
#include "include/audio.h"

static void get_room_bounds(int room,int *r1,int *c1,int *r2,int *c2){
    if(room==1){*r1=0;  *c1=0;  *r2=8;      *c2=18;}
    else if(room==2){*r1=0;  *c1=21; *r2=8;      *c2=39;}
    else if(room==3){*r1=10; *c1=0;  *r2=18;     *c2=18;}
    else if(room==4){*r1=10; *c1=21; *r2=18;     *c2=39;}
    else if(room==5){*r1=20; *c1=0;  *r2=ROWS-1; *c2=18;}
    else            {*r1=20; *c1=21; *r2=ROWS-1; *c2=39;}
}

static const char* room_name(int room){
    if(room==1) return "Sala principal";
    if(room==2) return "Dormitorio";
    if(room==3) return "Hab. media izq.";
    if(room==4) return "Bano";
    if(room==5) return "Hab. final izq.";
    if(room==6) return "Hab. final der.";
    return "Pasillo";
}

static void draw(Game *g){
    go_home();

    int pr=g->player.pos.r, pc=g->player.pos.c;
    int curRoom=map_get_room(pr,pc);
    if(curRoom==0) curRoom=1;

    int r1,c1,r2,c2;
    get_room_bounds(curRoom,&r1,&c1,&r2,&c2);

    int viewH=r2-r1+1;
    int viewW=c2-c1+1;

    for(int r=r1;r<=r2;r++){
        for(int c=c1;c<=c2;c++){
            char ch=' ';
            int t=gMap[r][c];
            if(t==TILE_WALL)   ch='#';
            if(t==TILE_FLOOR)  ch='.';
            if(t==TILE_DOOR)   ch='+';
            if(t==TILE_CLOSET) ch='[';

            for(int i=0;i<MAX_ITEMS;i++){
                Item *it=&g->items[i];
                if(!it->collected&&it->pos.r==r&&it->pos.c==c){ch='*';break;}
            }
            for(int i=0;i<MAX_ENEMIES;i++){
                Enemy *e=&g->enemies[i];
                if(e->active&&e->pos.r==r&&e->pos.c==c){
                    ch=(e->type==0)?'B':'V';break;
                }
            }
            if(pr==r&&pc==c) ch=g->player.hidden?'H':'@';

            putchar(ch);
        }
        putchar('\n');
    }

    for(int i=viewH;i<14;i++) printf("%-*s\n",viewW,"");

    printf("%-40s\n", room_name(curRoom));
    printf("[WASD]mover [E]recoger [R]leer [Q]soltar\n");
    printf("Objetos:%d/5  Inv:%-20s%s\n",
        items_collected(g->items),
        g->player.item!=ITEM_NONE?items_name(g->player.item):"(vacio)",
        g->player.hidden?"[ESCONDIDA]":"");
    if(g->messageTicks>0)
        printf("%-42s\n",g->message);
    else
        printf("%-42s\n","");
    printf("@=Eli B=Novio V=Conciencia *=Objeto [=Arm\n");
    fflush(stdout);
}

static void wait_key(){kb_block();}

static void screen_intro(){
    clr_screen();
    printf("\n  Alguna vez pensaste que moririas por amor?\n\n");
    printf("  Pues Eli nunca lo penso.\n");
    printf("  Nunca penso que la persona que decia amarla\n");
    printf("  pudiera ser de quien tuviera que huir.\n\n");
    printf("  Recoge los 5 objetos (*) y escondete en el\n");
    printf("  armario ([) de la hab. final derecha.\n\n");
    printf("  B = novio (persigue si te acerca)\n");
    printf("  V = conciencia (aparece al leer el celular)\n");
    printf("  Si te atrapan fuera del armario, mueres.\n\n");
    printf("  [cualquier tecla para empezar]\n");
    fflush(stdout);
    wait_key();
}

static void screen_read(Game *g){
    clr_screen();
    printf("\n  [ %s ]\n\n",items_name(g->player.item));
    printf("%s\n\n",items_text(g->player.item));
    if(g->player.item==ITEM_PHONE)
        printf("  * Tu conciencia despierta...\n\n");
    printf("  [cualquier tecla para continuar]\n");
    fflush(stdout);
    if(g->player.item==ITEM_PHONE){
        g->conscienceOn=true;
        g->enemies[1].active=true;
    }
    g->player.item=ITEM_NONE;
    wait_key();
}

static void screen_dead(Game *g){
    clr_screen();
    printf("\n\n");
    if(g->killedBy==1){
        printf("  No pudiste ignorarme.\n");
        printf("  Sabias que algo estaba mal.\n\n");
    } else {
        printf("  Te atrapo.\n");
        printf("  Como tantas otras veces.\n\n");
    }
    printf("  Has muerto. Y no de amor.\n\n");
    printf("  [cualquier tecla para intentar de nuevo]\n");
    fflush(stdout);
    wait_key();
}

static void screen_win(){
    audio_play(SND_WIN);
    clr_screen();
    printf("\n\n");
    printf("  Estas en el armario.\n");
    printf("  Lo escuchas pasar.\n");
    printf("  Seguir de largo.\n\n");
    printf("  El amor no duele.\n");
    printf("  Y no deberia doler nunca.\n\n");
    printf("  [cualquier tecla para salir]\n");
    fflush(stdout);
    wait_key();
}

int main(){
    plat_init();
    hide_cur();

    Game g;
    game_init(&g);
    screen_intro();

    g.phase=PHASE_PLAY;
    clr_screen();

    while(true){
        char key=0;
        if(kb_hit()) key=kb_get();

        if(g.phase==PHASE_PLAY){
            if((key=='r'||key=='R')&&g.player.item!=ITEM_NONE&&items_text(g.player.item)){
                audio_play(SND_READ);
                screen_read(&g);
                clr_screen();
                continue;
            }
            game_update(&g,key);
            draw(&g);
            sleep_ms(80);
        }
        else if(g.phase==PHASE_DEAD){
            screen_dead(&g);
            game_init(&g);
            screen_intro();
            g.phase=PHASE_PLAY;
            clr_screen();
        }
        else if(g.phase==PHASE_WIN){
            screen_win();
            break;
        }
    }

    plat_restore();
    return 0;
}
