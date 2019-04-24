//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program that contains a function to sell commodites that the bot is holding

//Bot only sells to a location that buys the same commodity and is willing to buy otherwise it keeps moving
#include "files.h"
#include "trader_bot.h"
#include <stdio.h>
#include <string.h>
//Function to sell a commodity
void sell(struct bot *b, int *action, int *n, int *flag)
{
	//flag is set to 3 and remains 3 if selling is succesful
	*flag=3;
	
	//if the bot is at a location that buys the same commodity as in the cargo, and the location is willing to buy, attempt to sell 
	if( strcmp(b->cargo->commodity->name,b->location->commodity->name)==0 && b->location->quantity > 0)
	{
		*action=ACTION_SELL;
		*n=b->location->quantity;
	}
	
	else 
	{
		*flag=2;
	}



}
