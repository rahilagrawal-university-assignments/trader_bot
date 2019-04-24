#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trader_bot.h"

#define MAXLINE 65536

struct commodity *read_commodity(void);
struct location *read_location(struct commodity **commodities);
struct bot *read_bot(struct commodity **commodities, struct location **locations);
struct cargo *read_cargo(struct commodity **commodities, struct location **locations, struct bot **bots);
void *read_str(char *s, int size);
void *salloc(size_t n_bytes);

int main(int argc, char *argv[]) {
    if (argc != 6) {
        puts(get_bot_name());
        return 0;
    }
    int n_commodities = atoi(argv[1]);
    int n_locations = atoi(argv[2]);
    int n_bots = atoi(argv[3]);
    int n_cargo = atoi(argv[4]);
    int which_bot = atoi(argv[5]);

    struct commodity *commodities[n_commodities];
    struct location *locations[n_locations];
    struct bot *bots[n_bots];

    for (int i = 0; i < n_commodities; i++) {
        commodities[i] = read_commodity();
    }

    for (int i = 0; i < n_locations; i++) {
        locations[i] = read_location(commodities);
    }

    for (int i = 0; i < n_bots; i++) {
        bots[i] = read_bot(commodities, locations);
    }

    for (int i = 0; i < n_cargo; i++) {
        read_cargo(commodities, locations, bots);
    }

    for (int i = 0; i < n_locations; i++) {
        locations[i]->next = locations[(i+1) % n_locations];
        locations[i]->previous = locations[(n_locations+i-1) % n_locations];
    }

    int action = -1;
    int n = 0;
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    get_action(bots[which_bot], &action, &n);
    printf("action=%d n=%d\n", action, n);
    return 0;
}

struct commodity *read_commodity(void) {
    char line[MAXLINE];
    int weight, volume;

    struct commodity *c = salloc(sizeof *c);

    read_str(line, MAXLINE);
    c->name = strdup(line);
    assert(c->name);

    read_str(line, MAXLINE);
    int n_read = sscanf(line, "%d%d", &weight, &volume);
    assert(n_read == 2);
    c->weight = weight;
    c->volume = volume;

    return c;
}

struct location *read_location(struct commodity **commodities) {
    char line[MAXLINE];
    int type, commodity_index, price, quantity;

    struct location *l = salloc(sizeof *l);

    read_str(line, MAXLINE);
    l->name = strdup(line);
    assert(l->name);

    read_str(line, MAXLINE);
    int n_read = sscanf(line, "%d%d%d%d", &type, &commodity_index, &price, &quantity);
    assert(n_read == 4);
    l->type = type;
    l->commodity = commodities[commodity_index];
    l->price = price;
    l->quantity = quantity;

    return l;
}

struct bot *read_bot(struct commodity **commodities, struct location **locations) {
    char line[MAXLINE];
    int cash, fuel, location_index, turns_left, fuel_tank_capacity, maximum_move, maximum_cargo_weight, maximum_cargo_volume;

    struct bot *b = salloc(sizeof *b);

    read_str(line, MAXLINE);
    b->name = strdup(line);
    assert(b->name);

    read_str(line, MAXLINE);
    int n_read = sscanf(line, "%d%d%d%d%d%d%d%d", &cash, &fuel, &location_index, &turns_left, &fuel_tank_capacity, &maximum_move, &maximum_cargo_weight, &maximum_cargo_volume);
    assert(n_read == 8);
    b->cash = cash;
    b->fuel = fuel;
    b->location = locations[location_index];
    b->turns_left = turns_left;
    b->fuel_tank_capacity = fuel_tank_capacity;
    b->maximum_move = maximum_move;
    b->maximum_cargo_weight = maximum_cargo_weight;
    b->maximum_cargo_volume = maximum_cargo_volume;

    struct bot_list *bl = salloc(sizeof *bl);
    bl->bot = b;
    bl->next = locations[location_index]->bots;
    locations[location_index]->bots = bl;

    return b;
}

struct cargo *read_cargo(struct commodity **commodities, struct location **locations,  struct bot **bots) {
    char line[MAXLINE];
    int bot_index, commodity_index, quantity;

    struct cargo *c = salloc(sizeof *c);
    read_str(line, MAXLINE);
    int n_read = sscanf(line, "%d%d%d", &bot_index, &commodity_index, &quantity);
    assert(n_read == 3);
    c->next = bots[bot_index]->cargo;
    c->commodity = commodities[commodity_index];
    c->quantity = quantity;
    bots[bot_index]->cargo = c;
    return c;
}

void *read_str(char *s, int size) {
    char *t = fgets(s, size, stdin);
    assert(t);
    char *p = strchr(t, '\n');
    if (p)
        *p = '\0';
    return t;
}

void *salloc(size_t n_bytes) {
    void *p = malloc(n_bytes);
    assert(p);
    memset(p, 0, n_bytes);
    return p;
}