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
	{ IEXTEN ,  "iexten" },
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
	if(tcgetattr(0, &tio) == -1)
	{
		perror("Unable to get info. Exiting...");
		exit(1);
	}

	if(argc > 1)
		for(int i = 1; i < argc; ++i)
		{
			if(argv[i][0] == '-')
				disable(argv[i], &tio);
			else
				enable (argv[i], &tio);
		}
	else
		noArgs(&tio);

	return 0;
}


void disable(char* str, struct termios* tio)
{
	++str; 										/* removes '-' */
	int l = checkFlags(str, lflags);
	int i = checkFlags(str, iflags);
	int o = checkFlags(str, oflags);

	/* Uses bitwise AND to turn flags off */
	if(l != -1) 								/* str found in lflags struct */
	{
		tio->c_lflag &= ~lflags[l].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else if(i != -1)							/* str found in iflags struct */
	{
		tio->c_iflag &= ~iflags[i].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else if(o != -1)							/* str found in oflags struct */
	{
		tio->c_oflag &= ~oflags[o].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else
		printf("Unknown mode.\n");
}


void enable(char* str, struct termios* tio)
{
	int l = checkFlags(str, lflags);
	int i = checkFlags(str, iflags);
	int o = checkFlags(str, oflags);

	/* Uses bitwise OR to turn flags on */
	if(l != -1) 								/* str found in lflags struct */
	{
		tio->c_lflag |= lflags[l].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else if(i != -1)							/* str found in iflags struct */
	{
		tio->c_iflag |= iflags[i].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else if(o != -1)							/* str found in oflags struct */
	{
		tio->c_oflag |= oflags[o].fl_value;
		tcsetattr(0, TCSANOW, tio);
	}
	else
		printf("Unknown mode.\n");
}


/* Prints flag status and commands */
void noArgs(struct termios *tio)
{
	/* Prints various keyboard commands */
	printf("intr = ^%c; erase = ^%c; kill = ^%c; start = ^%c; stop = ^%c;\n",
			tio->c_cc[VINTR]  - 1 + 'A',
			tio->c_cc[VERASE] - 1 + 'A',
			tio->c_cc[VKILL]  - 1 + 'A',
			tio->c_cc[VSTART] - 1 + 'A',
			tio->c_cc[VSTOP]  - 1 + 'A'
		  );

	printFlags(tio->c_lflag, lflags);
	printFlags(tio->c_iflag, iflags);
	printFlags(tio->c_oflag, oflags);
}


/* Utility functions */

/* Searches structs for flag names   */
/* Returns index if found, -1 if not */
int checkFlags(char* str, struct fl_info name[])
{
	for(int i = 0; name[i].fl_value; ++i)
	{
		if(!strcmp(str, name[i].fl_name))
			return i;
	}
	return -1;
}


/* Prints if flags are enables or disabled */
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