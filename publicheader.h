
#define Q_PUBLIC_H

#ifndef _PTHREAD_H
#include <pthread.h>
#endif

#ifndef _SEMAPHORE_H
#include <semaphore.h>
#endif

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

pthread_mutex_t queuemutex[4];

pthread_mutex_t treemutex;
sem_t idle_threads;

pthread_t threads[4];

typedef struct IORequest{
    unsigned int id;
    char* content;
}IORequest;

typedef struct IOQueue{
    unsigned int counts;
    IORequest requests[256];
}IOQueue;

IOQueue ioqueue[4];
int flag_threadstop[4];

//typedef struct existence{
    //char* filename[4096];
    //int appearance[4096];
    //int counts;
    
//}existence;

//existence kwmatch[16384];
