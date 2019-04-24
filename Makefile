CC=dcc
mybot: trader_bot_main.o simple_bot.o move.o buy.o sell.o items_to_buy.o nearest_petrol.o trader_bot.h files.h
	$(CC) trader_bot_main.o simple_bot.o move.o buy.o sell.o items_to_buy.o nearest_petrol.o -o mybot
trader_bot_main.o: trader_bot_main.c 
	$(CC) -c trader_bot_main.c
simple_bot.o: simple_bot.c trader_bot.h files.h
	$(CC) -c simple_bot.c 
move.o: move.c trader_bot.h files.h
	$(CC) -c move.c 
buy.o: buy.c trader_bot.h files.h
	$(CC) -c buy.c 
sell.o: sell.c trader_bot.h files.h 
	$(CC) -c sell.c
items_to_buy.o: items_to_buy.c trader_bot.h files.h
	$(CC) -c items_to_buy.c 
nearest_petrol.o: nearest_petrol.c trader_bot.h files.h
	$(CC) -c nearest_petrol.c
clean:
	rm *.o
	
