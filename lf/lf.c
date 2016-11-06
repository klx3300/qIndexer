#include "../publicheader.h"
#include "lf.h"
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
void iterate_all_files(char* target,int* count){

    DIR* dir;
    struct dirent* file;
    struct stat *st;
    if(!(dir=opendir(target))){
        printf("Fatal Error:Specified Wrong Path.\n");
        return ;
    }
    while((file=readdir(dir))!=NULL){
        // loop_read_all_dirs
        if(strncmp(file->d_name,".",1)==0){
            continue;
        }
        // only storages files
        /*lstat(file->d_name,st);*/
        /*printf("%d\n",(st->st_mode));*/
        if(file->d_type==DT_DIR){
            // that's a directory!
            // recursively-search it.
            char fullpath[4096];
            strcpy(fullpath,target);
            strcat(fullpath,"/");
            strcat(fullpath,file->d_name);
            /*printf("RECURSIVE:%s\n",fullpath);*/
            iterate_all_files(fullpath,count);
            
        }else{

            char fullpath[4096];
            strcpy(fullpath,target);
            strcat(fullpath,"/");
            strcat(fullpath,file->d_name);
            /*printf("%s\n",fullpath);*/
            strcpy(files[*count],fullpath);
            (*count)++;
        }
    }
    closedir(dir);
}
