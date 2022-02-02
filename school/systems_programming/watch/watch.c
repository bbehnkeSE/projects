/*
 * Brian Behnke
 * Systems Programming
 * Feb 11, 2022
 *
 * Checks for the login/logout of one or more users
 */

#include    <stdio.h>
#include    <sys/types.h>
#include    <utmp.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <unistd.h>      /* sleep() */

void show_info(struct utmp *);
int  checkNum (char cla[]);

int main(int argc, char *argv[])
{
    struct utmp *utbufp,        /* holds pointer to next rec    */
                *utmp_next();   /* returns pointer to next  */

    int sleepTime;
    if(checkNum(argv[1])) 
        sscanf(argv[1], "%d", &sleepTime);  /* converts argv[1] to int */
    else
        sleepTime = 10;

    /* infinite loop to keep checking users */
    for(;;)
    {
        if (utmp_open(UTMP_FILE) == -1) {
            perror(UTMP_FILE);
            exit(1);
        }

        while ((utbufp = utmp_next()) != ((struct utmp *) NULL))
            show_info(utbufp);
        utmp_close();

        sleep(sleepTime);
    }
    return 0;
}

/*
 *  show info()
 *  displays the contents of the utmp struct
 *  in human readable form
 *  displays nothing if record has no user name
 */
void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-8.8s\n", utbufp->ut_name);      /* the logname  */
}

/* Checks if char array is an int */
int checkNum(char cla[])
{
    for(int i = 0; cla[i] != 0; ++i)
        if(!isdigit(cla[i]))
            return 0;

    return 1;
}