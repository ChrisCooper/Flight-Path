/*    GLOBAL DECLARATIONS.H

This header file is included only once, in SPQR.cpp

*/


#include "Definitions.h" //All structure definitions, #defines, #includes, and ENUMs


volatile long speedCounter = 0;
volatile long speedCounterCheck = 0;
volatile long moveCounter = 0;
volatile long moveCounterCheck = 0;



/*BITMAPs and BUTTONs*/
BITMAP *screenBuffer;                     //Bitmap for double buffering
BITMAP *reticle;                         //Highlights the selected square
BITMAP *machineGun;
BITMAP *bulletPic;
BITMAP *missilePic;
BITMAP *explosionPic[11];
BITMAP *smokePic[15];
BITMAP *enemyPic[1];
BITMAP *foreground;
BITMAP *planePic;

/*Gameplay variables*/
int inGame = 0;                           //Whether the actual SPQR game is in progress
float turretAngle = 0;
int totalBullets = 0;
int screenShakerX = 0;
int screenShakerY = 0;
int landscapeCounter = 0;
int totalEnemies = 0;
int score = 0;

/*mouse variables*/
int mouseX;                               //Pixel X locations of the mouse
int mouseY;                               //Pixel Y locations of the mouse
int mouseClick[2];                        //True or false if each mouse button has been clicked once
int mouseDown[2];                         //True or false if each button is down


PALETTE palette;

OBJECT theShip;

OBJECT *bulletHeader = NULL;
OBJECT *particleHeader = NULL;
OBJECT *enemyHeader = NULL;
OBJECT *enemyBulletHeader = NULL;
OBJECT *alliesHeader = NULL;
