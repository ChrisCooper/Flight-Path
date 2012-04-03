#include "Definitions.h"
#include "Globals.h"

void getInput();
void evaluateMouse();
void searchButtons();
void fireBullet();
OBJECT *fireMissile();
void moveAllObjects();
void moveObjectList(OBJECT *theObject);
void cleanObjectList(OBJECT **listHeader);
void factorGravity(OBJECT *theObject);
void keepOnScreen(OBJECT *theObject);
OBJECT *createObject(OBJECT **listHeader);
void destroyObject(OBJECT *theObject, OBJECT **listHeader);
void switchObjects(OBJECT *first, OBJECT *second, OBJECT *listHeader);
void createExplosion(float x, float y);
void createSmoke(float x, float y, float rotation);
void updateParticle(OBJECT **listHeader);
void smokeTrail(OBJECT *theSource);
void shakeScreen();
void updateTurret();
void pointForward(OBJECT *theObject);
void killShip();
void createEnemy();
void evaluateGroundCollision(OBJECT *theObject);
void checkForDeath(OBJECT **listHeader);
int collision(OBJECT *objectA, OBJECT *objectB);
void evaluateEnemyAI(OBJECT *theObject);
void callAirStrike();
void dropBomb(OBJECT * thePlane);
void forAllDo(void (*funcPtr)(), OBJECT *listHeader);

void getInput()
{
	evaluateMouse();
	updateTurret();
   searchButtons();
	if (mouseDown[0])
	{
		fireBullet();
	}
}

void evaluateMouse()
{
	mouseX = mouse_x;
	mouseY = mouse_y;
	for (int i = 0; i < 2; i++)
	{
		if ((!mouseClick[i]) && (!mouseDown[i]) && (mouse_b & (i+1)))
		{
         mouseClick[i] = TRUE;
			mouseDown[i] = TRUE;
		}
      else if (mouse_b & (i+1))
		{
			mouseClick[i] = FALSE;
			mouseDown[i] = TRUE;
		}
      else if (!(mouse_b & (i+1)))
		{
			mouseClick[i] = FALSE;
			mouseDown[i] = FALSE;
		}
	}
}

void searchButtons()
{
	if (key[KEY_W])
	{
		theShip.rotorPower += 0.03;
	}
	if (key[KEY_S])
	{
		theShip.rotorPower -= 0.03;
	}
	if (key[KEY_A])
	{
		theShip.rotation -= 0.01;
	}
	if (key[KEY_D])
	{
		theShip.rotation += 0.01;
	}

	if (key[KEY_I])
	{
		theShip.health--;
	}

	if (key[KEY_P])
	{
		readkey();
	}

	int nextKey = 0;
   if (keypressed())
   {
                     nextKey = readkey();
   }
   else
   {
                     nextKey = -1;
   }

   switch ((nextKey & 0xff))
   {
          case ' ':
              fireMissile();
              break;
          case 'l':
              createEnemy();
              break;
          case 'q':
              callAirStrike();
              break;
  }
}

void fireBullet()
{
	OBJECT *theBullet = createObject(&bulletHeader);
	theBullet->x = theShip.x + 50 + 75 * cos(turretAngle);
	theBullet->y = theShip.y + 50 + 75 * sin(turretAngle);
	theBullet->rotation = turretAngle;
	theBullet->velX += cos(turretAngle) * 60 + (rand() % 5 - 2.5) + theShip.velX;
	theBullet->velY += sin(turretAngle)* 60 + (rand() % 5 - 2.5) + theShip.velY;
	theBullet->rotorPower = 0;
	theBullet->rocketPower = 0;
	theBullet->width = 10;
	theBullet->height = 10;
	theBullet->maxHealth = 1;
	theBullet->health = 1;
	theBullet->type = BULLET;
	theBullet->picture = bulletPic;
	theShip.velX -= 0.05*(mouseX - theShip.x)/sqrt((mouseX - theShip.x)*(mouseX - theShip.x) + (mouseY - theShip.y)*(mouseY - theShip.y));
	theShip.velY -= 0.05*(mouseY - theShip.y)/sqrt((mouseX - theShip.x)*(mouseX - theShip.x) + (mouseY - theShip.y)*(mouseY - theShip.y));
   totalBullets++;
}

