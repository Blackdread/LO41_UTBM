//
//  anneauCircu.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__anneauCircu
#define LO41__anneauCircu

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Robots.h"
#include "Produit.h"
//#include "FactoryRobot.h"
#include "ProducteurComposant.h"

#define TAILLE_ANNEAU_MAX 16

#define POS_C_ENTREE 1
#define POS_C_P_SORTIE 3
#define POS_ROBOT_1 5
#define POS_ROBOT_2 7
#define POS_ROBOT_3 9
#define POS_ROBOT_4 11
#define POS_ROBOT_5 12
#define POS_ROBOT_6 14

#define TYPE_PROD 50
#define TYPE_COMP 51
#define TYPE_RIEN 0

pthread_mutex_t mutex_anneau;
// Permet de reveiller robots et autres en attente
pthread_cond_t cond_anneauATourner;

// l'anneau attend tant que les elements continue d'acceder a l'anneau
pthread_cond_t cond_anneauAttenteAcces;

void initAnneau();

int bufComposantOuProduit[TAILLE_ANNEAU_MAX]; // 51 c et 50 Prod <= ce n'est pas forcement utile car on peut supposer que tout les pointeur de type produit auront une valeur superieur à 1000 donc on pourrait juste tester la valeur du pointeur, mais qui a faire bien je mets ce 2eme tableau
void *bufferAnneau[TAILLE_ANNEAU_MAX];

void* prendreElement(int positionBuffer);
void ajouterElement(void *elem,int positionBuffer,int type);
int isPostionBufLibre(int pos);
int getPositionType(int pos);

// renvoie la position du robot sur le buffer
int getPositionDuRobot(int numRobot);

// Ne pas trop utiliser cette fonction
void* getPointeur(int pos);

int continuerAnneau;

int nbElementDansBuffer;

int nbElementQuiAccedeAnneau;
//int nbElementQuiVeulentAccedeAnneau;

void printAnneau();

void th_tournerAnneau();

#endif