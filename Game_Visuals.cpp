#include "Definitions.h"
#include "Globals.h"

void gameVisuals();
void printAll(OBJECT *theObject);
void drawHUD();
void drawRotatedSprite(BITMAP *targetBMP, BITMAP  *sprite, int x, int y, float angle);
void adjustScreenShake();
void showHealthBar(OBJECT *theObject);

void gameVisuals()
{

   landscapeCounter -= 10;
	if (landscapeCounter < -1024)
	{
      landscapeCounter = 0;
	}
 	draw_sprite(screenBuffer, foreground, landscapeCounter, 0);

	rectfill(screenBuffer, 100, 3, 500, 20, makecol(150, 150, 150));
	if (theShip.health > 750)
		rectfill(screenBuffer, 103, 6, 103 + ((int)(394*((float)theShip.health/(float)theShip.maxHealth))), 17, makecol(0, 200, 0));
	else if (theShip.health > 350)
		rectfill(screenBuffer, 103, 6, 103 + ((int)(394*((float)theShip.health/(float)theShip.maxHealth))), 17, makecol(255, 255, 0));
	else
		rectfill(screenBuffer, 103, 6, 103 + ((int)(394*((float)theShip.health/(float)theShip.maxHealth))), 17, makecol(200, 0, 0));
   textprintf_centre_ex(screenBuffer, font, 250, 8, makecol(0, 0, 0), -1, "Health: %d", theShip.health);
   textprintf_centre_ex(screenBuffer, font, 650, 8, makecol(255, 255, 255), -1, "Score: %d", score);

   adjustScreenShake();
   printAll(bulletHeader);
   printAll(enemyBulletHeader);
   printAll(enemyHeader);
   printAll(alliesHeader);
	showHealthBar(enemyHeader);
   printAll(particleHeader);
	printAll(&theShip);
//	drawRotatedSprite(screenBuffer, machineGun, (int)theShip.x + 10, (int)theShip.y + 10, itofix((int)(asin(((mouseY + 26) - (theShip.y + 50))/((mouseX + 26) - (theShip.x + 50)))/0.0174532925)));
	drawRotatedSprite(screenBuffer, machineGun, (int)theShip.x + 10, (int)theShip.y + 10, turretAngle);

//   textprintf_centre_ex(screenBuffer, font, 500, 70, makecol(255, 255, 255), -1, "float = %f fixed = %f",  5.8, ftofix(5.8));
   
	//textprintf_centre_ex(screenBuffer, font, 500, 100, makecol(255, 255, 255), -1, "Health: %d", theShip.health);

 	draw_sprite(screenBuffer, reticle, mouseX - (reticle->w / 2), mouseY - (reticle->h / 2));
	drawHUD();
	blit(screenBuffer, screen, 0,0,0 + screenShakerX, 0 + screenShakerY,1024,768);         //Blit the buffer
   clear_to_color(screenBuffer, makecol(0,0,0));
}

void printAll(OBJECT *theObject)
{
	while (theObject != NULL)
	{
   	drawRotatedSprite(screenBuffer, theObject->picture, (int)theObject->x, (int)theObject->y, theObject->rotation);
   	//drawRotatedSprite(screenBuffer, theObject->picture, (int)theObject->x, (int)theObject->y, 0 );
      theObject = theObject->next;
	}
}

void drawHUD()
{
}

void drawRotatedSprite(BITMAP *targetBMP, BITMAP  *sprite, int x, int y, float angle)
{
   rotate_sprite(targetBMP, sprite, x, y, itofix((int)(angle/0.0174532925)));
}

void adjustScreenShake()
{
	int upkeep = 10;
   if (screenShakerX != 0)
	{
	screenShakerX += upkeep;
	screenShakerX = rand() % screenShakerX - (screenShakerX/3);
	}
	if (screenShakerY != 0)
	{
	screenShakerY += upkeep;
	screenShakerY = rand() % screenShakerY - (screenShakerY/3);
	}
}

void showHealthBar(OBJECT *theObject)
{
   while (theObject != NULL)
	{
		rectfill(screenBuffer, (int)theObject->x, (int)theObject->y - 15, (int)theObject->x + 50, (int)theObject->y - 5, makecol(150, 150, 150));
		if (theObject->health/theObject->maxHealth > 0.75)
			rectfill(screenBuffer, (int)theObject->x+2, (int)theObject->y - 13, theObject->x + ((int)(47*((float)theObject->health/(float)theObject->maxHealth))), theObject->y - 7, makecol(0, 200, 0));
		else if (theShip.health > 350)
			rectfill(screenBuffer, (int)theObject->x+2, (int)theObject->y - 13, theObject->x + ((int)(47*((float)theObject->health/(float)theObject->maxHealth))), theObject->y - 7, makecol(255, 255, 0));
		else
			rectfill(screenBuffer, (int)theObject->x+2, (int)theObject->y - 13, theObject->x + ((int)(47*((float)theObject->health/(float)theObject->maxHealth))), theObject->y - 7, makecol(200, 0, 0));
		theObject = theObject->next;
	}
}