OBJECT *fireMissile()
{
	OBJECT *theMissile = createObject(&bulletHeader);
	theMissile->x = theShip.x + 50;
	theMissile->y = theShip.y + 75;
	theMissile->rotation = theShip.rotation;
	theMissile->velX = theShip.velX - 10;
	theMissile->velY = theShip.velY + 3;
	theMissile->rotorPower = 0.9;
	theMissile->rocketPower = 4;
	theMissile->width = 10;
	theMissile->height = 5;
	theMissile->maxHealth = 1;
	theMissile->health = 1;
	theMissile->type = MISSILE;
	theMissile->picture = missilePic;
   totalBullets++;
	return (theMissile);
}
void createExplosion(float x, float y)
{
	OBJECT *theExplosion = createObject(&particleHeader);
	theExplosion->x = x;
	theExplosion->y = y;
	theExplosion->rotorPower = 1;
	theExplosion->rocketPower = -3;
	theExplosion->maxHealth = 11;
	theExplosion->health = 11;
	theExplosion->type = EXPLOSION;
	theExplosion->picture = explosionPic[theExplosion->health];
}

void createSmoke(float x, float y, float rotation)
{
	OBJECT *theSmoke = createObject(&particleHeader);
	theSmoke->x = x;
	theSmoke->y = y;
	theSmoke->rotation = rotation;
	theSmoke->velX = (rand() % 1) - 0.5;
	theSmoke->velY = (rand() % 1) - 0.5;
	theSmoke->rotorPower = 0.5;
	theSmoke->rocketPower = -4;
	theSmoke->width = 0;
	theSmoke->height = 0;
	theSmoke->maxHealth = 11;
	theSmoke->health = 11;
	theSmoke->type = SMOKE;
	theSmoke->picture = smokePic[theSmoke->health];
}

void createEnemy()
{
   OBJECT *theEnemy = createObject(&enemyHeader);
	theEnemy->x = 1024;
	theEnemy->y = rand() % 500;
	theEnemy->rotation = -0.3;
	theEnemy->velX = -1;
	theEnemy->velY = 5;
	theEnemy->rotorPower = (rand() % 2 + 12) * 0.1;
	theEnemy->rocketPower = 0;
	theEnemy->width = 50;
	theEnemy->height = 50;
	theEnemy->maxHealth = 1000;
	theEnemy->health = 1000;
	theEnemy->type = ENEMY;
	theEnemy->picture = enemyPic[rand() % 1];
   totalEnemies++;
}
void enemyFireCannon(OBJECT *theSource)
{
	OBJECT *theBullet = createObject(&enemyBulletHeader);
	theBullet->x = theSource->x + 20;
	theBullet->y = theSource->y + 35;
	theBullet->rotation = theSource->rotation;
	theBullet->velX -= cos(theSource->rotation) * 60 + (rand() % 5 - 2.5) + theSource->velX;
	theBullet->velY -= sin(theSource->rotation)* 60 + (rand() % 5 - 2.5) + theSource->velY;
	theBullet->rotorPower = 0;
	theBullet->rocketPower = 0;
	theBullet->width = 10;
	theBullet->height = 10;
	theBullet->maxHealth = 1;
	theBullet->health = 1;
	theBullet->type = BULLET;
	theBullet->picture = bulletPic;
}

