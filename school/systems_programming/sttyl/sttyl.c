/* 
 * Brian Behnke
 * Systems Programming - CS43203
 * Feb 18, 2022
 *
 * Lite version of the stty command
 *
 * Compile: gcc -Wall sttyl.c -o sttyl
 * Run: ./sttyl
 *
 * Currently only prints certain flags without accepting arguments
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

void  noArgs     (struct termios*);
void  enable     (char*, struct termios*);
void  disable    (char*, struct termios*);

void  printFlags (int,   struct fl_info []);
int   checkFlags (char*, struct fl_info []);


int main(int argc, char *argv[])
{
	struct termios tio;
	if(argc > 1)
		for(int i = 1; i < argc; ++i)
		{
			if(argv[i][0] == '-')
				disable(argv[i], &tio);
			else
				continue;
		}
	else
		noArgs(&tio);

	return 0;
}


void disable(char* str, struct termios* tio)
{
	++str; 		/* removes '-' */
	int i = checkFlags(str, iflags);
	int l = checkFlags(str, lflags);
	int o = checkFlags(str, oflags);

	if(i)
		printf("disable %s\n", iflags[i].fl_name);
	else if(l)
		printf("disable %s\n", lflags[l].fl_name);
	else if(o)
		printf("disable %s\n", oflags[o].fl_name);
	else
		printf("Unknown mode.\n");
}


void noArgs(struct termios *tio)
{
	if(tcgetattr(0, tio) == -1)
	{
		perror("Unable to get info. Exiting...");
		exit(1);
	}
	/* Prints various keyboard commands */
	printf("intr = ^%c; erase = ^%c; kill = ^%c; start = ^%c; stop = ^%c;\n",
			tio->c_cc[VINTR]  - 1 + 'A',
			tio->c_cc[VERASE] - 1 + 'A',
			tio->c_cc[VKILL]  - 1 + 'A',
			tio->c_cc[VSTART] - 1 + 'A',
			tio->c_cc[VSTOP]  - 1 + 'A'
		  );

	printFlags(tio->c_iflag, iflags);
	printFlags(tio->c_lflag, lflags);
	printFlags(tio->c_oflag, oflags);
		
}


/* Utility functions */

int checkFlags(char* str, struct fl_info name[])
{
	for(int i = 0; name[i].fl_value; ++i)
	{
		if(!strcmp(str, name[i].fl_name))
			return i;
	}
	return 0;
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