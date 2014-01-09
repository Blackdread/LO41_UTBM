//
//  strBuf.h
//  TP1
//
//  Created by yoann on 11/02/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41_voidBuf
#define LO41_voidBuf

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int capa;
    int nbElement;
    void **buffer;
} voidBuf;

void initBuf(voidBuf* buf, int capa);
void appendBuf(voidBuf* buf, void* s);
void* readBuf(voidBuf* buf, int pos);

void printVoidBuf(voidBuf* buf);

void libererBuf(voidBuf* buf);

#endif
