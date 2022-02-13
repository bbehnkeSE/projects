/*
 * Brian Behnke
 * Systems Programming
 * Feb 11, 2022
 *
 * Checks for the login/logout of one or more users
 */

#include    <stdlib.h>
#include    <unistd.h>      /* sleep() */

#include    "u.c"

void reset_array     (struct utmp**, size_t);
int  check_utmp_array(char*, struct utmp**, size_t);
int  check_arg_array (char*, char**, size_t);
int  check_num       (char cla[]);


int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("Too few arguments. Exiting...\n");
        return 1;
    }

    size_t ut_size = NRECS * UTSIZE;

    struct utmp *utbufp;                    /* holds pointer to next rec */
    struct utmp *ut_array[ut_size];         /* holds users from previous reload() */

    if (utmp_open(UTMP_FILE) == -1) 
    {
        perror(UTMP_FILE);
        exit(1);
    }

    /* Allows optional argument to set how often the program repeats */
    int sleepTime, argv_index;
    if(check_num(argv[1])) 
    {
        sscanf(argv[1], "%d", &sleepTime);  /* converts first CLA to int and assigns to sleepTime */
        argv_index = 2;
    }
    else 
    {
        sleepTime = 300;
        argv_index = 1;
    }
    int   nrs        = utmp_reload();       /* saves number of records at first run */
    int   index_init = argv_index;          /* saves initial value of index */
    int   ut_index   = 0;

    /* checks if any given names are already logged in and stores them in ut_array */
    while((utbufp = utmp_next()) != NULLUT) 
    {
        argv_index = index_init;
        while(argv_index < argc) 
        {
            if(!strcmp(utbufp->ut_name, argv[argv_index]))
            {
                printf("%s ", utbufp->ut_name);
                ut_array[ut_index] = utbufp;
                ++ut_index;
            }
            ++argv_index;
        }
    }
    printf("(is/are) currently logged in.\n");
    utmp_close();
    ut_index = 0;

    /* infinite loop to continually check utmp file */
    for(;;)
    {
        sleep(sleepTime);
        if (utmp_open(UTMP_FILE) == -1) 
        {
            perror(UTMP_FILE);
            exit(1);
        }

        /* someone logged off */
        if(nrs > utmp_reload())
        {
            while(ut_array[ut_index] != NULL)               /* compare each name from last pass with each name in current record */
            {
                static int found = 0;
                while((utbufp = utmp_next()) != NULLUT)         
                {
                    if(!strcmp(ut_array[ut_index]->ut_name, utbufp->ut_name)) 
                    {
                        found = 1;
                        break;
                    }
                }
                if(!found)
                    printf("%s logged off.\n", ut_array[ut_index]->ut_name);

                ++ut_index;
                utmp_reload();
            }
        }

        /* someone logged on */
        if(nrs < utmp_reload())
        {
            while((utbufp = utmp_next()) != NULLUT)
                if(!check_utmp_array(utbufp->ut_name, ut_array, ut_size) && check_arg_array(utbufp->ut_name, argv, argc))
                    printf("%s logged in.\n", utbufp->ut_name);
        }

        /* resets everything to prepare for next round */
        ut_index = 0;
        nrs = utmp_reload();
        reset_array(ut_array, ut_size);
        while((utbufp = utmp_next()) != NULLUT) 
        {
            argv_index = index_init;
            while(argv_index < argc) 
            {
                if(!strcmp(utbufp->ut_name, argv[argv_index]))
                {
                    ut_array[ut_index] = utbufp;
                    ++ut_index;
                }
                ++argv_index;
            }
        }

        utmp_close();
    }
    

    return 0;
}


/* Checks if char array is an int */
int check_num(char cla[])
{
    for(int i = 0; cla[i] != 0; ++i)
        if(!isdigit(cla[i]))
            return 0;

    return 1;
}

/* array of struct utmp* */
int check_utmp_array(char* name, struct utmp** names, size_t size)
{
    for(int i = 0; i < size; ++i)
        if(!strcmp(name, names[i]))
            return i;               /* name found */

    return 0;                       /* not found */
}

/* array of char* */
int  check_arg_array(char* name, char** names, size_t size)
{
    for(int i = 0; i < size; ++i)
        if(!strcmp(name, names[i]))
            return i;               /* name found */

    return 0;                       /* not found */
}

void reset_array(struct utmp** ut_array, size_t size)
{
    for(int i = 0; i < size; ++i)
        ut_array[i] = NULL;
}