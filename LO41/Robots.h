//
//  Robots.h
//  LO41
//
//  Created by yoann on 02/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41_Robots_h
#define LO41_Robots_h

//* ca se trouve ici car sinon dans FactoryRobot j'avais une inclusion circulaire
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
//*/
#define TAILLE_MAX_NB_OP_DEGRADE 4
#define TAILLE_MAX_NB_COMP_GARDE 3

#define MODE_NORMAL 1
#define MODE_DEGRADE 2

#include <stdio.h>
#include <stdlib.h>
#include "Produit.h"
#include "Operation.h"
#include "Composant.h"
#include "anneauCircu.h"
#include "FactoryProduit.h"


typedef struct _robot{
    int continuer; // ajouter a la fin, c'est juste pour arreter le thread a partir du main
    int mode;
    
    int opNormal;
    
    // Nb d'element => Ou remplacer par un pointeur et garder le nb d'element de ce tableau
    int nbOpDegrade;
    int opDegrade[TAILLE_MAX_NB_OP_DEGRADE]; // taille statique ou pointeur
    
    // peut posseder un produit
    produit* produit;
    // peut posseder des composants => supposer identique car dans le sujet les produits commencent avec un seul type de composant
    int composant[TAILLE_MAX_NB_COMP_GARDE];
    
}robot;


void changerModeRobot(int mode, robot *robot);

// Regarde si le produit passer en parametre peut etre utiliser par le robot (si le robot peut faire l'operation)
int isProduitNextOpCanBeDone(produit *prod, robot *robot);

// renvoie 1 si oui. Regarde si ce composant est utile au robot ce qui signifie si ce robot peut creer un produit a partir de ce composant, ne prends que les composants d'un meme type si 1 type a deja etait pris.
int isComposantUsefulToBeTaken(int composant, robot *robot);

// renvoie 1 si le robot a deja des composants de stocke
int isRobotAlreadyHaveComposant(robot *robot);

// renvoie le nb de composant
int countNbComposant(robot *robot);

// renvoie 1 si le robot possede un produit a remettre sur l'anneau
int isRobotNeedToGiveProduit(robot *robot);

// renvoie 1 si le robot est plein de composants
int isRobotFullOfComposant(robot *robot);

// ajoute le composant -> attention a la limite en taille -> si ça depasse le composant est perdu
void ajouterComposant(int composant, robot *robot);

// supprime les composants
void enleverLesComposants(robot *robot);

// supprime un composant de type donne (part de la fin à 0)
void enleverLeComposant(int composant, robot *robot);


// Num robot et arg[1] un pointeur sur un robot
void th_robot(void* arg[]);
//void th_robot(void *numRob, robot *robot);

// la fonction qui enleve les composants, creer le produit puis...
void procederALaCreationDuProduit(int numProd, robot *robot);

// fonction qui fais les operations sur le produit (faire l'op suivante de la suivante si le robot peut le faire ? (robot en mode degrade donc))
void procederOpSuivanteDuProduit(robot *robot);

// On remet sur l'anneau le produit (toute verification faite cette fonction
void procederRemiseDuProduitSurAnneau(int positionSurAnneau, robot *robot);

#endif
