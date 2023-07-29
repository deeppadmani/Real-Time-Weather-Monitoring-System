/*Ext_InterruptDriver.c*/

#include "header.h"

void Ext_INT0_Init()				
{
	EA  = 1;							
	EX0 = 1;
	//IT0=1 //edge triggered 
	IT0=1; //level triggered     							
}
