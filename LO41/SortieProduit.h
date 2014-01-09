//
//  SortieProduit.h
//  LO41
//
//  Created by yoann on 07/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__SortieProduit
#define LO41__SortieProduit

#include "voidBuf.h"
#include <pthread.h>
#include "anneauCircu.h"
#include "ProducteurComposant.h"

int continuerSortie;

int nbProduitSortie;

// Pour le moment je choisi de ne faire sortir que des produits
voidBuf produitsSortis;

void initSortieProduit();

void th_verifSortieProduit();

#endif 
