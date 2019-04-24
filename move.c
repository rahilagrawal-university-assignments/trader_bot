//Author: Rahil Agrawal
//Email: barcalm10@yahoo.com
//Date Created: 7 May 2017
//This is a C program that contains a function that sets the movement of the bot of the bot

//the bot only moves if it has not made another action in this turn
//before moving the bot checks its current status and moves to the required location using optimised number of turns and checking for any chance of refuelling on its way
//if the bot comes accross a petrol station, it buys enough petrol to go to the next petrol station
//if the petrol is enough to keep moving, bot keeps moving
//if the cargo is NULL, bot genereally moves to the nearest selling location that has items to sell and ensures that the bot can sell these items once bought
//if the bot has something in its cargo, it moves to the closest selling location that buys that commodity at a higher price than the bot bought it at
//if the fuel is finished and there is no way that th bot can move, the move is set to 0
//if there is enough fuel but the bot's current status doesnt allow profitable moves, the move is set to 0 to avoid unnecessary loss.
#include "files.h"
#include "trader_bot.h"
#include <stdio.h>
#include <string.h>
//Function to move - only called if neither buying nor selling
void move(struct bot *b, int *action, int *n, int *flag)
{

	*action=ACTION_MOVE;
	//variable to determine the amount of steps to be moved
	int move=0;
	//flag to determine if a move has alread been decided, if not then other conditions are checked
	int move_made=0;
	//flag to check if petrol has been filled so bot can start moving from a petrol station
	int petrol_filled=0;
	//pointer to a location struct used for traversing through the linked lists 
	struct location *current_location = b->location;
	//If the fuel is 0, stop moving 
	if(b->fuel==0)
	{
		move_made=1;
		*n=0;
	}
	if(current_location->type==LOCATION_PETROL_STATION)
	{
		//only buy enough fuel to reach the next petrol station
		if(b->fuel!=b->fuel_tank_capacity && current_location->quantity>0 && b->fuel<nearest_petrol_station(b))
		{
			*action=ACTION_BUY;
			//*n=b->fuel_tank_capacity-b->fuel;
			*n=nearest_petrol_station(b);
			move_made=1;
		}
		//if the next petrol station is too close then the bot should fill up the fuel tank and then skip the next petrol station
		else if(b->fuel!=b->fuel_tank_capacity && current_location->quantity>0 && nearest_petrol_station(b)<b->maximum_move)
		{
			*action=ACTION_BUY;
			*n=b->fuel_tank_capacity-b->fuel;
			move_made=1;
		}
		//if petrol is enough to keep moving then set flag for petrol filling to 1	
		else
		{		
			petrol_filled=1;
		}
	}
	//if fuel is not 0 AND the cargo is empty or the items have just been sold, then move to the nearest seller 
	if((b->cargo==NULL || current_location->type==LOCATION_BUYER) && move_made!=1)
	{
		int seller_exhausted=0;
		//keep moving until a seller is found, otherwise move maximum distance that is allowed		
		if(current_location->type==LOCATION_SELLER && b->cargo==NULL && current_location->quantity>0 && items_to_buy(b)==0)
		{
			seller_exhausted=1;
		}

		while(!( (b->cargo!=NULL && current_location->type==LOCATION_BUYER && strcmp(current_location->commodity->name,b->cargo->commodity->name)==0 && current_location->quantity>0) || (current_location->type==LOCATION_SELLER && b->cargo==NULL && current_location->quantity>0 && seller_exhausted!=1)))
		{
			seller_exhausted=0;
			move++;
			current_location=current_location->next;
			
			//if the bot can reach a nearby petrol station and does not have enough fuel, it should go there
			if(current_location->type==LOCATION_PETROL_STATION && petrol_filled!=1)
			{
				break;
			}
			//bot can only move the maximum number of turns if it is not doing anything else
			if(move==b->maximum_move)
			{
				break;
			}
		}
		if(move>=1)
		{
			move_made=1;
		}
		*action=ACTION_MOVE;
		*n=move;
		
		
	}


	//if items have not been sold and no move has been made, move to nearest buyer
	if (b->cargo!=NULL && move_made!=1)
	{
		//move until a buying location is found, otherwise move maximum distance allowed
		while(!(current_location->type==LOCATION_BUYER && strcmp(b->cargo->commodity->name,current_location->commodity->name)==0 && current_location->quantity>0))
		{
			move++;
			current_location=current_location->next;
			//if the bot can reach a nearby petrol station and does not have enough fuel, it should go there
			if(current_location->type==LOCATION_PETROL_STATION && petrol_filled!=1)
			{
				break;
			}
			//bot can only move the maximum number of turns if it is not doing anything else
			if(move==b->maximum_move)
			{
				break;
			}
			
		}
		if(move>=1)
		{
			move_made=1;
			*action=ACTION_MOVE;
			*n=move;
		}
		//if a wise move hasnt been made so far, just go to the next location
		else 	
		{
			*action=ACTION_MOVE;
			*n=1;
		}
		
		
	}
	
	
}