void moveAllObjects()
{
	if (!(rand() % 30))
	{
		createEnemy();
	}
	moveObjectList(&theShip);
	if (theShip.rotorPower > 1)
	{
      theShip.rotorPower -= 0.1;
	}
	if (theShip.rotorPower < 1)
	{
      theShip.rotorPower += 0.1;
	}
	keepOnScreen(&theShip);
	if (theShip.health < 1)
	{
      killShip();
	}
   OBJECT *theBullet = enemyBulletHeader;
   while(theBullet != NULL)
	{
			if (collision(theBullet, &theShip))
			{
				if (theBullet->type == MISSILE)
				{
	            theShip.health -= 200;
					score += 100;
				}
				else if (theBullet->type == BULLET)
				{
	            theShip.health -= 10;
					score += 1;
				}
            createExplosion(theBullet->x + (rand() % 20 - 10), theBullet->y + (rand() % 20 - 10));
				destroyObject(theBullet, &enemyBulletHeader);
			}
		theBullet = theBullet->next;
	}

	evaluateGroundCollision(&theShip);

	OBJECT *theObject = NULL;

	theObject = bulletHeader;
	while (theObject != NULL)
	{
		cleanObject(theObject, &enemyHeader);
		moveObject(theObject);
		theObject = theObject->next;
	}

   theObject = enemyBulletHeader;
	while (theObject != NULL)
	{
		cleanObject(theObject, &enemyBulletHeader);
		moveObject(theObject);
		theObject = theObject->next;
	}


	theObject = enemyHeader;
	while (theObject != NULL)
	{
      checkForDeath(theObject, &enemyHeader);
		cleanObject(theObject, &enemyHeader);
		moveObject(theObject);
	   evaluateGroundCollision(theObject);
		theObject = theObject->next;
	}



	theObject = particleHeader;
	while (theObject != NULL)
	{
		moveObject(theObject);
      updateParticle(theObject, &particleHeader);
		theObject = theObject->next;
	}

	theObject = alliesHeader;
	while (theObject != NULL)
	{
		moveObject(theObject);
      cleanObject(theObject, &alliesHeader);
   	dropBomb(theObject);
		theObject = theObject->next;
	}
}

void moveObject(OBJECT *theObject)
{
	static float upsideDown = 2.24;

	theObject->velX += sin(theObject->rotation) * theObject->rotorPower;
	theObject->velY += -cos(theObject->rotation) * theObject->rotorPower;
	theObject->velY += sin(theObject->rotation) * theObject->rocketPower;
	theObject->velX += cos(theObject->rotation) * theObject->rocketPower;
	factorGravity(theObject);
	theObject->x += theObject->velX;
	theObject->y += theObject->velY;
	if (theObject->rotation > upsideDown)
	{
		theObject->rotation = -upsideDown;
	}
	else if (theObject->rotation < -upsideDown)
	{
		theObject->rotation = upsideDown;
	}
}

void cleanObject(OBJECT theObject, OBJECT **listHeader)
{
	if (theObject->x < -200)
	{
      destroyObject(theObject, listHeader);
	}
	else if (theObject->x > 1124)
	{
		destroyObject(theObject, listHeader);
		//shakeScreen();
	}
	else if (theObject->y - theObject->height < -150)
	{
      destroyObject(theObject, listHeader);
	}
	else if (theObject->y > 700)
	{
      createExplosion(theObject->x - 15, theObject->y - 15);
      destroyObject(theObject, listHeader);
	}
	if (theObject->type == MISSILE)
	{
      smokeTrail(theObject);
	}
}

void factorGravity(OBJECT *theObject)
{
		theObject->velY += 1;
}

void keepOnScreen(OBJECT *theObject)
{
	static int safetyDistance = 5;
	if (theObject->x < 0)
	{
      theObject->x = safetyDistance;
		theObject->velX = 0;
	}
	else if (theObject->x > 1024 - theObject->width)
	{
		theObject->x = 1024 - safetyDistance - theObject->width;
		theObject->velX = 0;
	}
	if (theObject->y < 0)
	{
      theObject->y = safetyDistance;
		theObject->velY = 0;
	}
	else if (theObject->y > 768 - theObject->height)
	{
		theObject->y = 768 - safetyDistance - theObject->height;
		theObject->velY = 0;
	}
}

