#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../publicheader.h"
#include "searcher.h"
#include "../publicutils.h"

void storageHash(unsigned int *array,unsigned int hash,int *size){
    for(int i=0;i<*size;i++){
        if(array[i]==hash){
            return;
        }
    }
    array[*size]=hash;
    (*size)++;
}

void searcher(const char* kw){
    unsigned int hashes[16384];
    int size=0;
    struct StorageTreeNode dirTree;
    initNode(&dirTree);
    unsigned int hash=BKDRHash(kw);
    printf("KW HASHV:%u\n",hash);
    const char* existence=getItem(hash);
    if(existence==NULL){
        printf("NO MATCHING PATTERN.\n");
        return;
    }
    //separate items in string.
    printf("EXISTENCE PATTERN:%s\n",existence);
    char* buffer=malloc(sizeof(char)*(strlen(existence)+1));
    strcpy(buffer,existence);
    buffer=autoconcat(buffer,"|",buffer,NULL);
    int mlength=strlen(buffer);
    int lastpos=1;
    for(int i=1;i<mlength;i++){
        if(buffer[i]=='|'){
            buffer[i]='\0';
            unsigned int h=BKDRHash(buffer+lastpos);
            storageHash(hashes,h,&size);
            addDirItem(h,buffer+lastpos,&dirTree);
            lastpos=i+1;
        }
    }
    for(int i=0;i<size;i++){
        /*printf("%s with %d times\n",getDirName(hashes[i],&dirTree),getDirCount(hashes[i],&dirTree));*/
        addEntries(getDirName(hashes[i],&dirTree),kw,getDirCount(hashes[i],&dirTree));
    }
    


}
