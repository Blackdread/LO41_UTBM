//
//  PileFIFO.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__PileFIFO
#define LO41__PileFIFO

#include <stdio.h>
#include <stdlib.h>

typedef struct _maillon{
    struct _maillon *next;
    int value;// je pourrais mettre a la place de int -> void* ainsi j'aurais une pile fifo pouvant contenir tout
}maillon;

typedef struct _pileFIFO{
    maillon *sommet;
    //int nbElement;
}pileFIFO;

void initPileFIFO(pileFIFO* pile);

void push(pileFIFO* pile, int value);
int pop(pileFIFO* pile);
int isEmpty(const pileFIFO* pile);

void vider(pileFIFO* pile);

int getSommetValue(pileFIFO* pile);

// renvoie -1 si a atteint la fin
int getValueAt(maillon* mail, int pos);


#endif
