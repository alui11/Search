/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool        filterr(const char *path, const Settings *settings) {
    //printf("Running filter\n");
    struct stat s;
    if(lstat(path, &s) == 0){
        if(settings->access && access(path, settings->access)!=0){
            //printf("Failed access\n");
            return true;
        }
        if(settings->type){
           if((settings->type == 'f' && !S_ISREG(s.st_mode)) || (settings->type == 'd' && !S_ISDIR(s.st_mode))){
                //printf("Failed type\n");
                return true;
            }
        }
        if(settings->empty && S_ISDIR(s.st_mode)){
            if(!is_directory_empty(path)){
                //printf("Failed empty - directory\n");
                return true;
            }
        }else if(settings->empty && (S_ISREG(s.st_mode) || S_ISLNK(s.st_mode))){
            if(s.st_size!=0){
                //printf("Failed empty - file\n");
                return true;
            }
        }
        if(settings->uid!=-1 && s.st_uid!=settings->uid){
            //printf("Failed uid\n");
            return true;
        }
        if(settings->gid!=-1 && s.st_gid!=settings->gid){
            //printf("Failed gid\n");
            return true;
        }
        if(settings->perm){
            if(settings->perm != (s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO))){
                return true;
            }
        }
    }
    char *base = strrchr(path, '/');
    if(settings->name && fnmatch(settings->name, base, 0)){
        //printf("Failed name\n");
        return true;
    }
    if(settings->path && fnmatch(settings->path, path, 0)){
        //printf("Failed path\n");
        return true;
    }
    if(settings->newer && get_mtime(path)<=settings->newer){
        //printf("Failed time\n");
        return true;
    }
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
