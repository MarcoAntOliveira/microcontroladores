
#include "Nokia5110.h"
#include "bot.h"

#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

#define SNAKE_HEAD              1
#define SNAKE_UP                2
#define SNAKE_DOWN              3
#define SNAKE_LEFT              4
#define SNAKE_RIGHT             5
#define SNAKE_FOOD              6
#define SNAKE_BLOCK             7
#define SNAKE_BLANK             0
#define SNAKE_EASTER_EGG        8
#define SNAKE_INVALID           255

#define SNAKE_START_X           12
#define SNAKE_START_Y           21
#define SNAKE_START             {SNAKE_START_X, SNAKE_START_Y}
#define INVALID_POSITION        255
#define FOOD_START              {INVALID_POSITION, INVALID_POSITION}
#define STARTING_TICKS          7

#define SNAKE_START_SIZE        2

char map[24][42];

char speed_up_points[STARTING_TICKS - 1] = {2, 5, 8, 13, 20, 35};

int last_button = BUTTON_NOT_PRESSED;
int before_button;

char head[] = SNAKE_START;
char tail[] = SNAKE_START;

char food_exist = 0;

int __aux = SNAKE_START_SIZE;

char _rand;

char _food_image = 2;

char _squares = 0;

char _food_ticks = 5;
char _ticks = STARTING_TICKS;

char _tick_cur = 0;
char _food_tick_cur = 0;

void MapStart(){

    int i, j;

    for(i = 0; i < 24; i++) for(j = 1; j < 42; j++) map[i][j] = SNAKE_BLANK;

    for(i = 0; i < 24; i++) map[i][0] = SNAKE_BLOCK;

    for(i = 0; i < 24; i++) map[i][41] = SNAKE_BLOCK;

    for(j = 0; j < 42; j++) map[0][j] = SNAKE_BLOCK;

    for(j = 0; j < 42; j++) map[23][j] = SNAKE_BLOCK;

    map[head[0]][head[1]] = SNAKE_HEAD;
}

void lost(){

    Nokia5110_Clear();

    Nokia5110_SetCursor(1, 3);
    if(_squares < 16)       Nokia5110_OutStringInv(" YOU SUCK ");
    else if(_squares < 24)  Nokia5110_OutStringInv("GAME OVER ");
    else if(_squares < 32)  Nokia5110_OutStringInv("NOT SO BAD");
    else if(_squares < 40)  Nokia5110_OutStringInv(" NOT BAD  ");
    else if(_squares < 50)  Nokia5110_OutStringInv("GOOD WORK ");
    else if(_squares < 60)  Nokia5110_OutStringInv("VERY GOOD ");
    else                    Nokia5110_OutStringInv("YOU'RE GOOD");

    Nokia5110_SetCursor(5, 2);
    Nokia5110_OutCharInv('0' + _squares%10);
    Nokia5110_OutCharInv('0' + (_squares/10)%10);
    Nokia5110_OutCharInv('0' + (_squares/100)%10);

    uint32_t loop;

    for(loop = 0; loop < 0xfffff; loop++);

    while(GetButton() == BUTTON_NOT_PRESSED);

    for(loop = 0; loop < 0xfff; loop++);

    head[0] = tail[0] = SNAKE_START_X;
    head[1] = tail[1] = SNAKE_START_Y;

    MapStart();

    _squares = 0;

    __aux = SNAKE_START_SIZE;

    _ticks = STARTING_TICKS;

    last_button = BUTTON_NOT_PRESSED;

    Nokia5110_Clear();
}

void set_food(){

    char food[2];

    for(;;){

        food[0] = 2 + _rand%21;
        food[1] = 2 + (_rand - 24)%39;

        if(map[food[0]][food[1]] == SNAKE_BLANK){

            map[food[0]][food[1]] = SNAKE_FOOD;

            food_exist = 1;

            return;
        }

        _rand -= 50;
    }
}

void draw(){

    int i, j, k;

    char food_not_found = 1;

    for(i = 0; i < 24; i += 4) for(j = 0; j < 42; j++){

        char aux[4] = {(map[i+3][j] == SNAKE_FOOD) ? _food_image : (map[i+3][j] != 0),
                       (map[i+2][j] == SNAKE_FOOD) ? _food_image : (map[i+2][j] != 0),
                       (map[i+1][j] == SNAKE_FOOD) ? _food_image : (map[i+1][j] != 0),
                       (map[i][j]   == SNAKE_FOOD) ? _food_image : (map[i][j]   != 0)};

        for(k = 0; k < 4; k++) if(aux[k] == _food_image) food_not_found = 0;

        Nokia5110_DrawMix(aux[0], aux[1], aux[2], aux[3]);
    }

    if(food_not_found) set_food();

    Nokia5110_SetCursor(0, 0);
}

