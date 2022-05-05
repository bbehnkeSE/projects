/*
 * Brian Behnke
 * Systems Programming - CS43203
 * Mar 4, 2022
 *
 * paddle function definitions
 *
 * Compile: gcc pong.c paddle.c -lcurses -o pong
 * Run:     ./bounce
 *
 */

#include "pong.h"

#define PAD_LOC (RIGHT_EDGE - 1)

struct pppaddle paddle;

void paddle_init()
{
	paddle.pad_top  = PT_INIT;
	paddle.pad_bot  = PB_INIT;
	paddle.pad_col  = 0;
	paddle.pad_char = PAD_SYMBOL;

	for(int i = paddle.pad_top; i <= paddle.pad_bot; ++i)
	{
		mvaddch(i, PAD_LOC, paddle.pad_char);
	}
}


void paddle_up()
{
	if(paddle.pad_top > (TOP_ROW + 1)) 		/* Makes sure paddle is in-bounds */
	{
		--paddle.pad_top;
		
		mvaddch(paddle.pad_top, PAD_LOC, paddle.pad_char);
		mvaddch(paddle.pad_bot, PAD_LOC, BLANK);

		--paddle.pad_bot;

		move(0, 0);
		refresh();
	}
}


void paddle_down()
{
	if(paddle.pad_bot < (BOT_ROW - 1)) 		/* Makes sure paddle is in-bounds */
	{
		++paddle.pad_bot;

		mvaddch(paddle.pad_bot, PAD_LOC, paddle.pad_char);
		mvaddch(paddle.pad_top, PAD_LOC, BLANK);

		++paddle.pad_top;

		move(0, 0);
		refresh();
	}
}


int paddle_contact(int x, int y)
{
	/* 
	 * If the ball is in the column infront of the paddle
	 * and in the rows between the top and bottom of the paddle
	 * it will "collide" and bounce off.
	 *
	 * Added a buffer of 1 row to the top and bottom of paddle to make the game more forgiving
	 */
	if(x == (PAD_LOC - 1))
		if((paddle.pad_bot + 1) > y && y > (paddle.pad_top - 1))
			return 1;
		else
			return 0;

	return 0;
}