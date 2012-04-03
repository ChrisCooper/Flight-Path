/*		DEFINITIONS.H

This header is included in ALL other files, it contains the include files, as well as all
definitions of structures, ENUMs, and #define statements.

*/

#include <stdio.h>               //Standard functions prototypes
#include <string.h>              //Prototypes related to strings
#include <math.h>              //Prototypes related to strings
#include <allegro.h>             //Allegro MACROs, defines, and prototypes
#include <algif.h>               //Used for support of gif files

#define OBJECT struct object     //Makes referring to the structure type "stuct object" more obvious

#define TEMP 3
#define BULLET 4
#define MISSILE 5
#define EXPLOSION 6
#define SMOKE 7
#define ENEMY 8

#define PI 3.1415



/*
SELECTIVE DECLARATIONS
The following two lines of code are used to prevent multiple definitions and ENUMS
*/
#ifndef SPQR_DEF                 //If SPQR_DEF has not been defined then...
#define SPQR_DEF                 //DefineS PQR_DEF


OBJECT{
       float x, y;
		 float rotation, velRotation;
		 float velX, velY;
		 float rotorPower, rocketPower;
		 int width, height;
       int maxHealth;
       int health;
		 int type;
       BITMAP *picture;
		 OBJECT *next, *previous;
};

#endif                                                   //End of selective declarations