void move(){

    char prev_tail[2];
    char prev_head[2];

    prev_tail[0] = tail[0];
    prev_tail[1] = tail[1];

    prev_head[0] = head[0];
    prev_head[1] = head[1];

    int next_value = SNAKE_INVALID;

    if(last_button == 1){

        next_value = map[head[0] + 1][head[1]];

        if(next_value == SNAKE_BLANK || next_value == SNAKE_FOOD) head[0]++;
        else return lost();

        map[prev_head[0]][prev_head[1]] = SNAKE_UP;
    }
    else if(last_button == 9){

        next_value = map[head[0] - 1][head[1]];

        if(next_value == SNAKE_BLANK || next_value == SNAKE_FOOD) head[0]--;
        else return lost();

        map[prev_head[0]][prev_head[1]] = SNAKE_DOWN;
    }
    else if(last_button == 4){

        next_value = map[head[0]][head[1] + 1];

        if(next_value == SNAKE_BLANK || next_value == SNAKE_FOOD) head[1]++;
        else if(next_value == SNAKE_BLOCK){

            if(head[0] == 2){

                map[head[0]][head[1]] = SNAKE_EASTER_EGG;
            }
            else return lost();
        }
        else if(next_value != SNAKE_EASTER_EGG) return lost();

        if(map[prev_head[0]][prev_head[1]] != SNAKE_EASTER_EGG) map[prev_head[0]][prev_head[1]] = SNAKE_LEFT;
        else{

            head[0] = SNAKE_START_X;
            head[1] = SNAKE_START_Y;
        }
    }
    else if(last_button == 6) {

        next_value = map[head[0]][head[1] - 1];

        if(next_value == SNAKE_BLANK || next_value == SNAKE_FOOD) head[1]--;
        else return lost();

        map[prev_head[0]][prev_head[1]] = SNAKE_RIGHT;
    }

    if(next_value == SNAKE_FOOD){

        __aux++;
        _squares++;
        food_exist = 0;
        if(_ticks > 1) if(_squares == speed_up_points[STARTING_TICKS - _ticks]) _ticks--;
    }

    int tail_value = map[prev_tail[0]][prev_tail[1]];

    if(__aux != 0){

        if(last_button != BUTTON_NOT_PRESSED) __aux--;
    }
    else{

        if(tail_value == SNAKE_UP) tail[0]++;
        else if(tail_value == SNAKE_DOWN) tail[0]--;
        else if(tail_value == SNAKE_LEFT) tail[1]++;
        else if(tail_value == SNAKE_RIGHT) tail[1]--;
        else if(tail_value == SNAKE_EASTER_EGG){

            tail[0] = SNAKE_START_X;
            tail[1] = SNAKE_START_Y;
        }

        map[prev_tail[0]][prev_tail[1]] = SNAKE_BLANK;
    }

    map[head[0]][head[1]] = SNAKE_HEAD;
}

void SysTickHandler(){

    char _bool = 0;

    if(++_tick_cur >= _ticks && last_button != BUTTON_NOT_PRESSED){

        if(!food_exist) set_food();

        move();
        _tick_cur = 0;

        before_button = last_button;

        _bool = 1;
    }

    if(++_food_tick_cur >= _food_ticks){

        if(_food_image == 3) _food_image = 2;
        else _food_image = 3;

        _food_tick_cur = 0;

        draw();
    }
    else if(_bool) draw();
}

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    ConfigureButtons();

    MapStart();

    Nokia5110_Init();

    Nokia5110_Clear();

    Nokia5110_SetCursor(4, 2);

    Nokia5110_OutStringInv("Snake");

    int loop = 0;

    while(GetButton() == BUTTON_NOT_PRESSED) if(loop++ == 0xffff) break;

    Nokia5110_Clear();

    Nokia5110_SetCursor(1, 4);
    Nokia5110_OutStringInv("SW2  - UP  ");

    Nokia5110_SetCursor(1, 3);
    Nokia5110_OutStringInv("SW5  - LEFT");

    Nokia5110_SetCursor(0, 2);
    Nokia5110_OutStringInv("SW7  - RIGHT");

    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutStringInv("SW10 - DOWN");

    loop = 0;

    while(GetButton() == BUTTON_NOT_PRESSED) if(loop++ == 0x20000) break;

    Nokia5110_Clear();

    SysTickEnable();

    SysTickIntEnable();

    SysTickPeriodSet(400000);

    IntMasterEnable();

    while (1){

        int aux = GetButton();

        if(aux == 1 || aux == 4 || aux == 9 || aux == 6){

            if(aux == 1 && before_button == 9) continue;
            else if(aux == 4 && before_button == 6) continue;
            else if(aux == 9 && before_button == 1) continue;
            else if(aux == 6 && before_button == 4) continue;

            last_button = aux;

            _rand = SysTickValueGet();
        }
    }
}
