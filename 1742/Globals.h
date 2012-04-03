/*    GLOBALS.H

This header file is included in most files, and includes
all global variables declared as "extern"

*/

#include "Definitions.h"


extern volatile long speedCounter;        	//For input v.s. printing
extern volatile long speedCounterCheck;
extern volatile long moveCounter;
extern volatile long moveCounterCheck;


/*BITMAPs and BUTTONs*/
extern BITMAP *screenBuffer;                     //Bitmap for double buffering
extern BITMAP *reticle;                         //Highlights the selected square
extern BITMAP *machineGun;
extern BITMAP *bulletPic;
extern BITMAP *missilePic;
extern BITMAP *explosionPic[11];
extern BITMAP *smokePic[15];
extern BITMAP *enemyPic[1];
extern BITMAP *foreground;
extern BITMAP *planePic;

/*Gameplay variables*/
extern int inGame;                           //Whether the actual SPQR game is in progress
extern float turretAngle;
extern int totalBullets;
extern int screenShakerX;
extern int screenShakerY;
extern int landscapeCounter;
extern int totalEnemies;
extern int score;

/*mouse variables*/
extern int mouseX;                               //Pixel X locations
extern int mouseY;                               //Pixel Y locations
extern int mouseClick[2];                        //True or false if each mouse button has been clicked once
extern int mouseDown[2];                         //True or false if each button is down

extern PALETTE palette;

extern OBJECT theShip;

extern OBJECT *bulletHeader;
extern OBJECT *particleHeader;
extern OBJECT *enemyHeader;
extern OBJECT *enemyBulletHeader;
extern OBJECT *alliesHeader;
