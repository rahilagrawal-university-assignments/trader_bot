//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program that contains a function to buy commodities


//commodities are only bought if the items_to_buy function returns a positive integer and the cargo is NULL, otherwise the bot keeps moving
#include "files.h"
#include "trader_bot.h"
#include <stdio.h>
#include <string.h>
//Function to buy a commodity
void buy(struct bot *b, int *action, int *n, int *flag)
{
	//flag will be changed to 3 and remain 3 if buying a commodity is succesful	
	*flag=3;
	//Only buy if the cargo is empty - Previous items have to be successfully sold
	if(b->cargo==NULL)
	{
		*action=ACTION_BUY;
		*n=items_to_buy(b);
		//if 0 items are bought then the bought should keep moving
		if(*n==0)
		{
			*flag=2;
		}
	}
	//if buying is unsuccessful - either items were bought in previous turn or items need not be bought, then flag is set to 2
	else
	{
		*flag=2;
	}


}
