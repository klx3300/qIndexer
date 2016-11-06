#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "publicutils.h"
#ifndef Q_PUBLIC_H
#include "publicheader.h"
#endif
#include <sys/types.h>
#include <sys/stat.h>
unsigned int getLastBit(unsigned int a){
    return (a &((unsigned int) 1));
}

unsigned int bitpush(unsigned int a){
    return (a>>1);
}

void initNode(struct StorageTreeNode *node){
    node->content=NULL;
    node->p0=NULL;
    node->p1=NULL;
    node->counts=0;
    node->mypos=0;
}

void initSearchResult(){
    for(int i=0;i<65536;i++){
        searchresult[i].filename=NULL;
        for(int j=0;j<32;j++){
            searchresult[i].matchedkw[j]=NULL;
            searchresult[i].matchingnum[j]=0;
        }
    }
}

void addEntries(const char* filename,const char* kw,int counts){
    int i;
    for(i=0;i<65536;i++){
       if(searchresult[i].filename==NULL){
            break;
       }
       if(fullstrcmp(searchresult[i].filename,filename))
           break;
    }
    if(searchresult[i].filename==NULL){
        searchresult[i].filename=malloc(sizeof(char)*(strlen(filename)+1));
        strcpy(searchresult[i].filename,filename);
        searchresult[i].matchedkw[0]=malloc(sizeof(char)*(strlen(kw)+1));
        strcpy(searchresult[i].matchedkw[0],kw);
        searchresult[i].matchingnum[0]=counts;
    }else{
        int j=0;
        for(j=0;j<32;j++){
            if(searchresult[i].matchedkw[j]==NULL){
                searchresult[i].matchedkw[j]=malloc(sizeof(char)*(strlen(kw)+1));
                strcpy(searchresult[i].matchedkw[j],kw);
                searchresult[i].matchingnum[j]=counts;
                break;
            }
            if(fullstrcmp(searchresult[i].matchedkw[j],kw)){
                searchresult[i].matchingnum[j]+=counts;
                break;
            }
        }
    }
}
int entryCmp(const void *a,const void *b);
void sortEntries(){
    int i;
    for(i=0;i<65536;i++){
        if(searchresult[i].filename==NULL){
            break;
        }
    }
    qsort(searchresult,i,sizeof(struct SearchResult),entryCmp);
};

int entryCmp(const void *a,const void *b){
    struct SearchResult *ptra=(struct SearchResult*)a,*ptrb=(struct SearchResult*)b;
    int matchesa=0,matchesb=0,totalmatcha=0,totalmatchb=0;
    for(int i=0;i<32;i++){
        if(ptra->matchedkw[i]==NULL)
            break;
        matchesa++;
        totalmatcha+=ptra->matchingnum[i];
    }
    for(int i=0;i<32;i++){
        if(ptrb->matchedkw[i]==NULL)
            break;
        matchesb++;
        totalmatchb+=ptrb->matchingnum[i];
    }
    if(matchesa!=matchesb){
        return matchesb-matchesa;
    }else{
        return totalmatchb-totalmatcha;
    }
}

void printEntries(){
    for(int i=0;i<65536;i++){
        if(searchresult[i].filename==NULL){
            break;
        }
        printf("%s:(",searchresult[i].filename);
        for(int j=0;j<32;j++){
            if(searchresult[i].matchedkw[j]==NULL){
                break;
            }
            printf("%s:%d,",searchresult[i].matchedkw[j],searchresult[i].matchingnum[j]);
        }
        printf(")\n");
    }
}

char* getItem(unsigned int id){
    struct StorageTreeNode *searchptr=&database;
    int flag_searchsucc=0;
    unsigned int key=id;
    int i;
    for(i=0;i<32;i++){
        //printf("iterated ln:%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1!=NULL){
                searchptr=searchptr->p1;
            }else{
                break;
            }
        }else{
            if(searchptr->p0!=NULL){
                searchptr=searchptr->p0;
            }else{
                break;
            }
        }
        key=bitpush(key);
    }
    return searchptr->content;
}

