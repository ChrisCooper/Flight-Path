#include "Definitions.h"
#include "Global_Declarations.h"


extern void allegInitializations();
extern void initializeGame();
extern void getInput();
extern void gameVisuals();
extern void moveAllObjects();
extern void pointForward(OBJECT *theObject);


int main()
{

   allegInitializations();

	initializeGame();

   inGame = 1;
	//The main game loop
	while (inGame && (!key[KEY_ESC]))
    {
			/*Input vs. Visuals loop                      130 BPS*/
			if (speedCounterCheck == speedCounter)
			{
			}
			else if (speedCounter > 1)
			{
              speedCounter = 0;
              gameVisuals();
			}
         else
         {
              getInput();
              speedCounterCheck = speedCounter;
         }

			/*Input vs. Visuals loop                      30 BPS*/
			if (moveCounterCheck == moveCounter)
			{
			}
         else
         {
              moveAllObjects();
              pointForward(bulletHeader);
              moveCounterCheck = moveCounter;
         }

    }
	return 0;
}END_OF_MAIN();

//TO-DO
/*

*Make moves (flip, strafe, , air-strike etc.)

*Make enemies shoot

*make copter collide w/ enemies/bullets

*/
