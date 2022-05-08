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
void   setUp(int);
void   wrapUp();
void   moveBall(int);
void   reset(struct ppball *);
int    bounceOrLose(struct ppball *);
int    setTicker(int);


int main(int argc, char* argv[])
{
	if(argc == 1) 
	{
		printf("Too few arguments. Exiting...\n");
        	return -1;
	}

	if(argc == 2) 	// Process is the server
	{
		//int role = SERVER;

		// Gets name of the host player and creates the welcome message to send to the client
		printf("Please enter your name: ");
		char name[100];
		scanf("%s", name);
		char welcomeMsg[256] = "\n*************************\n*        NETPONG        *\n*************************\n  Welcome to the game!\n";

		// Initialize host info
		struct pphost host;
		host.versionNum = VERSION;
		host.tps 	= TICKS_PER_SEC;
		host.netHeight 	= 20;
		strcpy(host.name, name);

		int port = atoi(argv[1]);
		int sock = make_server_socket(port);

		// Get client socket
		printf("Waiting for client...\t");
		fflush(stdout);
		int client;
		if((client = accept(sock, NULL, NULL)) == -1)
		{
			printf("Unable to accept.\n");
			return -1;
		}
		printf("Done.\n");

		// Serialize struct data to send to client
		char txt[512];
		sprintf(txt, "%0.1f,%d,%d,%s", host.versionNum, host.tps, host.netHeight, host.name);

		// Send message to client
		printf("Sending message...\t");
		fflush(stdout);
		send(client, welcomeMsg, sizeof(welcomeMsg), 0);
		send(client, txt, sizeof(txt), 0);
		printf("Done.\n");

		// Begin the game
		printf("%s", welcomeMsg);
		printf("  Version: %0.1f\n\n", host.versionNum);

		// Close the socket
		printf("Closing the socket...\t");
		fflush(stdout);
		close(sock);
		printf("Done.\n");

		return 0;
	}

	if(argc == 3) 	// Process is the client
	{
		//int role = CLIENT;

		printf("Please enter your name: ");
		char name[100];
		scanf("%s", name);

		char *host = argv[1];
		int   port = atoi(argv[2]);
		int   sock = connect_to_server(host, port);

		// Receive data from server
		char welcomeMsg[256];
		char hostInfo[512];
		recv(sock, &welcomeMsg, sizeof(welcomeMsg), 0);
		recv(sock, &hostInfo, sizeof(hostInfo), 0);

		// Parse data from server
		struct pphost info;
		sscanf(hostInfo, "%f,%d,%d,%s", &info.versionNum, &info.tps, &info.netHeight, info.name);

		// Begin the game
		printf("%s", welcomeMsg);
		printf("  Version: %0.1f\n\n", info.versionNum);

		// Close the socket
		printf("Closing the socket...\t");
		fflush(stdout);
		close(sock);
		printf("Done.\n");

		return 0;
	}
	/*
	int c;
	setUp();
	while(ball.remaining > 0 && (c=getchar()) != 'q')
		switch (c)
		{
			case 'k':paddle_up();  break;
			case 'j':paddle_down();break;
		}
	wrapUp();
	*/

	return 0;
}


void setUp(int role)
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

	// Set location of net depending on player side
	int netSide;
	switch(role)
	{
		case(SERVER):
			netSide = LEFT_EDGE;
			break;
		case(CLIENT):
			netSide = RIGHT_EDGE;
			break;
	}

	/* Draw the playing field */
	for(int i = TOP_ROW; i <= BOT_ROW; ++i)
		for(int j = LEFT_EDGE; j <= RIGHT_EDGE; ++j)
		{
			move(i, j);
			if(i == TOP_ROW || i == BOT_ROW)
				addch(FLOOR);
			else if(j == netSide)
				addch(NET);
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

	paddle_init(role);
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