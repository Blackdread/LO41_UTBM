//
//  main.c
//  LO41
//
//  Created by yoann on 02/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>

#include "Robots.h"
#include "anneauCircu.h"
#include "ProducteurComposant.h"
#include "SortieProduit.h"
#include "FactoryRobot.h"

#define NB_TH 9
pthread_t tid[NB_TH];
robot* r[6];

void fin();
void gererChoix();

void traitantC(int n){
    printf("TraitantC\n");
    
    fin();
}

int main(int argc, const char * argv[])
{
    srand((unsigned int)time(NULL));
    int num;

    signal(SIGINT,traitantC);
    signal(SIGSTOP,traitantC);
    
    /* Initialisation des conditions et des mutex */
    initAnneau();
    initProducteur();
    initSortieProduit();
    
    //robot *r = creerRobot(R1);
    //*
    r[0] = creerRobot(R1);
    //*
    r[1] = creerRobot(R2);
    r[2] = creerRobot(R3);
    r[3] = creerRobot(R4);
    r[4] = creerRobot(R5);
    r[5] = creerRobot(R6);
    //*/
    
    /* Juste pour des tests en changeant le mode des robots
    changerModeRobot(MODE_DEGRADE, r[0]);
    //changerModeRobot(MODE_DEGRADE, r[1]);
    //changerModeRobot(MODE_DEGRADE, r[2]);
    //changerModeRobot(MODE_DEGRADE, r[3]);
    // r5 et r6 n'ont pas de mode degrade (en ont un mais il est vide donc...)
    //*/
	/* creation des threads */
    //for(num=0;num<NB_TH;num++)
	//pthread_create(&tid[0], NULL, ******, NULL);
    pthread_create(&tid[0], NULL, (void*)th_tournerAnneau, NULL);
    pthread_create(&tid[1], NULL, (void*)th_creerComposantEtAjoutDansAnneau, NULL);
    pthread_create(&tid[2], NULL, (void*)th_verifSortieProduit, NULL);
    
    void* arg[] = {(void*)R1,r[0]};
    pthread_create(&tid[3], NULL, (void*)th_robot, arg);
    //*
    void* arg1[] = {(void*)R2,r[1]};
    pthread_create(&tid[4], NULL, (void*)th_robot, arg1);
    void* arg2[] = {(void*)R3,r[2]};
    pthread_create(&tid[5], NULL, (void*)th_robot, arg2);
    void* arg3[] = {(void*)R4,r[3]};
    pthread_create(&tid[6], NULL, (void*)th_robot, arg3);
    void* arg4[] = {(void*)R5,r[4]};
    pthread_create(&tid[7], NULL, (void*)th_robot, arg4);
    void* arg5[] = {(void*)R6,r[5]};
    pthread_create(&tid[8], NULL, (void*)th_robot, arg5);
    //*/
    printAnneau();
    usleep(400000);
    printAnneau();
    //usleep(600000);
    //printAnneau();
    
    // Juste pour afficher l'anneau
    /*
    int count = 0;
    do{
        usleep(50000);
        printAnneau();
    }while(count < 20);
    printf("afficher anneau fini");
    //*/
    
    // Juste pour afficher entierement la chaine de montage sous une forme d'interface (sera fait seulement a la fin si tout marche)
    // le probleme est que printf n'est pas synchronise donc l'affichage n'est pas tjr super...
    // ***************************
    // AUCUNE SYNCHRO EST FAITE SUR l'acces des variables, c'est juste un affichage
    // ***************************
    //*
    int k;
    for(k=0;k<10;k++){
        printf("     R6   \n");
        printf("  C%d C%d C%d  \n",r[5]->composant[0],r[5]->composant[1],r[5]->composant[2]);
        printf("                    14 %d     \n",bufComposantOuProduit[14]);
        printf("                                   R5 C%d C%d C%d\n",r[4]->composant[0],r[4]->composant[1],r[4]->composant[2]);
        printf("           15 %d                 13 %d\n",bufComposantOuProduit[15],bufComposantOuProduit[13]);
        printf("                                \n");
        printf("                                  11 %d  R4 C%d C%d C%d\n",bufComposantOuProduit[0],r[3]->composant[0],r[3]->composant[1],r[3]->composant[2]);
        printf("                                \n");
        printf("         0 %d                         10 %d\n",bufComposantOuProduit[0],bufComposantOuProduit[10]);
        printf("                                \n");
        printf("  %d => 1 %d                             9 %d   R3 C%d C%d C%d\n",resteTIlComposant(),bufComposantOuProduit[1],bufComposantOuProduit[9],r[3]->composant[0],r[3]->composant[1],r[3]->composant[2]);
        printf("                                \n");
        printf("         2 %d                        8 %d\n",bufComposantOuProduit[2],bufComposantOuProduit[8]);
        printf("                                \n");
        printf("     %d <=  3 %d                   7 %d  R2 C%d C%d C%d\n",nbProduitSortie,bufComposantOuProduit[3],bufComposantOuProduit[7],r[2]->composant[0],r[2]->composant[1],r[2]->composant[2]);
        printf("                                \n");
        printf("             4 %d               6 %d\n",bufComposantOuProduit[4],bufComposantOuProduit[6]);
        printf("                                \n");
        printf("                    5 %d\n",bufComposantOuProduit[5]);
        printf("                   R1 \n");
        printf("               C%d C%d C%d  \n",r[0]->composant[0],r[0]->composant[1],r[0]->composant[2]);
        usleep(10000);
    }
    //*/
    
    //*
    char ppp[10];
    int go=1;
    while(go==1){
        scanf("%9s",ppp);
        printf("la chaine vaut=%s\n",ppp);
        if(strcmp(ppp,"stop")==0){
            // a supprimer peut-etre et garder fin (donc ce qui suit ce while devrait etre enleve)
            printf("arretForce\n");
            go=0;
        }else if(strcmp(ppp,"fin")==0){
            fin();
        }else
            gererChoix(ppp);
    }
    //*/
    
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    printAnneau();
    printVoidBuf(&produitsSortis);
    libererBuf(&produitsSortis);
    
    // Free des robots
    for(num=0;num<6;num++)
        free(r[num]);
	//*
	// attente de la fin des threads
    for(num=3;num<NB_TH;num++)
        pthread_join(tid[num],NULL);
     
	
    // libÈration des ressources
    for(num=0;num<NB_TH;num++)
        pthread_detach(tid[num]);
    //*/
    printf("fin main / nb de produit sortie=%d",nbProduitSortie);
    return 0;
}