void addItem(unsigned int id,const char* s,int flag_autodelete){
    struct StorageTreeNode *searchptr=&database;
    unsigned int key=id;
    char* buf=malloc(sizeof(char)*(strlen(s)+1));
    strcpy(buf,s);
    buf=autoconcat("|",buf,buf,NULL);
    for(int i=0;i<32;i++){
        //printf("iterated to ln%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1==NULL){
                searchptr->p1=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p1==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p1);
            }
            searchptr=searchptr->p1;
        }else{
            if(searchptr->p0==NULL){
                searchptr->p0=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p0==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p0);
            }
            searchptr=searchptr->p0;
        }
        key=bitpush(key);
    }
    // now it iterated to the leaf node.
    // let it be it.
    if(searchptr->content!=NULL)
        buf=autoconcat(searchptr->content,buf,searchptr->content,buf);
    searchptr->content=buf;
    searchptr->mypos=id;
}

void setItem(unsigned int id,const char* s){

    struct StorageTreeNode *searchptr=&database;
    unsigned int key=id;
    char* buf=malloc(sizeof(char)*(strlen(s)+1));
    strcpy(buf,s);
    for(int i=0;i<32;i++){
        if(id==(unsigned int)4055505040)
        printf("iterated to ln%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1==NULL){
                searchptr->p1=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p1==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p1);
            }
            searchptr=searchptr->p1;
        }else{
            if(searchptr->p0==NULL){
                searchptr->p0=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p0==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p0);
            }
            searchptr=searchptr->p0;
        }
        key=bitpush(key);
    }
    // now it iterated to the leaf node.
    // let it be it.
    if(id==(unsigned int)4055505040)
        printf("LOOP OUT\n");
    searchptr->content=buf;
}

const char* getDirName(unsigned int id,struct StorageTreeNode *root){
    struct StorageTreeNode *searchptr=root;
    unsigned int key=id;
    for(int i=0;i<32;i++){
        //printf("iterated ln:%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1!=NULL){
                searchptr=searchptr->p1;
            }else{
                break;
            }
        }else{
            if(searchptr->p0!=NULL){
                searchptr=searchptr->p0;
            }else{
                break;
            }
        }
        key=bitpush(key);
    }
    return searchptr->content;
}

int getDirCount(unsigned int id,struct StorageTreeNode *root){
    struct StorageTreeNode *searchptr=root;
    unsigned int key=id;
    for(int i=0;i<32;i++){
        //printf("iterated ln:%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1!=NULL){
                searchptr=searchptr->p1;
            }else{
                break;
            }
        }else{
            if(searchptr->p0!=NULL){
                searchptr=searchptr->p0;
            }else{
                break;
            }
        }
        key=bitpush(key);
    }
    return searchptr->counts;
}

void addDirItem(unsigned int id,const char* n,struct StorageTreeNode* root){
    struct StorageTreeNode *searchptr=root;
    char* name=malloc(sizeof(char)*(strlen(n)+1));
    strcpy(name,n);
    unsigned int key=id;
    for(int i=0;i<32;i++){
        //printf("iterated to ln%d\n",i);
        if(getLastBit(key)){
            if(searchptr->p1==NULL){
                searchptr->p1=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p1==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p1);
            }
            searchptr=searchptr->p1;
        }else{
            if(searchptr->p0==NULL){
                searchptr->p0=malloc(sizeof(struct StorageTreeNode));
                if(searchptr->p0==NULL){
                    printf("Fatal Exception:OOM\n");
                }
                initNode(searchptr->p0);
            }
            searchptr=searchptr->p0;
        }
        key=bitpush(key);
    }
    // now it iterated to the leaf node.
    // let it be it.
    searchptr->counts++;
    searchptr->content=name;
}

