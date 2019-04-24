//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program to determine after each turn a bot's move
#include <stdio.h>
#include <string.h>
#include "trader_bot.h"
#include "files.h"
//Function to get the name of the Bot
char *get_bot_name(void)
{
	return "Rahil";
}
//Get Action Function for passing the required *action and corresponding *n
void get_action(struct bot *b, int *action, int *n)
{
	//flag variable - used to determine if an action has already been made or not, if it has not been made, then the program keeps executing
	int flag=0; 
	//If bot is at a seller location, has enough cash and the location has amount to sell, call the buy function	
	if (b->cash>0 && b->location->type==LOCATION_SELLER && b->location->quantity>0)
	{
		buy(b,action,n,&flag);
			
	}
 	
	//If bot is at a buying location, its cargo is not empty and it has not performed any other action in this turn, call the sell function
	if(flag==0 && b->location->type==LOCATION_BUYER && b->cargo!=NULL)
	{
		sell(b,action,n,&flag);
	}	
	
	//If the bot is neither buying, nor selling for this turn, then move function is called
	if (flag==2 || flag==0)
	{
		move(b,action,n,&flag);
	}
	
}
