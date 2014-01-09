//
//  ProducteurComposant.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__ProducteurComposant
#define LO41__ProducteurComposant

#include "Composant.h"
#include <pthread.h>
#include "anneauCircu.h"

int continuerProducteur;

// Le nb de composant au total qui seront envoye
int nbC1;
int nbC2;
int nbC3;
int nbC4;

void initProducteur();

// Renvoie 1 s'il reste des composants a envoyer
int resteTIlComposant();
int recupererUnComposant();

void th_creerComposantEtAjoutDansAnneau();
    
#endif
