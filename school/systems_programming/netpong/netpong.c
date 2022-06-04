/*
 * Brian Behnke
 * Systems Programming - CS43203
 * Mar 4, 2022
 *
 * Simple, single-player pong game
 * Modified verson of bounce2d.c
 *
 * Compile: gcc netpong.c paddle.c socklib.c -lcurses -o netpong, or type make.
 * Run:     ./netpong [port number] or
 *	    ./netpong [hostname] [port number]
 *
 *	    ***INCOMPLETE***
 * See provided README.txt for more details
 */


#include "pong.h"


struct pppaddle paddle;
struct ppball   ball;
void   setUp(int, int, char name[256]);
void   wrapUp();
void   moveBall(int);
void   reset(struct ppball *);
int    bounceOrLose(struct ppball *);
int    setTicker(int);

struct ppball setBall(int, int);


int main(int argc, char* argv[])
{
	if(argc == 1) 
	{
		printf("Too few arguments. Exiting...\n");
        	return -1;
	}

	if(argc == 2) 	// Process is the server
	{
		int role  = SERVER;
		int score = 0;

		// Gets name of the host player and creates the welcome message to send to the client
		printf("Please enter your name: ");
		char name[256];
		scanf("%s", name);
		char welcomeMsg[256] = "\n*************************\n*        NETPONG        *\n*************************\n  Welcome to the game!\n";

		int port = atoi(argv[1]);
		int sock = make_server_socket(port);
		if(sock == -1)
			return -1;

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

		// Get client's name
		char clientName[256];
		recv(client, &clientName, sizeof(clientName), 0);

		// Serialize struct data to send to client
		char gameInfo[512];
		sprintf(gameInfo, "%0.1f,%d,%d,%s", VERSION, TICKS_PER_SEC, 20, name);

		// Send message to client
		printf("Sending message...\t");
		fflush(stdout);
		send(client, welcomeMsg, sizeof(welcomeMsg), 0);
		send(client, gameInfo, sizeof(gameInfo), 0);
		printf("Done.\n");

		// Begin the game
		printf("%s", welcomeMsg);
		printf("  Version: %0.1f\n\n", VERSION);

		// Set max score and send to client
		printf("You will be playing with ");
		printf("%s\n", clientName);
		printf("Enter the number of ping pong balls: ");
		int ppb = 0;
		scanf("%d", &ppb);
		send(client, &ppb, sizeof(ppb), 0);

		int c;
		int hasBall = 0;
		setUp(role, ppb, clientName);
		ball.remaining = ppb;
		while(ball.remaining > 0 && (c=getchar()) != 'q')
			switch (c)
			{
				case 'k':paddle_up();  break;
				case 'j':paddle_down();break;
			}
		wrapUp();

		// Close the socket
		printf("Closing the socket...\t");
		fflush(stdout);
		close(sock);
		printf("Done.\n");

		return 0;
	}

	if(argc == 3) 	// Process is the client
	{
		int role  = CLIENT;
		int score = 0;

		printf("Please enter your name: ");
		char name[256];
		scanf("%s", name);

		char *host = argv[1];
		int   port = atoi(argv[2]);
		int   sock = connect_to_server(host, port);
		if(sock == -1)
			return -1;

		// Send client name to server
		send(sock, name, sizeof(name), 0);

		// Receive data from server
		char welcomeMsg[256];
		char hostInfo[512];
		recv(sock, &welcomeMsg, sizeof(welcomeMsg), 0);
		recv(sock, &hostInfo, sizeof(hostInfo), 0);

		// Parse data from server
		float versionNum = 0.0;
		int   tps 	 = 0;
		int   netHeight  = 0;
		char  hostName[256];
		sscanf(hostInfo, "%f,%d,%d,%s", &versionNum, &tps, &netHeight, hostName);

		// Begin the game
		printf("%s", welcomeMsg);
		printf("  Version: %0.1f\n\n", versionNum);
		printf("Waiting for your opponent, ");
		printf("%s ", hostName);
		printf(" to decide the max score...\n");
		int ppb = 0;
		recv(sock, &ppb, sizeof(ppb), 0);
		printf("Total ping pong balls: %d\n", ppb);

		// Create ball
		struct ppball ball = setBall(role, ppb);

		int c;
		int hasBall = 1;
		setUp(role, ppb, hostName);
		while(ball.remaining > 0 && (c=getchar()) != 'q')
			switch (c)
			{
				case 'k':paddle_up();  break;
				case 'j':paddle_down();break;
			}
		wrapUp();

		// Close the socket
		printf("Closing the socket...\t");
		fflush(stdout);
		close(sock);
		printf("Done.\n");

		return 0;
	}

	return 0;
}


struct ppball setBall(int role, int ppb)
{
	struct ppball ball;

	ball.xPos      = X_INIT;
	ball.yPos      = Y_INIT;
	ball.xTtg      = ball.xTtm = X_TTM;
	ball.yTtg      = ball.yTtm = Y_TTM;
	ball.remaining = ppb;
	ball.symbol    = DFL_SYMBOL;

	if(role == SERVER)
		ball.xDir = 1;
	else
		ball.xDir = -1;

	if(rand() % 2)
		ball.yDir = -1;
	else
		ball.yDir =  1;

	return ball;
}


void setUp(int role, int ppb, char name[256])
{
	srand(time(NULL));

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

	// Display scoreboard
	mvaddstr(BOT_ROW + 1, LEFT_EDGE, "Me: 0");
	mvaddstr(BOT_ROW + 1, LEFT_EDGE + 7, name);
	mvaddstr(BOT_ROW + 1, (LEFT_EDGE + 7 + strlen(name)), ": 0");

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