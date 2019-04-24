#include "trader_bot.h"
//Declaring prototypes of functions
void buy(struct bot *b, int *action, int *n, int *flag);
void sell(struct bot *b, int *action, int *n, int *flag);
void move(struct bot *b, int *action, int *n, int *flag);
int items_to_buy(struct bot *b);
int nearest_petrol_station(struct bot *b);
void get_action(struct bot *b, int *action, int *n);
char *get_bot_name(void);

