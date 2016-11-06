#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"publicheader.h"
#include"publicutils.h"
#include"lf/lf.h"
#include"indexer/indexer.h"
#include"searcher/searcher.h"

int main(int argc,char** argv){
    // building index.
    // check command line param
    if(argc==1 || fullstrcmp("--help",argv[1])){
        printf("qIndexer alpha 0.01\n");
        printf("Usage: qIndexer COMMAND PARAMS\n");
        printf("COMMAND: build search\n");
        printf("COMMAND build: PARAMS=[directory path](absolute)\n");
        printf("COMMAND search: PARAMS= [directory path] [keyword1] ...\n");
        printf("                search result will be automatically sorted.\n");
    }else if(fullstrcmp("search",argv[1])){
        int filenumber=0;
        strcpy(origpath,argv[2]);
        iterate_all_files(argv[2],&filenumber);
        printf("iterate end.\n");
        initmatches();
        initSearchResult();
        if(!loaddata()){
            for(int i=0;i<filenumber;i++){
                printf("Checking file %d/%d\n",i,filenumber-1);
                if(isTextfile(files[i])){
                    readfile(files[i]);
                }
            }
            savedata();
        }
        printf("indexing end.\n");
        // try searching
        for(int i=3;i<argc;i++){
            searcher(argv[i]);
        }
        /*searcher("void");*/
        /*searcher("char");*/
        /*searcher("int");*/
        sortEntries();
        printEntries();
    }else if(fullstrcmp("build",argv[1])){
        // FORCE BUILD INDEX.
        int filenumber=0;
        strcpy(origpath,argv[2]);
        iterate_all_files(argv[2],&filenumber);
        printf("iterate end.\n");
        initmatches();
        initSearchResult();
        for(int i=0;i<filenumber;i++){
            printf("CHECKING FILE %d/%d\n",i,filenumber-1);
            if(isTextfile(files[i])){
                    readfile(files[i]);
            }
        }
        savedata();
        printf("INDEXING END\n");
    }
    return 0;
}

