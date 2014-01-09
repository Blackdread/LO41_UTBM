//
//  FactoryProduit.c
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "FactoryProduit.h"


produit* creerProduit(int numProduit){
    produit *prod = (produit*)malloc(sizeof(produit));
    
    switch(numProduit){
        case Prod1:
            prod->numProduit = Prod1;
            prod->composant = C1;
            prod->nbCNecessaire = 3;
            
            push(&(prod->listeDesOperationRequired), Op1);
            push(&(prod->listeDesOperationRequired), Op2);
            push(&(prod->listeDesOperationRequired), Op3);
            push(&(prod->listeDesOperationRequired), Op5);
            
            break;
        case Prod2:
            prod->numProduit = Prod2;
            prod->composant = C2;
            prod->nbCNecessaire = 3;
            
            push(&(prod->listeDesOperationRequired), Op2);
            push(&(prod->listeDesOperationRequired), Op4);
            push(&(prod->listeDesOperationRequired), Op1);
            push(&(prod->listeDesOperationRequired), Op6);
            break;
        case Prod3:
            prod->numProduit = Prod3;
            prod->composant = C3;
            prod->nbCNecessaire = 1;
            
            push(&(prod->listeDesOperationRequired), Op3);
            push(&(prod->listeDesOperationRequired), Op1);
            push(&(prod->listeDesOperationRequired), Op5);
            push(&(prod->listeDesOperationRequired), Op1);
            push(&(prod->listeDesOperationRequired), Op3);
            break;
        case Prod4:
            prod->numProduit = Prod4;
            prod->composant = C4;
            prod->nbCNecessaire = 2;
            
            push(&(prod->listeDesOperationRequired), Op4);
            push(&(prod->listeDesOperationRequired), Op6);
            push(&(prod->listeDesOperationRequired), Op1);
            break;
        default:
            prod->numProduit = Prod1;
            prod->composant = C1;
            prod->nbCNecessaire = 3;
            
            push(&(prod->listeDesOperationRequired), Op1);
            push(&(prod->listeDesOperationRequired), Op2);
            push(&(prod->listeDesOperationRequired), Op3);
            push(&(prod->listeDesOperationRequired), Op5);
            break;
    }
    return prod;
}