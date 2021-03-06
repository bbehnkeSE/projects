/* who4.c - who with buffered reads
*  Identity crisis: The manual page for who lists who   am   i as an acceptable *usage of     *   the command. It also lists whoami. Modify who2.c so it supports the who am i *usage. 
*   Experiment with the command whom and read the manage. How does it differ from who    
*   am i ? write a program that works like whoami.
*/

/*
*  Brian Behnke
*  System Programming CS-43203
*  Jan 29, 2022
*
*  Simple program to function like whoami
*/

#include	<stdio.h>
#include    <pwd.h>

int main()
{
	struct passwd  *pwbufp;
	pwbufp = getpwuid(geteuid());
	printf("%s\n", pwbufp->pw_name);
	
	return 0;
}
