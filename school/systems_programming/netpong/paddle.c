/*
 * Brian Behnke
 * Systems Programming - CS43203
 * Mar 4, 2022
 *
 * paddle function definitions
 *
 */

#include "pong.h"

struct pppaddle paddle;

void paddle_init(int role)
{
	paddle.pad_top  = PT_INIT;
	paddle.pad_bot  = PB_INIT;
	paddle.pad_char = PAD_SYMBOL;

	switch(role)
	{
		case(SERVER):
			paddle.pad_loc = (RIGHT_EDGE - 1);
			break;
		case(CLIENT):
			paddle.pad_loc = (LEFT_EDGE + 1);
			break;
	}

	for(int i = paddle.pad_top; i <= paddle.pad_bot; ++i)
	{
		mvaddch(i, paddle.pad_loc, paddle.pad_char);
	}
}


void paddle_up()
{
	if(paddle.pad_top > (TOP_ROW + 1)) 		/* Makes sure paddle is in-bounds */
	{
		--paddle.pad_top;
		
		mvaddch(paddle.pad_top, paddle.pad_loc, paddle.pad_char);
		mvaddch(paddle.pad_bot, paddle.pad_loc, BLANK);

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

		mvaddch(paddle.pad_bot, paddle.pad_loc, paddle.pad_char);
		mvaddch(paddle.pad_top, paddle.pad_loc, BLANK);

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

	if(x == (paddle.pad_loc - 1) || x == (paddle.pad_loc + 1))
	{
		if((paddle.pad_bot + 1) > y && y > (paddle.pad_top - 1))
			return 1;
		else
			return 0;
	}

	return 0;
}