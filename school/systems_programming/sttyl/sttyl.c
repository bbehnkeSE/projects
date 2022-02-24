/* 
 * Brian Behnke
 * Systems Programming - CS43203
 * Feb 23, 2022
 *
 * Lite version of the stty command
 *
 * Compile: gcc -Wall sttyl.c -o sttyl
 * Run:     ./sttyl          // prints info on various flags and commands
 *          ./sttyl [FLAG]   // enables  flag
 *          ./sttyl -[FLAG]  // disables flag
 *          ./sttyl [CMD] ^Q // sets CMD to Ctrl+Q
 *
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
	{ -1     ,   NULL    }
};

struct fl_info iflags[] = 
{
	{ BRKINT ,  "brkint" },
	{ INPCK  ,  "inpck"  },
	{ ICRNL  ,  "icrnl"  },
	{ IXANY  ,  "ixany"  },
	{ -1     ,   NULL    }
};

struct fl_info oflags[] =
{
	{ ONLCR  ,  "onlcr"  },
	{ OLCUC  ,  "olcuc"  },
	{ -1     ,   NULL    }
};

struct fl_info commands[] =
{
	{ VINTR  ,  "intr"   },
	{ VERASE ,  "erase"  },
	{ VKILL  ,  "kill"   },
	{ VSTART ,  "start"  },
	{ VSTOP  ,  "stop"   },
	{ -1     ,   NULL    }
};

void  noArgs     (struct termios*);
void  enable     (char*, struct termios*);
void  disable    (char*, struct termios*);
void  assignKey  (int  , char*, struct termios*);

void  printFlags (int  , struct fl_info []);
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
	{
	   /* 
		* If arg's first char is a '-', try to disable.
		* If arg is found in commands array, and there is another argument,
		* and that argument is shorter than three characters, assume the combination is
		* assigning a new hotkey to that command.
		* Else, try to enable arg.
		*/
		int cmdIndex = -1;
		for(int i = 1; i < argc; ++i)
		{
			if((argv[i][0] == '-') && (strlen(argv[i]) > 2))
			{
				disable(argv[i], &tio);
				continue;
			}
			cmdIndex = checkFlags(argv[i], commands);
			if((cmdIndex != -1) && (argv[i + 1] != NULL) && (strlen(argv[i + 1]) < 3))
			{
				assignKey(cmdIndex, argv[i + 1], &tio);
				continue;
			}
			if(strlen(argv[i]) > 2)
				enable (argv[i], &tio);
		}
	}
	else
		noArgs(&tio);

	return 0;
}


/* Disables flags */
void disable(char* str, struct termios* tio)
{
	++str;		/* removes '-' from str */

	/* First, check oflags */
	int o = checkFlags(str, oflags);
	if (o != -1)						/* str found in oflags struct */
	{
		tio->c_oflag &= ~oflags[o].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}

	/* If not found in oflags, check iflags */
	int i = checkFlags(str, iflags);
	if (i != -1)						/* str found in iflags struct */
	{
		tio->c_iflag &= ~iflags[i].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}

	/* Finally, check lflags struct */
	int l = checkFlags(str, lflags);
	if (l != -1) 						/* str found in lflags struct */
	{
		tio->c_lflag &= ~lflags[l].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}
	printf("Unknown mode: \"%s\".\n", str); 	  /* str wasn't found */
}


/* Enables flags */
void enable(char* str, struct termios* tio)
{
	/* First, check oflags */
	int o = checkFlags(str, oflags);
	if (o != -1)						/* str found in oflags struct */
	{
		tio->c_oflag |= oflags[o].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}

	/* If not found in oflags, check iflags */
	int i = checkFlags(str, iflags);
	if (i != -1)						/* str found in iflags struct */
	{
		tio->c_iflag |= iflags[i].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}

	/* Finally, check lflags struct */
	int l = checkFlags(str, lflags);
	if (l != -1) 						/* str found in lflags struct */
	{
		tio->c_lflag |= lflags[l].fl_value;
		tcsetattr(0, TCSANOW, tio);
		return;
	}
	printf("Unknown mode: \"%s\".\n", str); 	  /* str wasn't found */
}


void assignKey(int cmdIndex, char* hotkey, struct termios *tio)
{
	int tmp = 0;
	if(hotkey[0] == '^')
		tmp = 1;

	tio->c_cc[commands[cmdIndex].fl_value] = (hotkey[tmp] - 'A' + 1);
	tcsetattr(0, TCSANOW, tio);
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


/********* Utility functions *********/

/* Searches structs for flag names   */
/* Returns index if found, -1 if not */
int checkFlags(char* str, struct fl_info name[])
{
	for(int i = 0; name[i].fl_value != -1; ++i)
	{
		if(!strcmp(str, name[i].fl_name))
			return i;
	}
	return -1;
}


/* Prints if flags are enabled or disabled */
void printFlags(int flag, struct fl_info name[])
{
	for(int i = 0; name[i].fl_value != -1; ++i)
	{
		if(flag & name[i].fl_value)
			printf("%s ",  name[i].fl_name);
		else
			printf("-%s ", name[i].fl_name);
	}
	printf("\n");
}