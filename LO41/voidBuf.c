//
//  strBuf.c
//  TP1
//
//  Created by yoann on 11/02/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strBuf.h"

void initBuf(strBuf* buf, int capa){
    buf->capa = capa;
    buf->s = (char *)malloc(capa*sizeof(char));
}
void appendBuf(strBuf* buf, char* s){
    int u = (int)strlen(s), u1 = (int)strlen(buf->s), tot = u1 + u;
    printf("total: %d\n",tot);
    if(tot > buf->capa){
        buf->s = (char *)realloc(buf->s, tot*sizeof(char));
        buf->capa = tot;
        printf("reallouer\n");
    }
    int i;
    for(i=0;i<u;i++)
        buf->s[u1+i] = s[i];
    buf->s[u1+i]='\0';
}
char* readBuf(strBuf* buf){
    return buf->s;
}