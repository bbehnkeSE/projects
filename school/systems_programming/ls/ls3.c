/* ls3.c
 *	showing Access Times: Standard ls supports a -u option to display the time of last   
 *  access instead of the time of last modification. What happens if you use -u without using -l? 
 *  Modify ls2.c to support the -u option.
 *  Modify ls2.c	 
 */


/*
 * Brian Behnke
 * Systems Programming
 * Feb 6, 2022
 *
 * Adds -u option to ls2.c
 * Compile: cc ls3.c -o ls3
 * Run: ./ls3 runs just like ./ls2. 
 *      ./ls3 -u will list the files with their last access time instead of modification time.
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <dirent.h>
#include    <sys/stat.h>
#include    <string.h>

void do_ls(char[], int);
void dostat(char *, int);
void show_file_info( char *, struct stat *, int);
void mode_to_letters( int , char [] );
char *uid_to_name( uid_t );
char *gid_to_name( gid_t );

int compare(const void *, const void *);    /* comparison function for qsort() */

int main(int ac, char *av[])
{
    int u_op = 0;
    if(ac == 1)
        do_ls(".", u_op);

    /* 
     * check if the first argument has a '-' in front.
     * if not, treat first argument as a directory
     * if so, check if second character is a 'u'
     */
    else if ( ac == 2 && av[1][0] == '-') 
    {
        if(av[1][1] == 'u')
            u_op = 1;
        else 
        {
            printf("Only supported option is \"-u.\"\n");
            u_op = 0;
        }
        do_ls( ".", u_op );
    }
    else 
    {
        if(av[1][0] == '-' && av[1][1] == 'u') { 
            u_op = 1;
            *++av;
            --ac;
        }
        else if(av[1][0] == '-' && av[1][1] != 'u')
        {
            printf("Only supported option is \"-u.\"\n");
            u_op = 0;
            *++av;
            --ac;
        }
        while ( --ac )
        {
            printf("%s:\n", *++av );
            do_ls( *av, u_op );
        }
    }

    return 0;
}

void do_ls( char dirname[], int u_op )
/*
 *  list files in directory called dirname
 */
{
    DIR     *dir_ptr;       /* the directory */
    struct dirent   *direntp;       /* each entry    */

    if ( ( dir_ptr = opendir( dirname ) ) == NULL )
        fprintf(stderr,"ls1: cannot open %s\n", dirname);
    else
    {
        while ( ( direntp = readdir( dir_ptr ) ) != NULL )
            dostat( direntp->d_name, u_op);
        closedir(dir_ptr);
    }
} 

void dostat( char *filename, int u_op )
{
    struct stat info;

    if ( stat(filename, &info) == -1 )      /* cannot stat   */
        perror( filename );                 /* say why   */
    else                                    /* else show info    */
        show_file_info( filename, &info, u_op );
}

void show_file_info( char *filename, struct stat *info_p, int u_op )
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
    char    *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void    mode_to_letters();
    char    modestr[11];

    mode_to_letters( info_p->st_mode, modestr );

    printf( "%s"    , modestr );
    printf( "%4d "  , (int) info_p->st_nlink);  
    printf( "%-8s " , uid_to_name(info_p->st_uid) );
    printf( "%-8s " , gid_to_name(info_p->st_gid) );
    printf( "%8ld " , (long)info_p->st_size);
    if(u_op)
        printf( "%.12s ", 4+ctime(&info_p->st_atime));
    else
        printf( "%.12s ", 4+ctime(&info_p->st_mtime));
    printf( "%s\n"  , filename );
}

/*
 * utility functions
 */

int compare(const void *lhs, const void *rhs) {
    int l = ((struct stat *)lhs) -> st_atime;
    int r = ((struct stat *)rhs) -> st_atime;

    return (l - r);
}

/*
 * This function takes a mode value and a char array
 * and puts into the char array the file type and the 
 * nine letters that correspond to the bits in mode.
 * NOTE: It does not code setuid, setgid, and sticky
 * codes
 */
void mode_to_letters( int mode, char str[] )
{
    strcpy( str, "----------" );           /* default=no perms */

    if ( S_ISDIR(mode) )  str[0] = 'd';    /* directory?       */
    if ( S_ISCHR(mode) )  str[0] = 'c';    /* char devices     */
    if ( S_ISBLK(mode) )  str[0] = 'b';    /* block device     */

    if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';

    if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';

    if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}

#include    <pwd.h>

char *uid_to_name( uid_t uid )
/* 
 *  returns pointer to username associated with uid, uses getpw()
 */ 
{
    struct  passwd *getpwuid(), *pw_ptr;
    static  char numstr[10];

    if ( ( pw_ptr = getpwuid( uid ) ) == NULL ){
        sprintf(numstr,"%d", uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name ;
}

#include    <grp.h>

char *gid_to_name( gid_t gid )
/*
 *  returns pointer to group number gid. used getgrgid(3)
 */
{
    struct group *getgrgid(), *grp_ptr;
    static  char numstr[10];

    if ( ( grp_ptr = getgrgid(gid) ) == NULL ){
        sprintf(numstr,"%d", gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}