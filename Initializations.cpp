#include "Definitions.h" //All structure definitions, #defines, #includes, and ENUMs
#include "Globals.h"     //Includes all global variables declared as "extern"

extern void incrementTimer();
extern void incrementMoveTimer();

void initializeGame();
void allegInitializations();
void initializeShip();
BITMAP *makeBitmap(char *aFilename);
SAMPLE *makeSample(char *aFilename);
FONT *makeFont(char *aFilename);


void allegInitializations()
{
	int error = 0;
	srand(time(0));
   error |= allegro_init ();
	algif_init ();

   	set_color_depth (32);
   	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768,0,0);
   	//set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024,768,0,0);
   	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
   	error |= install_keyboard ();
   	install_mouse();
   	error |= install_timer();
   	error |= install_int_ex(incrementTimer, BPS_TO_TIMER(130));
   	error |= install_int_ex(incrementMoveTimer, BPS_TO_TIMER(30));
	if (error)
	{
		set_gfx_mode(GFX_TEXT, 1024,768,0,0);
		allegro_message("Allegro Failed to Initialize!");
		exit(1);
	}

}

void initializeGame()
{
   screenBuffer = create_bitmap(1024, 768);
   reticle = makeBitmap("Images/Reticle.gif");
	machineGun = makeBitmap("Images/MachineGun.gif");
	bulletPic = makeBitmap("Images/Bullet.gif");
	missilePic = makeBitmap("Images/Missile.gif");

	explosionPic[0] = makeBitmap("Images/Explosion0.gif");
	explosionPic[1] = makeBitmap("Images/Explosion1.gif");
	explosionPic[2] = makeBitmap("Images/Explosion2.gif");
	explosionPic[3] = makeBitmap("Images/Explosion4.gif");
	explosionPic[4] = makeBitmap("Images/Explosion6.gif");
	explosionPic[5] = makeBitmap("Images/Explosion8.gif");
	explosionPic[6] = makeBitmap("Images/Explosion9.gif");
	explosionPic[7] = makeBitmap("Images/Explosion9.gif");
	explosionPic[8] = makeBitmap("Images/Explosion10.gif");
	explosionPic[9] = makeBitmap("Images/Explosion10.gif");
	explosionPic[10] = makeBitmap("Images/Explosion11.gif");
	explosionPic[11] = makeBitmap("Images/Explosion11.gif");

	smokePic[0] = makeBitmap("Images/GoodSmoke0.gif");
	smokePic[1] = makeBitmap("Images/GoodSmoke0.gif");
	smokePic[2] = makeBitmap("Images/GoodSmoke0.gif");
	smokePic[3] = makeBitmap("Images/GoodSmoke0.gif");
	smokePic[4] = makeBitmap("Images/GoodSmoke0.gif");
	smokePic[5] = makeBitmap("Images/GoodSmoke1.gif");
	smokePic[6] = makeBitmap("Images/GoodSmoke2.gif");
	smokePic[7] = makeBitmap("Images/GoodSmoke2.gif");
	smokePic[8] = makeBitmap("Images/GoodSmoke1.gif");
	smokePic[9] = makeBitmap("Images/GoodSmoke2.gif");
	smokePic[10] = makeBitmap("Images/GoodSmoke2.gif");
	smokePic[11] = makeBitmap("Images/GoodSmoke1.gif");
	smokePic[12] = makeBitmap("Images/GoodSmoke2.gif");
	smokePic[13] = makeBitmap("Images/GoodSmoke1.gif");
	smokePic[14] = makeBitmap("Images/GoodSmoke2.gif");

	enemyPic[0] = makeBitmap("Images/Enemy0.gif");

   foreground = makeBitmap("Images/Foreground.bmp");

   planePic = makeBitmap("Images/Plane.gif");
   debrisPic = makeBitmap("Images/Chunk.gif");

	initializeShip();
}

void initializeShip()
{
	theShip.x = 500;
	theShip.y = 500;
	theShip.rotation = 0;
	theShip.velRotation = 0;
	theShip.velX = 0;
	theShip.velY = -1;
   theShip.rotorPower = 1;
   theShip.rocketPower = 0;
	theShip.width = 100;
	theShip.height = 100;
	theShip.maxHealth = 1000;
	theShip.health = 1000;
	theShip.picture = makeBitmap("Images/Ship.gif");
	theShip.next = NULL;
	theShip.previous = NULL;
}









BITMAP *makeBitmap(char *aFilename)
{
	BITMAP *bitmapPointer;
	if (!(bitmapPointer = load_bitmap(aFilename, NULL)))
	{
      set_gfx_mode(GFX_TEXT, 1024,768,0,0);
		allegro_message("Error! Could not find the file \"%s\"!", aFilename);
		exit(1);
	}
	return(bitmapPointer);
}

//returns a pointer to SAMPLE (char *aFilename) and shows
//error message on failure
SAMPLE *makeSample(char *aFilename)
{
	SAMPLE *samplePointer;
	if (!(samplePointer = load_sample(aFilename)))
	{
      set_gfx_mode(GFX_TEXT, 1024,768,0,0);
		allegro_message("Error! Could not find the file \"%s\"!", aFilename);
		exit(1);
	}
	return(samplePointer);
}

//returns a pointer to FONT (char *aFilename) and shows
//error message on failure
FONT *makeFont(char *aFilename)
{
	FONT *fontPointer;
	if (!(fontPointer = load_font(aFilename, palette, NULL)))
	{
      set_gfx_mode(GFX_TEXT, 1024,768,0,0);
		allegro_message("Error! Could not find the file \"%s\"!", aFilename);
		exit(1);
	}
	return(fontPointer);
}

