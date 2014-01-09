//
//  Produit.c
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "Produit.h"


int isProduitT0Done(const produit *prod){
    if(prod->nbCNecessaire == 0)
        return 1;
    return 0;
}
int isProduitDone(const produit *prod){
    return isEmpty(&(prod->listeDesOperationRequired));
}

int popNextOp(produit *prod){
    if(isProduitDone(prod) == 0){
        return pop(&(prod->listeDesOperationRequired));
    }
    return -1;
}

int getNextOp(produit *prod){
    return getSommetValue(&(prod->listeDesOperationRequired));
}