//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program that contains a function to determine the amount of items that the bot should buy from a seller
		
//if there is a buyer that buys the same commodity at a higher price, there is enough fuel and enough number of turns to reach the buyer and sell the commodities to him and if the cargo is empty, then the bot buys the amount that the buyer can later buy from the bot
//if there is no such location then the bot does not buy anything, return 0.
#include "files.h"
#include "trader_bot.h"
#include <stdio.h>
#include <string.h>
//Function to return amount of items to be bought
int items_to_buy(struct bot *b)
{
	int items_to_buy=0,distance=0,no_petrol_stations=0;
	struct location *curr_location = b->location;
	//loop to find a location that buys the same commodity as the current selling location, at a higher price and is willing to buy
	while(1)
	{
		//also calculate the distance between the current selling location and the location of the buyer		
		distance++;
		curr_location=curr_location->next;
		//if such a location is found, return the value that it is willing to buy - buy only as much as you can sell		
		if(curr_location->commodity != NULL && strcmp(b->location->commodity->name,curr_location->commodity->name)==0 && curr_location->quantity > 0 && curr_location->price>b->location->price && curr_location->type==LOCATION_BUYER)
		{
			items_to_buy=curr_location->quantity;
			break;
		}
		//Counting the number of petrol stations for optimising the behaviour of robot when it comes towards the number of turns left
		if(curr_location->type==LOCATION_PETROL_STATION)
		{
			no_petrol_stations+=1;
		}
				
		//if no such location is found, break out of the loop and continue moving
		if(curr_location==b->location)
		{
			break;
		}
		
	}
	//if there is enough fuel to reach the buying location or a nearby petrol pump
	//and if there are enough turns left so as to reach the buying location (towards the end of the game)
	if((distance<=b->fuel || b->fuel>=nearest_petrol_station(b)) && b->turns_left>=(distance/b->maximum_move + (2*no_petrol_stations) + 3))
	{
		return items_to_buy;
	}
	//OTHERWISE, if there is not enouogh fuel to reach the buying location, do NOT buy
	else
	{
		return 0;
	}
}
