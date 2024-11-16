#include <stdio.h>

#define SQUAD_SIZE 11

struct age
{
    int day;
    int month;
    int year;
};

struct player_t
{
    char name[25];
    int kitnum;
    char club[30];
    struct age playerage;
    char position[20];
};

struct team_t{
    char name[20];
    struct player_t players[SQUAD_SIZE];
    int activeSize;
};

