//
//  FactoryProduit.h
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__FactoryProduit
#define LO41__FactoryProduit

#include <stdio.h>
#include "Produit.h"
#include "Composant.h"
#include "Operation.h"
#include "PileFIFO.h"

#define Prod1 1
#define Prod2 2
#define Prod3 3
#define Prod4 4

produit* creerProduit(int numProduit);

#endif
