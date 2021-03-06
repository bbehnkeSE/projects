/*
 * Brian Behnke
 * Systems Programming - CS43203
 * Mar 4, 2022
 *
 * Header file for pong.c
 * Modified version of bounce.h
 *
 * Compile: gcc pong.c paddle.c -lcurses -o pong
 * Run:     ./pong
 *
 */

#include "curses.h"
#include "stdio.h"
#include "sys/time.h"
#include "signal.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define BLANK        ' '
#define DFL_SYMBOL   'O'
#define FLOOR        '-'
#define WALL 		 '|'
#define PAD_SYMBOL   '#'
#define TOP_ROW       5
#define BOT_ROW       25
#define LEFT_EDGE     10
#define RIGHT_EDGE    80
#define X_INIT        15
#define Y_INIT        15
#define PT_INIT       12     /* top    of paddle */
#define PB_INIT       17     /* bottom of paddle */
#define TICKS_PER_SEC 50
#define LIVES_LEN     17
#define MAXNUM_X      6
#define MAXNUM_Y      6

#define X_TTM         5
#define Y_TTM         8


/* paddle prototypes */
void paddle_init();
void paddle_up();
void paddle_down();
int  paddle_contact(int, int);

struct ppball
{
	int yPos, xPos,
	    yTtm, xTtm,
	    yTtg, xTtg,
	    yDir, xDir,
	    remaining;

	char symbol;
};


struct pppaddle
{
	int pad_top,
		pad_bot,
		pad_col; 		/* I don't know what this is for but the instructions said to add it */

	char pad_char;
};