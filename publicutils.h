#ifndef Q_PUBLIC_H
#include "publicheader.h"
#endif

int fullstrcmp(const char *a,const char *b);
void initmatches();
void initSearchResult();
void addEntries(const char*,const char*,int);
void sortEntries();
void printEntries();
void savedata();
int loaddata();
void setmatches(const char* id,const char* s);
void addmatches(const char* id,const char* s,int);
void removematches(const char* id,const char* s);

char* autoconcat(const char* a ,const char* b ,char* ada,char* adb);


char* autoremove(const char *a,const char *b,char* ada,char* adb);

void initNode(struct StorageTreeNode *node);

char* getItem(unsigned int);

const char* getDirName(unsigned int,struct StorageTreeNode*);
int getDirCount(unsigned int,struct StorageTreeNode *);
void addDirItem(unsigned int,const char *,struct StorageTreeNode *);

unsigned int BKDRHash(const char*);
