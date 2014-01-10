//
//  FactoryRobot.c
//  LO41
//
//  Created by yoann on 07/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#include "FactoryRobot.h"

robot* creerRobot(int numRobot){
    
    robot *rob = (robot*)malloc(sizeof(robot));
    rob->mode = MODE_NORMAL;
    int i;
    for(i=0;i<TAILLE_MAX_NB_OP_DEGRADE;i++)
        rob->opDegrade[i] = -1;
    
    for(i=0;i<TAILLE_MAX_NB_COMP_GARDE;i++)
        rob->composant[i] = -1;
    
    rob->produit = NULL;
    
    rob->continuer = 1;
    
    switch(numRobot){
        case R1:
            rob->opNormal = Op1;
            
            rob->nbOpDegrade = 3;
            rob->opDegrade[0] = Op1;
            rob->opDegrade[1] = Op2;
            rob->opDegrade[2] = Op5;
            break;
        case R2:
            rob->opNormal = Op2;
            
            rob->nbOpDegrade = 2;
            rob->opDegrade[0] = Op2;
            rob->opDegrade[1] = Op1;
            break;
        case R3:
            rob->opNormal = Op3;
            
            rob->nbOpDegrade = 3;
            rob->opDegrade[0] = Op3;
            rob->opDegrade[1] = Op4;
            rob->opDegrade[2] = Op6;
            break;
        case R4:
            rob->opNormal = Op4;
            
            rob->nbOpDegrade = 2;
            rob->opDegrade[0] = Op4;
            rob->opDegrade[1] = Op3;
            break;
        case R5:
            rob->opNormal = Op5;
            
            rob->nbOpDegrade = 0;
            break;
        case R6:
            rob->opNormal = Op6;
            
            rob->nbOpDegrade = 0;
            break;
        default:
            
            break;
    }
    return rob;
}