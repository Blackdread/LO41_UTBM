//
//  strBuf.h
//  TP1
//
//  Created by yoann on 11/02/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef TP1_strBuf_h
#define TP1_strBuf_h

typedef struct {
    int capa;
    char *s;
} strBuf;

void initBuf(strBuf* buf, int capa);
void appendBuf(strBuf* buf, char* s);
char* readBuf(strBuf* buf);

#endif
