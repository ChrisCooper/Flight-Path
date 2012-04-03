/*  INCREMENTS.cpp

This contains the functions passed to timer routins.
All that they do is increment the selected variable

*/

#include "Definitions.h" //All structure definitions, #defines, #includes, and ENUMs
#include "Globals.h"     //Includes all global variables declared as "extern"

void incrementTimer()
{
  speedCounter++;
}
void incrementMoveTimer()
{
  moveCounter++;
}