char *qitoa(int src){
	int tmp=src,cnt=0,riter=0;;
	char result[20];
	char * rr=(char*)malloc(sizeof(char)*20);
	while(tmp/10!=0){
		result[cnt]=(tmp%10)+48;
		tmp=tmp/10;
		cnt++;
	}
	result[cnt]=tmp+48;
	cnt++;
	// reverse
	for(int i=cnt-1;i>=0;i--){
		rr[riter]=result[i];
		riter++;
	}
	rr[riter]='\0';
	return rr;
}


char *qutoa(unsigned int src){
	unsigned int tmp=src,cnt=0,riter=0;;
	char result[20];
	char * rr=(char*)malloc(sizeof(char)*20);
	while(tmp/10!=0){
		result[cnt]=(tmp%10)+48;
		tmp=tmp/10;
		cnt++;
	}
	result[cnt]=tmp+48;
	cnt++;
	// reverse
	for(int i=cnt-1;i>=0;i--){
		rr[riter]=result[i];
		riter++;
	}
	rr[riter]='\0';
	return rr;
}

unsigned int BKDRHash(const char* s){
    unsigned int h=0;
    const char* iter=s;
    char ch=(char)*(iter++);
    while(ch!='\0'){
        h=h*131+ch;
        ch=(char)*(iter++);
    }
    return h;
}

int fullstrcmp(const char *a,const char *b){
    if(strlen(a)==strlen(b))
        return !strcmp(a,b);
    return 0;
}
/*
char* indexread(FILE* fp,int index){
    char buf;
    char* tmpstr=malloc(sizeof(char)*65536);
    tmpstr[0]='\0';
    for(int i=0;i<index;i++){
        while((buf=fgetc(fp))!='\n'){
            if(buf==EOF){
               return tmpstr; 
            }
        }
    }
    while((buf=fgetc(fp))!='\n'){
        if(buf==EOF){
            break;
        }else{
            int i=strlen(tmpstr);
            tmpstr[i]=buf;
            tmpstr[i+1]='\0';
        }
    }
    return tmpstr;
}
*/
void initmatches(){
    initNode(&database);
    FLAG_DEBUG_ON=0;
}
/*
void setmatches(const char * id,const char * s,int appear){
    int i;
    for(i=0;i<indexnum;i++){
        if(strlen(kwindex[i])==strlen(id))
            if(!strcmp(kwindex[i],id))
                break;
    }
    if(i==indexnum){
        // trying to set a matches that did not exist in indexes!
        // so add it to the index.
        strcpy(kwindex[i],id);
        kwmatch[i].filename[0]=malloc(sizeof(char)*(strlen(s)+1));
        strcpy(kwmatch[i].filename[0],s);
        kwmatch[i].appearance[0]=appear;
        indexnum++;
        kwmatch[i].counts=1;
    }else{
        //search filename
        int j;
        for(j=0;j<kwmatch[i].counts;j++){
           if(fullstrcmp(s,kwmatch[i].filename[j]))
              break; 
        }
        if(j==kwmatch[i].counts){
            kwmatch[i].counts++;
            kwmatch[i].filename[j]=malloc(sizeof(char)*(strlen(s)+1));
            strcpy(kwmatch[i].filename[j],s);
            kwmatch[i].appearance[j]=appear;
        }else{
            free(kwmatch[i].filename[j]);
            kwmatch[i].filename[j]=malloc(sizeof(char)*(strlen(s)+1));
            strcpy(kwmatch[i].filename[j],s);
            kwmatch[i].appearance[j]=appear;
        }
    }
}*/

void addmatches(const char* id,const char * s){
    unsigned int hash;
    hash=BKDRHash(id);
    addItem(hash,s,0);
}

void removematches(const char* id,const char* s){
    unsigned int hash=BKDRHash(id);
    char* orig=getItem(hash);
    if(orig!=NULL){
        char* buf=autoconcat("|",s,NULL,NULL);
        orig=autoremove(orig,buf,orig,buf);
        addItem(hash,orig,1);
    }
}

