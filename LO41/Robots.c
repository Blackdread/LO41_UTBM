//
//  Robots.c
//  LO41
//
//  Created by yoann on 02/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "Robots.h"

void changerModeRobot(int mode, robot *robot){
    robot->mode = mode;
}

int isProduitNextOpCanBeDone(produit *prod, robot *robot){
    if(robot->mode == MODE_NORMAL){
        //if(getSommetValue(&((prod->listeDesOperationRequired))) == robot->opNormal)
        if(getNextOp(prod) == robot->opNormal)
            return 1;
    }else{
        int i;
        //while((a = getValueAt((&prod->listeDesOperationRequired)->sommet, ii)) != -1 ){
            for(i=0;i<robot->nbOpDegrade; i++){
                if(getSommetValue(&prod->listeDesOperationRequired) == robot->opDegrade[i])
                    return 1;
            }
           // ii++;
        //}
        return 0;
    }
    return 0;
}

int isComposantUsefulToBeTaken(int composant, robot *robot){
    if(robot->mode == MODE_NORMAL){
        switch (robot->opNormal) {
            case Op1:
                if(composant == C1)
                    return 1;
                break;
            case Op2:
                if(composant == C2)
                    return 1;
                break;
            case Op3:
                if(composant == C3)
                    return 1;
                break;
            case Op4:
                if(composant == C4)
                    return 1;
                break;
            default:
                return 0;
                break;
        }
    }else{
        int i;
        for(i=0;i<robot->nbOpDegrade; i++)
            switch (robot->opDegrade[i]) {
                case Op1:
                    if(composant == C1)
                        return 1;
                    break;
                case Op2:
                    if(composant == C2)
                        return 1;
                    break;
                case Op3:
                    if(composant == C3)
                        return 1;
                    break;
                case Op4:
                    if(composant == C4)
                        return 1;
                    break;
            }
    }
    return 0;
}

int isRobotAlreadyHaveComposant(robot *robot){
    int i;
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE; i++)
        if(robot->composant[i] != -1)
            return 1;
    return 0;
}

int countNbComposant(robot *robot){
    int i, somme=0;
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE; i++)
        if(robot->composant[i] != -1)
            somme++;
    return somme;
}

int isRobotNeedToGiveProduit(robot *robot){
   // return ((robot->produit == NULL) ? 0 : 1);
    if(robot->produit == NULL)
        return 0;
    return 1;
}

int isRobotFullOfComposant(robot *robot){
    int i;
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE; i++)
        if(robot->composant[i] == -1)
            return 0;
    return 1;
}

void ajouterComposant(int composant, robot *robot){
    int i;
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE; i++)
        if(robot->composant[i] == -1){
            robot->composant[i] = composant;
            break;
        }
}

void enleverLesComposants(robot *robot){
    int i;
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE; i++)
        robot->composant[i] = -1;
}

void enleverLeComposant(int composant, robot *robot){
    int i;
    for(i = TAILLE_MAX_NB_COMP_GARDE-1 ; i>=0 ; i--)
        if(robot->composant[i] == composant){
            robot->composant[i] = -1;
            break;
        }
}

void procederALaCreationDuProduit(int numProd, robot *robot){
    printf("sleep puis creation prod%d\n",numProd);
    // rand maniere simple rand() % N
    usleep(10000 * (rand() % 10));
    enleverLesComposants(robot);
    robot->produit = creerProduit(numProd);
    printf("resultat produit:%d %d %d\n",robot->produit->composant, robot->produit->nbCNecessaire, robot->produit->numProduit);
    
}

void procederOpSuivanteDuProduit(robot *robot){
    if(isProduitNextOpCanBeDone(robot->produit, robot) == 1){
        printf("sleep puis procede a l'op\n");
        // rand maniere simple rand() % N
        usleep(10000 * (rand() % 10));
        pop(&robot->produit->listeDesOperationRequired);
        
        // On fait recursif
        procederOpSuivanteDuProduit(robot);
    }
    return;
}

void procederRemiseDuProduitSurAnneau(int positionSurAnneau, robot *robot){
    if(isRobotNeedToGiveProduit(robot) == 1){
         printf("produit avant d'etre remis:%d %d %d et rob %d\n",robot->produit->composant, robot->produit->nbCNecessaire, robot->produit->numProduit, robot->opNormal);
        ajouterElement((void*)robot->produit, positionSurAnneau, TYPE_PROD);
        robot->produit = NULL;
    }else
        printf("erreur remise du produit");
}

