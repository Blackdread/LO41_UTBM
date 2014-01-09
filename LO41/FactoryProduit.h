//
//  FactoryProduit.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__FactoryProduit
#define LO41__FactoryProduit

#include "Produit.h"
#include "Composant.h"
#include "Operation.h"

#define Prod1 1
#define Prod2 2
#define Prod3 3
#define Prod4 4

produit* creerProduit(int numProduit);

// renvoie le numDuProduit si suffisament de composant pour le creer / fonction special du au sujet et un produit n'a besoin que d'un seul type de composant / sinon renvoie 0
int hasEnoughComposantToDoProd(int nb, int compo);

#endif