void gererChoix(char *ppp){
    if(strcmp(ppp,"r1s")==0){
        r[0]->continuer = 0;
    }else if(strcmp(ppp,"r2s")==0){
        r[1]->continuer = 0;
    }else if(strcmp(ppp,"r3s")==0){
        r[2]->continuer = 0;
    }else if(strcmp(ppp,"r4s")==0){
        r[3]->continuer = 0;
    }else if(strcmp(ppp,"r5s")==0){
        r[4]->continuer = 0;
    }else if(strcmp(ppp,"r6s")==0){
        r[5]->continuer = 0;
    }else if(strcmp(ppp,"r1m")==0){
        if(r[0]->mode == MODE_NORMAL)
            r[0]->mode = MODE_DEGRADE;
        else
            r[0]->mode = MODE_NORMAL;
    }else if(strcmp(ppp,"r2m")==0){
        if(r[1]->mode == MODE_NORMAL)
            r[1]->mode = MODE_DEGRADE;
        else
            r[1]->mode = MODE_NORMAL;
    }else if(strcmp(ppp,"r3m")==0){
        if(r[2]->mode == MODE_NORMAL)
            r[2]->mode = MODE_DEGRADE;
        else
            r[2]->mode = MODE_NORMAL;
    }else if(strcmp(ppp,"r4m")==0){
        if(r[3]->mode == MODE_NORMAL)
            r[3]->mode = MODE_DEGRADE;
        else
            r[3]->mode = MODE_NORMAL;
    }
}

void fin(){
    r[0]->continuer = 0;
    r[1]->continuer = 0;
    r[2]->continuer = 0;
    r[3]->continuer = 0;
    r[4]->continuer = 0;
    r[5]->continuer = 0;
    
    continuerProducteur = 0;
    continuerSortie = 0;
    
    continuerAnneau = 0;
    
    
    // ===============
    // Il faudrait faire une fonction qui vide l'anneau et dealloue les produit qui sont dans la memoire
    // ici c'est fait vite en mettant le compteur a 0
    nbElementDansBuffer = 0;
    
    // ===============
    
    
    // *************
    // Debloque tout si en attente de condition
    pthread_cond_broadcast(&cond_anneauATourner);
    pthread_cond_signal(&cond_anneauAttenteAcces);
    usleep(1000);
    pthread_cond_broadcast(&cond_anneauATourner);
    pthread_cond_signal(&cond_anneauAttenteAcces);
    usleep(1000);
    pthread_cond_broadcast(&cond_anneauATourner);
    pthread_cond_signal(&cond_anneauAttenteAcces);
    usleep(3000);
    pthread_cond_broadcast(&cond_anneauATourner);
    pthread_cond_signal(&cond_anneauAttenteAcces);
    usleep(3000);
    pthread_cond_broadcast(&cond_anneauATourner);
    pthread_cond_signal(&cond_anneauAttenteAcces);
    // *************
    
    libererBuf(&produitsSortis);
    int num;
    // Free des robots
    for(num=0;num<6;num++)
        free(r[num]);
    
    // libÈration des ressources
    for(num=0;num<NB_TH;num++)
        pthread_detach(tid[num]);
    printf("fin fonction fin / nb de produit sortie=%d",nbProduitSortie);
    
    exit(EXIT_SUCCESS);
}

