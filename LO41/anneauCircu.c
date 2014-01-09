//
//  anneauCircu.c
//  LO41
//
//  Created by yoann on 06/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "anneauCircu.h"

void initAnneau(){
    pthread_cond_init(&cond_anneauATourner, NULL);
    pthread_cond_init(&cond_anneauAttenteAcces, NULL);
    
	pthread_mutex_init(&mutex_anneau,NULL);
    
    int i;
    for(i=0;i<TAILLE_ANNEAU_MAX;i++){
        bufComposantOuProduit[i] = TYPE_RIEN;
        bufferAnneau[i] = NULL;
    }
    nbElementDansBuffer = 0;
    nbElementQuiAccedeAnneau = 0;
    
    continuerAnneau = 1;
}

void th_tournerAnneau(){
    while(continuerAnneau == 1){

        pthread_mutex_lock(&mutex_anneau);
        while(nbElementQuiAccedeAnneau != 0){
            printf("Anneau mis en attente\n");
            pthread_cond_wait(&cond_anneauAttenteAcces, &mutex_anneau);
        }
        
        // tourne les elements
        int i;
        int tmp = bufComposantOuProduit[TAILLE_ANNEAU_MAX-1];
        void* tmp2 = bufferAnneau[TAILLE_ANNEAU_MAX-1];
        
        for(i=TAILLE_ANNEAU_MAX-1;i>0;i--){
            bufComposantOuProduit[i] = bufComposantOuProduit[i-1];
            bufferAnneau[i] = bufferAnneau[i-1];
        }
        bufComposantOuProduit[0] = tmp;
        bufferAnneau[0] = tmp2;
        //printf("Anneau a tourner\n");
        
        pthread_cond_broadcast(&cond_anneauATourner);
        pthread_mutex_unlock(&mutex_anneau);
        //usleep(100000);
    }
    printf("Thread Anneau terminer\n");
}

int isPostionBufLibre(int pos){
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    if(bufComposantOuProduit[pos] == TYPE_RIEN){
        printf("Pos libre\n");
        nbElementQuiAccedeAnneau--;
        pthread_mutex_unlock(&mutex_anneau);
        return 1;
    }
    printf("Pos non libre\n");
    
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);
    return 0;
}

int getPositionType(int pos){
    // Les nbElementQui... ne sont pas forcement utile ici
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    int ret = bufComposantOuProduit[pos];
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    //pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);
    return ret;
}

int getPositionDuRobot(int numRobot){
    switch (numRobot) {
        case R1:
            return POS_ROBOT_1;
            break;
        case R2:
            return POS_ROBOT_2;
            break;
        case R3:
            return POS_ROBOT_3;
            break;
        case R4:
            return POS_ROBOT_4;
            break;
        case R5:
            return POS_ROBOT_5;
            break;
        case R6:
            return POS_ROBOT_6;
            break;
        default:
            printf("Erreur position du robot avec numRobot\n");
            return -1;
            break;
    }
}

void* getPointeur(int pos){
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    void* ret = bufferAnneau[pos];
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    //pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);
    return ret;
}


void* prendreElement(int positionBuffer){
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    void* elem = bufferAnneau[positionBuffer];
    nbElementDansBuffer--;
    
    bufComposantOuProduit[positionBuffer] = TYPE_RIEN;
    bufferAnneau[positionBuffer] = NULL;
    
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);
    return elem;
}

void ajouterElement(void *elem,int positionBuffer,int type){
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    nbElementDansBuffer++;
    
    switch(type){
        case TYPE_PROD:
            bufComposantOuProduit[positionBuffer] = TYPE_PROD;
            break;
        case TYPE_COMP:
            bufComposantOuProduit[positionBuffer] = TYPE_COMP;
            break;
    }
    bufferAnneau[positionBuffer] = elem;
    
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);
}

void printAnneau(){
    pthread_mutex_lock(&mutex_anneau);
    nbElementQuiAccedeAnneau++;
    int i;
    for(i=0;i<TAILLE_ANNEAU_MAX;i++){
        if(bufComposantOuProduit[i] == TYPE_PROD)
            printf("prod%d i=%d \n",((produit*)bufferAnneau[i])->numProduit,i);
        else if(bufComposantOuProduit[i] == TYPE_COMP)
            printf("comp%d i=%d \n",(int)bufferAnneau[i],i);
        else
            printf("rien i=%d \n",i);
    }
    printf("\n");
    nbElementQuiAccedeAnneau--;
    // mettre signal ?
    pthread_cond_signal(&cond_anneauAttenteAcces);
    pthread_mutex_unlock(&mutex_anneau);

}