OBJECT *createObject(OBJECT **listHeader)
{
	OBJECT *newObject = (OBJECT*)malloc(sizeof(OBJECT));

	newObject->x = 100;
	newObject->y = 100;
	newObject->rotation = 0;
	newObject->velRotation = 0;
	newObject->velX = 0;
	newObject->velY = 0;
	newObject->rotorPower = 1;
	newObject->rocketPower = 1;
	newObject->width = 10;
	newObject->height = 10;
	newObject->maxHealth = 1;
	newObject->health = 1;
	newObject->type = TEMP;
	newObject->picture = NULL;

	newObject->previous = NULL;
	newObject->next = *listHeader;
	if (newObject->next != NULL)
	{
      	newObject->next->previous = newObject;
	}
	*listHeader = newObject;
	return newObject;
}

void destroyObject(OBJECT *theObject, OBJECT **listHeader)
{
	if (theObject->type == BULLET || theObject->type == MISSILE)
	{
      totalBullets--;
	}
	else if (theObject->type == ENEMY)
	{
      totalEnemies--;
	}
	if (theObject == *listHeader)
	{
		*listHeader = theObject->next;
	}
	else
	{
		theObject->previous->next = theObject->next;
	}

	if (theObject->next != NULL)
	{
		theObject->next->previous = theObject->previous;
	}
	free(theObject);
}

void switchObjects(OBJECT *first, OBJECT *second, OBJECT *listHeader)
{
	OBJECT *A = first->previous;
	OBJECT *B = first;
	OBJECT *C = second;
	OBJECT *D = second->next;

	C->next = B;
	B->next = D;
	B->previous = C;
	C->previous = A;

	if (A == NULL)
	{
		listHeader = C;
	}

	else
	{
		A->next = C;
	}
	if (D != NULL)
	{
		D->previous = B;
	}
}

void updateParticle(OBJECT theParticleA, OBJECT **listHeader)
{
	OBJECT *theParticleA = *listHeader;
	OBJECT *theParticleB;
	while(theParticleA != NULL)
	{
		theParticleB = theParticleA->next;
		theParticleA->health -= 1;
		if (theParticleA->type == EXPLOSION)
		{
			theParticleA->picture = explosionPic[theParticleA->health];
		}
		else if (theParticleA->type == SMOKE)
		{
			theParticleA->picture = smokePic[theParticleA->health];
		}
		if (theParticleA->health < 0)
		{
			destroyObject(theParticleA, listHeader);
		}
		theParticleA = theParticleB;
	}
}

void smokeTrail(OBJECT *theSource)
{
		if (!(rand() % 3))
		{
			createSmoke(theSource->x, theSource->y, theSource->rotation);
		}
}

void shakeScreen()
{
	if (screenShakerX == 0)
	{
		screenShakerX = 100;
	}
	if (screenShakerY == 0)
	{
		screenShakerY = 100;
	}
	screenShakerX = rand() % screenShakerX - (screenShakerX/2);
	screenShakerY = rand() % screenShakerY - (screenShakerY/2);
}

void updateTurret()
{
	if (mouseX > theShip.x)
	{
		turretAngle = atan((mouseY - theShip.y)/(mouseX - theShip.x));
	}
	else
	{
      turretAngle = atan((mouseY - theShip.y)/(mouseX - theShip.x)) + PI;
	}
}

void pointForward(OBJECT *theObject)
{
   while(theObject != NULL)
	{
		if (theObject->type == BULLET)
		{
		   if (theObject->velX > 0)
			{
				theObject->rotation = atan((theObject->velY)/(theObject->velX));
			}
			else
			{
		      theObject->rotation = atan((theObject->velY)/(theObject->velX)) + PI;
			}
		}
   	theObject = theObject->next;
	}
}

void killShip()
{
   for(int i = 0; i < 30; i ++)
	{
   	createExplosion(theShip.x + 50  + (rand() % 100 - 50), theShip.y + 50 + (rand() % 100 - 50));
	}
	theShip.health = 1000;
	theShip.x = 200;
	theShip.y = 200;
	theShip.velX = 0;
	theShip.velY = 0;
	theShip.rotation = 0;
}

