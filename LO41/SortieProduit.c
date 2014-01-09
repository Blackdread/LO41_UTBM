//
//  SortieProduit.c
//  LO41
//
//  Created by yoann on 07/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "SortieProduit.h"

void initSortieProduit(){
    initBuf(&produitsSortis, 2);
    nbProduitSortie = 0;
    continuerSortie = 1;
}

void th_verifSortieProduit(){
    while(continuerSortie == 1){
        pthread_mutex_lock(&mutex_anneau);
        // On attend tjr que l'anneau est tournee
        pthread_cond_wait(&cond_anneauATourner, &mutex_anneau);
        nbElementQuiAccedeAnneau++;
        
        pthread_mutex_unlock(&mutex_anneau);
        if(getPositionType(POS_C_P_SORTIE) == TYPE_PROD){
           // produit* prod = (produit*)prendreElement(POS_C_P_SORTIE);
           // appendBuf(&produitsSortis, (void*)prod);
            produit* prod = (produit*)getPointeur(POS_C_P_SORTIE);
            if(isProduitDone(prod)){
                printf("Un produit a ete sortie Prod%d et total =%d\n",prod->numProduit, nbProduitSortie);
                
                // *********************************
                // pour des raisons de memoire vive, soit on stocke les produits soit on les supprime
                
                //On garde mais attention a la memoire !
                //appendBuf(&produitsSortis, prendreElement(POS_C_P_SORTIE));
                
                // On supprime et liberation de la memoire
                free(prendreElement(POS_C_P_SORTIE));
                // *********************************
                
                nbProduitSortie++;
            }else
                printf("Produit non sortie Prod%d\n",prod->numProduit);
        }else
            printf("Produit non sortie car s'en n'est pas un :)\n");
        
        pthread_mutex_lock(&mutex_anneau);
        nbElementQuiAccedeAnneau--;
        pthread_cond_signal(&cond_anneauAttenteAcces);
        pthread_mutex_unlock(&mutex_anneau);
    }
    printf("Thread verif Sortie produits terminer\n");
}