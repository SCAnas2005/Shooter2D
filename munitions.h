
#include <SDL.h>

#ifndef __MUNITIONS__C__
#define __MUNITIONS__C__


typedef struct Munition // Structure Munitions
{
    SDL_Rect pos;
    int speed;
    int available;
} Munition;

typedef struct Munition_Handler // Structure gestionnaire
{
    int munitions_number;
    Munition munitions[10];
} Munition_Handler;


Munition_Handler initHandler(SDL_Rect player);
int show_munition(Munition_Handler h, SDL_Renderer *render, SDL_Rect player);
void update_munition(Munition_Handler *h);
void check_munition(Munition_Handler *h, SDL_Rect player);


#endif