char* autoconchar(char *a,char b,unsigned int *currlen,unsigned int *mlen,int FLAG_AUTODELETE){
    char *buffer=a;
    if((*currlen)+1>(*mlen)){
        (*mlen)=(*mlen)*2;
        printf("WIDEN LENGTH TO %u\n",(*mlen));
        buffer=malloc(sizeof(char)*(*mlen));
        strcpy(buffer,a);
        if(FLAG_AUTODELETE)
            free(a);
    }
    buffer[*currlen]=b;
    buffer[++(*currlen)]='\0';
    return buffer;
}


char* autoconcat(const char* a,const char* b,char* ada,char* adb){
    char *buf=malloc(sizeof(char)*(strlen(a)+strlen(b)+1));
    strcpy(buf,a);
    strcat(buf,b);
    if(ada!=NULL)
        free(ada);
    if(adb!=NULL)
        free(adb);
    return buf;
}

char* autoremove(const char* a,const char* b,char* ada,char* adb){
    char *pos=NULL;
    char *tmpa=malloc(sizeof(char)*(strlen(a)+1));
    strcpy(tmpa,a);
    if((pos=strstr(tmpa,b))!=NULL){
        char* buf=malloc(sizeof(char)*(strlen(a)-strlen(b)+1));
        (*pos)='\0';
        strcpy(buf,tmpa);
        strcat(buf,(tmpa+strlen(b)));

        if(ada!=NULL)
            free(ada);
        if(adb!=NULL)
            free(adb);
        return buf;
    }else{

        if(ada!=NULL)
            free(ada);
        if(adb!=NULL)
            free(adb);
        return tmpa;
    }
};

// recursively reach every leaf
void fetcher(struct StorageTreeNode *node,FILE* fp){
    if(node->p0==NULL && node->p1==NULL){
        printf("RECURSIVE MEET %u/%u\n",node->mypos,(unsigned int)4294967295);
        fputs(qutoa(node->mypos),fp);
        fputs(":",fp);
        fputs(node->content,fp);
        fputs("\n",fp);
    }else{
        if(node->p0!=NULL)
            fetcher(node->p0,fp);
        if(node->p1!=NULL)
            fetcher(node->p1,fp);
        
    }
}

void savedata(){
    unsigned int maxu=0,iterator=0;
    maxu--;
    char* buffer=autoconcat(origpath,"/.qindexer",NULL,NULL);
    FILE *fp=fopen(buffer,"w");
    if(fp!=NULL){
        fetcher(&database,fp);
        free(buffer);
        fclose(fp);
    }
}

int loaddata(){
    char* buffer=autoconcat(origpath,"/.qindexer",NULL,NULL);
    FILE *fp=fopen(buffer,"r");
    if(fp!=NULL){
        char buf;char* sbuf=malloc(sizeof(char)*1024);unsigned int hash=0;unsigned int mlen=1024;unsigned int currlen=0;
        sbuf[0]='\0';
        while((buf=fgetc(fp))!=EOF){
            if(buf!='\n'){
                sbuf=autoconchar(sbuf,buf,&currlen,&mlen,1);
            }else{
                int i;
                for(i=0;i<strlen(sbuf);i++){
                    if(sbuf[i]==':')
                        break;
                }
                sbuf[i]='\0';
                i++;
                hash=atoi(sbuf);
                printf("SETTING %u/%u\n",hash,(unsigned int)4294967295);
                setItem(hash,sbuf+i);
                printf("SET OVER\n");
                sbuf[0]='\0';
                currlen=0;
                hash=0;
            }
        }
        if(strlen(sbuf)){
                int i;
                for(i=0;i<strlen(sbuf);i++){
                    if(sbuf[i]==':')
                        break;
                }
                sbuf[i]='\0';
                i++;
                hash=atoi(sbuf);
                printf("SETTING %u/%u\n",hash,(unsigned int)4294967295);
                setItem(hash,sbuf+i);
                sbuf[0]='\0';
                hash=0;
        }
        free(sbuf);
        free(buffer);
        fclose(fp);
        return 1;
    }else{
        return 0;
    }
}