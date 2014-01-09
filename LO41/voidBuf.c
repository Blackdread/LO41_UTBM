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
#include "voidBuf.h"

void initBuf(voidBuf* buf, int capa){
    buf->capa = capa;
    buf->nbElement = 0;
    buf->buffer = (void **)malloc(capa*sizeof(void*));
    //buf->buffer[0] = (void *)malloc(sizeof(void*));
}
void appendBuf(voidBuf* buf, void* s){
    printf("buffer total: %d %d\n",buf->nbElement, buf->capa);
    if(buf->nbElement+1 > buf->capa){
        buf->buffer = (void **)realloc(buf->buffer, (buf->capa+1)*sizeof(void*));
        buf->capa = buf->capa+1;
        printf("buffer reallouer\n");
    }
    
    buf->buffer[buf->nbElement] = s;
    buf->nbElement = buf->nbElement+1;
    
}

void* readBuf(voidBuf* buf, int pos){
    return buf->buffer[pos];
}

void printVoidBuf(voidBuf* buf){
    int i;
    for(i=0 ; i < buf->nbElement ; i++)
        printf("buf %d\n",(int)buf->buffer[i]);
}

void libererBuf(voidBuf* buf){
    /*
    int i;
    for(i=0 ; i < buf->nbElement ; i++)
        free(buf->buffer[i]); // ATTENTION ne stocker que des elements avec utilisation de malloc !
    */
     free(buf->buffer);
}