void th_robot(void* arg[]){
//void th_robot(void *numRob, robot *robot){
    robot *robot = arg[1];
    int numRobot = (int)arg[0];
    
    while(robot->continuer == 1){
        pthread_mutex_lock(&mutex_anneau);
        // On attend tjr que l'anneau est tournee
        pthread_cond_wait(&cond_anneauATourner, &mutex_anneau);
        nbElementQuiAccedeAnneau++;
        
        // ******************* ALGO *******************
        // regarder si on veut prendre des composants
        // regarder le composant -> on le prends ?
        // on prend le composants si on a en a besoin pour creer un produit (produit qui a besoin de plusieurs compo)
        // Besoin que de 1 composant -> ce composant nous est presente => on le prends et on creer le produit
        
        // regarder le produit -> possible de faire l'action ?
        // possible mais pas les composants, on atttends les prochains composants
        // possible et ce n'est pas la 1ere op donc on fait l'op
        // ******************* ALGO *******************
        
        
        int nbCompo = countNbComposant(robot);
        int numProdACreer = 0;
        //if(nbCompo > 0)
            numProdACreer = hasEnoughComposantToDoProd(nbCompo, robot->composant[0]);
        if(nbCompo > 0 && numProdACreer > 0 && isRobotNeedToGiveProduit(robot) == 0){
            // supposition -> un seul type de composant
            nbElementQuiAccedeAnneau--;
            pthread_cond_signal(&cond_anneauAttenteAcces);
            pthread_mutex_unlock(&mutex_anneau);
            
            printf("Robot%d procede creation produit\n", numRobot);
            procederALaCreationDuProduit(numProdACreer, robot);
            
            continue;
        }else{
        
            pthread_mutex_unlock(&mutex_anneau);
            int typePos = getPositionType(getPositionDuRobot(numRobot));
            
            if(typePos == TYPE_COMP){
                int composantSurAnneau = (int)getPointeur(getPositionDuRobot(numRobot));
                
                // On ne peut pas encore creer de produit => on cherche a avoir les composants necessaires
                if(isRobotAlreadyHaveComposant(robot) == 1){
                    // Un produit n'a besoin que d'1 type de composant donc on ne va pas chercher a stocker differents composant
                    if(composantSurAnneau == robot->composant[0] && isRobotFullOfComposant(robot) == 0){
                        // on prend le composant
                        ajouterComposant((int)prendreElement(getPositionDuRobot(numRobot)), robot);
                        typePos = TYPE_RIEN;
                        printf("Robot%d pris composant %d 1er nb=%d\n", numRobot,composantSurAnneau,countNbComposant(robot));
                    }
                }else{
                    // on prend le composant seulement si utile pour ce robot
                    if(isRobotFullOfComposant(robot) == 0 && isComposantUsefulToBeTaken(composantSurAnneau,robot) == 1){
                        ajouterComposant((int)prendreElement(getPositionDuRobot(numRobot)), robot);
                        typePos = TYPE_RIEN;
                        printf("Robot%d pris composant %d 2eme nb=%d\n", numRobot,composantSurAnneau,countNbComposant(robot));
                    }
                }
            }else if(typePos == TYPE_PROD && isRobotNeedToGiveProduit(robot) == 0){
                produit* produitSurAnneau = (produit*)getPointeur(getPositionDuRobot(numRobot));
                if(isProduitNextOpCanBeDone(produitSurAnneau, robot) == 1){
                    // on peut faire l'operation
                    // regarder si on peut faire plusieurs op si on est en mode degrade, c bete de remettre le produit si on peut faire les 2 operations qui suivent
                    robot->produit = prendreElement(getPositionDuRobot(numRobot));
                    
                    pthread_mutex_lock(&mutex_anneau);
                    nbElementQuiAccedeAnneau--;
                    pthread_cond_signal(&cond_anneauAttenteAcces);
                    pthread_mutex_unlock(&mutex_anneau);
                    
                    printf("Robot%d procede OpSuivante\n", numRobot);
                    procederOpSuivanteDuProduit(robot);
                    
                    continue;
                }
            }
            
            
            // Pas sûr de garder ca dans ce else...a voir -> le but est de pouvoir remettre le produit si il est possible de le mettre car on a pris le composant qui etait sur l'anneau ou s'il y avait rien
            if(typePos == TYPE_RIEN){
                if(isRobotNeedToGiveProduit(robot) == 1){
                    // Poser le produit
                    procederRemiseDuProduitSurAnneau(getPositionDuRobot(numRobot), robot);
                    printf("Robot%d produit remis\n", numRobot);
                    //printAnneau();
                }
            }
        }
        //*
        if(robot->produit != NULL){
            printf("Robot%d stocke un produit%d\n",numRobot,robot->produit->numProduit);
            if(isRobotNeedToGiveProduit(robot)){
                printf("Et a besoin de donner produit / %d\n", nbElementDansBuffer);
                printAnneau();
            }
        }
        printf("Robot%d fin boucle et mode %d\n", numRobot, robot->mode);
        pthread_mutex_lock(&mutex_anneau);
        nbElementQuiAccedeAnneau--;
        pthread_cond_signal(&cond_anneauAttenteAcces);
        pthread_mutex_unlock(&mutex_anneau);
         //*/
    }
    if(robot->produit != NULL)
        free(robot->produit);
    printf("Thread robot%d terminer\n", numRobot);
}