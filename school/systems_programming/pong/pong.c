/*
 * Brian Behnke
 * Systems Programming - CS43203
 * Mar 4, 2022
 *
 * Simple, single-player pong game
 * Modified verson of bounce2d.c
 *
 * Compile: gcc pong.c paddle.c -lcurses -o pong
 * Run:     ./pong
 *
 */


#include "pong.h"


struct ppball   ball;
struct pppaddle paddle;
void   setUp();
void   wrapUp();
void   moveBall(int);
void   reset(struct ppball *);
int    bounceOrLose(struct ppball *);
int    setTicker(int);


int main()
{
	int c;
	setUp();
	while(ball.remaining > 0 && (c=getchar()) != 'q')
		switch (c)
		{
			case 'k':paddle_up();  break;
			case 'j':paddle_down();break;
		}
	wrapUp();

	return 0;
}


void setUp()
{
	srand(time(NULL));

	ball.xPos      = X_INIT;
	ball.yPos      = Y_INIT;
	ball.xTtg      = ball.xTtm = X_TTM;
	ball.yTtg      = ball.yTtm = Y_TTM;
	ball.remaining = 3;
	ball.xDir      = 1;
	ball.symbol    = DFL_SYMBOL;

	if(rand() % 2)
		ball.yDir = -1;
	else
		ball.yDir =  1;

	initscr();
	noecho();
	crmode();
	signal(SIGALRM, moveBall);
	setTicker(1000 / TICKS_PER_SEC);

	/* Draw the playing field */
	for(int i = TOP_ROW; i <= BOT_ROW; ++i)
		for(int j = LEFT_EDGE; j <= RIGHT_EDGE; ++j)
		{
			move(i, j);
			if(i == TOP_ROW || i == BOT_ROW)
				addch(FLOOR);
			else if(j == LEFT_EDGE)
				addch(WALL);
		}

	/* Sets up display for remaining balls */
	char* lives  = "BALLS REMAINING: ";
	mvaddstr(TOP_ROW - 1, LEFT_EDGE, lives);
	for(int i = 0; i < ball.remaining; ++i)
		mvaddch(TOP_ROW - 1, (LEFT_EDGE + LIVES_LEN + i), 'O');

	/* Displays controls */
	mvaddstr(BOT_ROW + 5, LEFT_EDGE, "CONTROLS");
	mvaddstr(BOT_ROW + 7, LEFT_EDGE, "QUIT:        Q");
	mvaddstr(BOT_ROW + 8, LEFT_EDGE, "PADDLE UP:   K");
	mvaddstr(BOT_ROW + 9, LEFT_EDGE, "PADDLE DOWN: J");

	paddle_init();
	refresh();
}


void wrapUp()
{
	endwin();
}


int setTicker(int nMSecs)
{
        struct itimerval newTimeset;
        long   nSec, nUSecs;

        nSec   =  nMSecs / 1000;
        nUSecs = (nMSecs % 1000) * 1000L;

        newTimeset.it_interval.tv_sec  = nSec;
        newTimeset.it_interval.tv_usec = nUSecs;
        newTimeset.it_value.tv_sec     = nSec;
        newTimeset.it_value.tv_usec    = nUSecs;

        return setitimer(ITIMER_REAL,&newTimeset,NULL);
}


void moveBall(int s)
{
	int yCur,xCur,moved;
	signal(SIGALRM,SIG_IGN);

	xCur  = ball.xPos;
	yCur  = ball.yPos;
	moved = 0;

	if(ball.xTtm > 0 && ball.xTtg-- == 1)
	{
		ball.xTtg = ball.xTtm;
		ball.xPos += ball.xDir;
		moved = 1;
	}
	if(ball.yTtm > 0 && ball.yTtg-- == 1)
	{
                ball.yTtg = ball.yTtm;
                ball.yPos += ball.yDir;
                moved = 1;
        }
	if(moved)
	{
		mvaddch(yCur,xCur,BLANK);
		mvaddch(ball.yPos,ball.xPos,ball.symbol);
		move(0,0);
		refresh();
		bounceOrLose(&ball);
	}
	signal(SIGALRM,moveBall);

}


int bounceOrLose(struct ppball *b)
{
	int rtval = 0;
	if(b->yPos >= BOT_ROW - 1)
	{
		b->yDir = -1;
		rtval   =  1;
	}
	else if(b->yPos <= TOP_ROW + 1)
	{
		b->yDir = 1;
		rtval   = 1;
	}
	if(paddle_contact(b->xPos, b->yPos))
	{
                b->xDir = -1;
                b->xTtg = b->xTtm = (rand() % MAXNUM_X) + 1;
                b->yTtg = b->yTtm = (rand() % MAXNUM_Y) + 1;
                rtval   =  1;
        }
        else if(b->xPos <= LEFT_EDGE + 1)
        {
                b->xDir = 1;
                rtval   = 1;
        }
        if(b->xPos == RIGHT_EDGE)
        {
        	reset(b);
        	rtval = -1;
        }
	
	return rtval;	
}


/* Resets the ball on loss */
void reset(struct ppball *b)
{
	mvaddch(b->yPos, b->xPos, BLANK); 	/* Erases "previous" ball */

	/* Sets "new" ball at initial position with random speed and direction */
	b->xPos = X_INIT;
	b->yPos = Y_INIT;
	b->xTtg = ball.xTtm = (rand() % MAXNUM_X) + 1;
	b->yTtg = ball.yTtm = (rand() % MAXNUM_Y) + 1;
	if(rand() % 2)
	{
		ball.xDir = -1;
		ball.yDir =  1;
	}
	else
	{
		ball.xDir =  1;
		ball.yDir = -1;
	}

	/* Updates the remaining ball counter */
	--b->remaining;
	mvaddch(TOP_ROW - 1, (LEFT_EDGE + LIVES_LEN + b->remaining), BLANK);
	refresh();
}