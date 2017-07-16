/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool        is_directory_empty(const char *path) {
    struct dirent *dp;
    DIR *dfd = opendir(path);
    if(dfd != NULL) {
        int count = 0;
        while((dp = readdir(dfd)) != NULL){
            count++;
        }
        if(count <= 2) return true;
        closedir(dfd);
    }
    return false;
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat s;
    if(lstat(path, &s) == 0){
        return s.st_mtim.tv_sec;
    }
    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
