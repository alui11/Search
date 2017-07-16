/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    //printf("%s\n", root);
    //printf("Running search\n");
    //printf("Didn't filter\n");
    struct stat s;
    if(lstat(root, &s) == 0){
        if(S_ISREG(s.st_mode) || S_ISLNK(s.st_mode)){
            if(!filterr(root, settings)){
                execute(root, settings);
            }
        }else if(S_ISDIR(s.st_mode)){
            //printf("%s\n", root);
            if(!filterr(root, settings)){
                execute(root, settings);
            }
            struct dirent *dp;
            DIR *dfd = opendir(root);
            if(dfd != NULL) {
                while((dp = readdir(dfd)) != NULL){
                    if(strcmp(dp->d_name, ".")==0 || strcmp(dp->d_name, "..")==0){
                        continue;
                    }
                    char path[BUFSIZ];
                    sprintf(path, "%s/%s", root, dp->d_name);
                    search(path, settings);
                }
                closedir(dfd);
            }
        }
    }
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
