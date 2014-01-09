//
//  FactoryRobot.h
//  LO41
//
//  Created by yoann on 07/12/13.
//  Copyright (c) 2013 yoann. All rights reserved.
//

#ifndef LO41__FactoryRobot
#define LO41__FactoryRobot

#include "Robots.h"

/* Pour le moment, je commente car j'ai une inclusion circulaire en mettant ca la
 // C'est donc mis dans Robots.h
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
//*/

robot * creerRobot(int numRobot);

#endif
