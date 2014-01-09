//
//  Produit.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__Produit
#define LO41__Produit

#include "PileFIFO.h"

typedef struct _produit{
    int numProduit;//juste pour l'identifier
    
    // Ici on ne cherche pas a stocker differents composant pour creer un produit
    // car le sujet montre que pour un produit on a besoin que d'un seul type de composant
    int nbCNecessaire;
    int composant;
    
    // le 1er element est l'operation a faire prochainement
    pileFIFO listeDesOperationRequired;
    
}produit;

int isProduitT0Done(const produit *prod);
int isProduitDone(const produit *prod);

int popNextOp(produit *prod);

// n'enleve pas l'operation
int getNextOp(produit *prod);

#endif
