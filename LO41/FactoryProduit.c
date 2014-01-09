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
    
    initPileFIFO(&(prod->listeDesOperationRequired));
    
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
            // default Prod1 mais on pourrait mettre null ou je ne sais quoi...
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

int hasEnoughComposantToDoProd(int nb, int compo){
    switch (compo) {
        case C1:
            if(nb==3)
                return Prod1;
            break;
        case C2:
            if(nb==3)
                return Prod2;
            break;
        case C3:
            if(nb==1)
                return Prod3;
            break;
        case C4:
            if(nb==2)
                return Prod4;
            break;
    }
    return 0;
}