void evaluateGroundCollision(OBJECT *theObject)
{
 	while(theObject != NULL)
	{
	   if (theObject->y > 650)
		{
			theObject->health -= (int) (30 * theObject->velY);
			theObject->rotation += 0.01 * theObject->velX + 0.3;
			theObject->x -= 20;
			theObject->y -= 10;
			for( int i = 0; i < 3; i ++)
			{
				createExplosion(theObject->x + 50 + (rand() % 100 - 50), 700 + (rand() % 30 - 15));
			}
			//shakeScreen();
		}
   theObject = theObject->next;
	}
}

void checkForDeath(OBJECT **listHeader)
{
   OBJECT *theObject = *listHeader;
   OBJECT *theBullet;
   while(theObject != NULL)
	{
      evaluateEnemyAI(theObject);
      theBullet = bulletHeader;
		while (theBullet != NULL)
		{
			if (collision(theBullet, theObject))
			{
				if (theBullet->type == MISSILE)
				{
	            theObject->health -= 1000;
					score += 100;
				}
				else if (theBullet->type == BULLET)
				{
	            theObject->health -= 50;
					score += 1;
				}
            createExplosion(theBullet->x + (rand() % 20 - 10), theObject->y + (rand() % 20 - 10));
				destroyObject(theBullet, &bulletHeader);
			}
			theBullet = theBullet->next;
		}
		if (theObject->health < 1)
		{
	      for(int i = 0; i < 5; i ++)
			{
				createExplosion(theObject->x + 50  + (rand() % 100 - 50), theObject->y + 50 + (rand() % 100 - 50));
			}
         score += 50;
         destroyObject(theObject, listHeader);
		}
		theObject = theObject->next;
	}
}

int collision(OBJECT *objectA, OBJECT *objectB)
{
	int x = (int)((objectA->x + objectA->x + objectA->width)/2);
	int y = (int)((objectA->y + objectA->y + objectA->height)/2);

	if ((x > objectB->x) && (x < objectB->x + objectB->width))
	{
		if (y > objectB->y && (y < objectB->y + objectB->height))
		{
			return (1);
		}
	}
	return (0);
}

void evaluateEnemyAI(OBJECT *theObject)
{
	if (theShip.x < theObject->x && theShip.y > theObject->y)
	{
		if (!(rand() % 3))
		{
			enemyFireCannon(theObject);
		}
		if (theObject->rotation > -0.5)
		{
      	theObject->rotation -= 0.01;
		}
		theObject->velY += 0.1;
	}
	else
	{
		if (theShip.x > theObject->x && theObject->rotation < 0.3)
		{
		   theObject->rotation += 0.02;
		   theObject->rotorPower -= 0.005;
		}
		if (theShip.y < theObject->y)
		{
		   theObject->velY -= 0.3;
		}
	}
}

void callAirStrike()
{
	OBJECT *thePlane = createObject(&alliesHeader);
	thePlane->x = -200;
	thePlane->y = 0;
	thePlane->rotation = 0;
	thePlane->velX = 50;
	thePlane->velY = 0;
	thePlane->rotorPower = 1;
	thePlane->rocketPower = 0;
	thePlane->width = 10;
	thePlane->height = 10;
	thePlane->maxHealth = 1;
	thePlane->health = 1;
	thePlane->type = BULLET;
	thePlane->picture = planePic;
}

void dropBomb(OBJECT * thePlane)
{
	OBJECT *theBomb = fireMissile();
	theBomb->x = thePlane->x + 10;
	theBomb->y = thePlane->y + 10;
	theBomb->velX = thePlane->velX / 5;
	theBomb->velY = 0;
	theBomb->rotation = 0.5;
	theBomb->rotorPower = 0;
	theBomb->rocketPower = -0.5;
}

