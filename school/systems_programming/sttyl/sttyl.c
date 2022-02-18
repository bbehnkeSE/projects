/* 
 * Brian Behnke
 * Systems Programming - CS43203
 * Feb 18, 2022
 *
 * Lite version of the stty command
 * compile/run instructions go here
 */


#include "stdio.h"
#include "stdlib.h"
#include "termios.h"

#include "string.h"

struct fl_info
{
	int   fl_value;
	char* fl_name;
};

struct fl_info lflags[] = 
{
	{ ICANON ,  "icanon" },
	{ IEXTEN ,  "ixten"  },
	{ ECHO   ,  "echo"   },
	{ ECHOE  ,  "echoe"  },
	{ ECHOK  ,  "echok"  },
	{ ISIG   ,  "isig"   },
	{ 0      ,   NULL    }
};

struct fl_info iflags[] = 
{
	{ BRKINT ,  "brkint" },
	{ INPCK  ,  "inpck"  },
	{ ICRNL  ,  "icrnl"  },
	{ IXANY  ,  "ixany"  },
	{ 0      ,   NULL    }
};

struct fl_info oflags[] =
{
	{ ONLCR  ,  "onlcr"  },
	{ OLCUC  ,  "olcuc"  },
	{ 0      ,   NULL    }
};

void  noArgs(struct termios);

void  printFlags(int, struct fl_info []);

int main(int argc, char *argv[])
{
	struct termios tio;
	if(argc > 1)
	{
		if(tcgetattr(0, &tio) == -1)
		{
			perror("Unable to get info. Exiting...");
			exit(1);
		}
		;
	}
	else
		noArgs(tio);

	return 0;
}


void noArgs(struct termios tio)
{
	if(tcgetattr(0, &tio) == -1)
	{
		perror("Unable to get info. Exiting...");
		exit(1);
	}
	/* Prints various keyboard commands */
	printf("intr = ^%c; erase = ^%c; kill = ^%c; start = ^%c; stop = ^%c;\n",
			tio.c_cc[VINTR]  - 1 + 'A',
			tio.c_cc[VERASE] - 1 + 'A',
			tio.c_cc[VKILL]  - 1 + 'A',
			tio.c_cc[VSTART] - 1 + 'A',
			tio.c_cc[VSTOP]  - 1 + 'A'
		  );

	printFlags(tio.c_iflag, iflags);
	printFlags(tio.c_lflag, lflags);
	printFlags(tio.c_oflag, oflags);
		
}

void printFlags(int flag, struct fl_info name[])
{
	for(int i = 0; name[i].fl_value; ++i)
	{
		if(flag & name[i].fl_value)
			printf("%s ",  name[i].fl_name);
		else
			printf("-%s ", name[i].fl_name);
	}
	printf("\n");
}