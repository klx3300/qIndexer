#include <stdio.h>
#include <stdlib.h>
#include <magic.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "indexer.h"
#include "../publicheader.h"
#include "../publicutils.h"


int isTextfile(const char* filename){
    /*printf("CHECKING MIME : %s\n",filename);*/
    const char* mime;
    int i=0;
    magic_t magic;
    magic=magic_open(MAGIC_MIME_TYPE);
    magic_load(magic,NULL);
    mime=magic_file(magic,filename);
    i=!strncmp(mime,"text/",5);
    magic_close(magic);
    return i;
}

void readfile(char* filename){
    /*printf("READING %s\n",filename);*/
    FILE *fp=fopen(filename,"r");
    char buf;
    char *kw=malloc(sizeof(char)*16384);
    kw[0]='\0';
    int kwlen=0;
    if(fp==NULL){
        printf("Fatal Error:specific file can't be opened.");
        return;
    }
    while((buf=fgetc(fp))!=EOF){
        if(isalpha(buf) || buf=='_' || (buf>=48 && buf<=57)){
            kw[kwlen]=buf;
            kw[++kwlen]='\0';
        }else if(kwlen){
            // lock
            addmatches(kw,filename,kwlen);
            // reset kw
            //printf("KW STORAGE:%d/16384\n",indexnum);
            kw[0]='\0';
            kwlen=0;
        }//detect as a word.
    }
    if(kwlen){
        addmatches(kw,filename,kwlen);
    }
    free(kw);
    fclose(fp);
    /*sem_post(&idle_threads);*/
}

