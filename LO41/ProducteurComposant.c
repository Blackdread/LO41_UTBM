//
//  ProducteurComposant.c
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "ProducteurComposant.h"


void initProducteur(){
    nbC1 = 3*10;
    nbC2 = 3*10;
    nbC3 = 1*4000;
    nbC4 = 2*10;
    
    continuerProducteur = 1;
}

int resteTIlComposant(){
    if(nbC1 == 0 && nbC2 == 0 && nbC3 == 0 && nbC4 == 0)
        return 0;
    return 1;
}

int recupererUnComposant(){
    // ATTENTION peut boucler a l'infini si y a plus de composant
    int a;
    int c = -1;
    do{
        a =  (1 + (rand () % (4-1+1)));
        switch (a) {
            case 1:
                if(nbC1 > 0){
                    c = C1;
                    nbC1--;
                }
                break;
            case 2:
                if(nbC2 > 0){
                    c = C2;
                    nbC2--;
                }
                break;
            case 3:
                if(nbC3 > 0){
                    c = C3;
                    nbC3--;
                }
                break;
            case 4:
                if(nbC4 > 0){
                    c = C4;
                    nbC4--;
                }
                break;
                
            default:
                if(nbC1 > 0){
                    c = C1;
                    nbC1--;
                }
                break;
        }
    }while(c==-1);
    return c;
}

void th_creerComposantEtAjoutDansAnneau(){
    while(resteTIlComposant() == 1 && continuerProducteur == 1){
        pthread_mutex_lock(&mutex_anneau);
        // On attend tjr que l'anneau est tournee
        pthread_cond_wait(&cond_anneauATourner, &mutex_anneau);
        while(nbElementDansBuffer >= TAILLE_ANNEAU_MAX-6){
            // Il faut absolument laisser un minimum de place libre car il y a congestion du aux robots qui ont
            // des produits -> si on laisse trop peu de place, 1...2..ou 3 robots posent leur produit mais les 4..5..
            // ou 6 ont aussi un produit a poser sauf que l'anneau est plein. Malheuresement les produits que les robots 1,2 et 3 ont deposer ne sont pas fini et ils doivent passer dans les robots 4,5 ou 6 => on a donc un soucis pour continuer la chaine. => La chaine tourne a l'infini !
            // C'est pourquoi il faut laisser un minimum de place, j'ai choisi 6 car 6 robots (avant je laissé seulement 2 places libres) / on peut supposer que 4 places devraient suffir mais bon...
            
            printf("Producteur composant dormir while\n");
            // on s'endort pour ne pas remplir totalement la chaine
            pthread_cond_wait(&cond_anneauATourner, &mutex_anneau);
        }
        nbElementQuiAccedeAnneau++;
        //printf("Producteur composant acces\n");
        pthread_mutex_unlock(&mutex_anneau);
        if(isPostionBufLibre(POS_C_ENTREE) == 1){
            int aa=recupererUnComposant();
            ajouterElement((void*)aa, POS_C_ENTREE, TYPE_COMP);
            printf("composant ajouter %d\n",aa);
        }else
            printf("composant non ajouter car case non libre\n");
        
        pthread_mutex_lock(&mutex_anneau);
        nbElementQuiAccedeAnneau--;
        pthread_cond_signal(&cond_anneauAttenteAcces);
        pthread_mutex_unlock(&mutex_anneau);
        //usleep(200000);
    }
    printf("Thread Producteur Composant terminer\n");
}