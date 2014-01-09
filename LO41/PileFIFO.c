//
//  PileFIFO.c
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "PileFIFO.h"

void initPileFIFO(pileFIFO* pile){
    pile->sommet = NULL;
}

void pushMail(maillon* mail, int value){
    if(mail->next == NULL){
        mail->next = (maillon*)malloc(sizeof(maillon));
        mail->next->value = value;
        mail->next->next = NULL;
        printf("malloc2 v%d",value);
    }else
        pushMail(mail->next, value);
}

void push(pileFIFO* pile, int value){
    if(pile->sommet == NULL){
        pile->sommet = (maillon*)malloc(sizeof(maillon));
        pile->sommet->value = value;
        pile->sommet->next = NULL;
        printf("malloc1 v%d",value);
    }else{
        pushMail(pile->sommet, value);
    }
        
}
int pop(pileFIFO* pile){
    // Pile supposer non vide ! sinon erreur
    
    int val = pile->sommet->value;
    maillon *s = pile->sommet;
    pile->sommet = pile->sommet->next;
    free(s);
    return val;
}
int isEmpty(const pileFIFO* pile){
    if(pile->sommet == NULL)
        return 1;
    return 0;
}
void vider(pileFIFO* pile){
    while(isEmpty(pile) == 1)
        pop(pile);
    pile->sommet = NULL;
}

int getSommetValue(pileFIFO* pile){
    if(pile != NULL)
        if(pile->sommet != NULL){
            return pile->sommet->value;
        }
    return -1;
}

int getValueAt(maillon* mail, int pos){
    if(mail == NULL || pos < 0)
        return -1;
    if(pos == 0){
        return mail->value;
    }else
        return getValueAt(mail->next, pos - 1);
}