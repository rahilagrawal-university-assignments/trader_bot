//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program that contains a function to determine the distance to the nearest petrol station that has some fuel that the bot can buy
#include "files.h"
#include "trader_bot.h"
#include <stdio.h>
#include <string.h>
//Function to find nearest petrol station to the current location
int nearest_petrol_station(struct bot *b)
{
	struct location *nearest_petrol_station=b->location->next;
	//distance to nearest petrol station intially set to 1 as the next location might be a petrol station and the while loop may never run	
	int dist_petrol=1; 
	//while loop iterates from the location next to current location until the counter returns to current location OR
	// a petrol station that has fuel to sell is found
	while(!(nearest_petrol_station->type==LOCATION_PETROL_STATION && nearest_petrol_station->quantity>0))
	{
		dist_petrol++;
		//break out of the loop if the whole world has been scanned once
		if(nearest_petrol_station==b->location)
		{
			break;
		}
		nearest_petrol_station=nearest_petrol_station->next;
	}
	return dist_petrol;

}

