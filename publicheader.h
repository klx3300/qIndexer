
#define Q_PUBLIC_H

char origpath[4096];
char files[65536][4096];


struct StorageTreeNode{
    char* content;
    int counts;
    unsigned int mypos;
    struct StorageTreeNode *p0;
    struct StorageTreeNode *p1;
};

struct StorageTreeNode database;

int FLAG_DEBUG_ON;

struct SearchResult{
    char* filename;
    char* matchedkw[32];
    int matchingnum[32];
};

struct SearchResult searchresult[65536];

//typedef struct existence{
    //char* filename[4096];
    //int appearance[4096];
    //int counts;
    
//}existence;

//existence kwmatch[16384];