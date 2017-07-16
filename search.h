/* search.h */

#ifndef SEARCH_H
#define	SEARCH_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* Macros */

#define	    streq(s0, s1)   (strcmp((s0), (s1)) == 0)
#define     debug(M, ...) \
    fprintf(stderr, "DEBUG %s:%d:%s: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/* Type definitions */

typedef struct {
    int	    access;	/* Access modes (-executable, -readable, -writable) */
    int     type;       /* File type (-type); */
    bool    empty;      /* Empty files and directories (-empty) */
    char   *name;       /* Base of file name matches shell pattern (-name) */
    char   *path;       /* Path of file matches shell pattern (-path) */
    int     perm;       /* File's permission bits are exactly octal mode (-perm) */
    time_t  newer;      /* File was modified more recently than file (-newer) */ 
    int     uid;        /* File's numeric user ID is n */
    int     gid;        /* File's numeric group ID is n */

    bool    print;      /* Print (-print) */

    int     exec_argc;  /* Number of arguments for (-exec) */
    char  **exec_argv;  /* Arguments for (-exec) */

} Settings;

/* Function prototypes */

int	    search(const char *root, const Settings *settings);
bool	    filterr(const char *path, const Settings *settings);
int         execute(const char *path, const Settings *settings);

bool        is_directory_empty(const char *path);
time_t      get_mtime(const char *path);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
