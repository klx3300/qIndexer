#include <stdio.h>
#include <stdlib.h>
#include <magic.h>
#include <string.h>
#include <ctype.h>
#include "indexer.h"
#include "../publicheader.h"
#include "../publicutils.h"


int isTextfile(const char* filename){
    printf("CHECKING MIME : %s\n",filename);
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

void readfile(const char* filename){
    printf("READING %s\n",filename);
    FILE *fp=fopen(filename,"r");
    char buf;
    char *kw=malloc(sizeof(char)*16384);
    kw[0]='\0';
    if(fp==NULL){
        printf("Fatal Error:specific file can't be opened.");
        return;
    }
    while((buf=fgetc(fp))!=EOF){
        if(isalpha(buf) || buf=='_'){
            int k=strlen(kw);
            kw[k]=buf;
            kw[k+1]='\0';
        }else if(strlen(kw)){
            addmatches(kw,filename);
            // reset kw
            //printf("KW STORAGE:%d/16384\n",indexnum);
            kw[0]='\0';
        }//detect as a word.
    }
    if(strlen(kw)){
        addmatches(kw,filename);
    }
    free(kw);
    fclose(fp);
}

