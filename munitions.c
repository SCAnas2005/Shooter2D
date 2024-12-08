
#include <stdio.h>
#include <SDL.h>

#include "munitions.h"

Munition_Handler initHandler(SDL_Rect player) // initialisation gestionnaire de munitions
{
    SDL_Rect rect = {player.x+20, player.y, 7, 25};
    Munition mun = {rect, 20, 0};
    Munition_Handler h;
    h.munitions_number = 2;
    for (int i = 0; i < h.munitions_number; i++)
    {
        h.munitions[i] = mun; 
    }

    return h;
}

int show_munition(Munition_Handler h, SDL_Renderer *render, SDL_Rect player) // Affiche les munitions
{
    if (SDL_SetRenderDrawColor(render, 255, 255 ,0, 255) != 0) {printf("1\n"); return -1;}
    for (int i = 0; i < h.munitions_number; i++)
    {
        if (h.munitions[i].available == 1)
        {
            h.munitions[i].pos.x = player.x+((player.w-h.munitions[i].pos.w) / 2);
            if (SDL_RenderFillRect(render, &h.munitions[i].pos) != 0) {printf("2\n"); return -1;}
        }
    }

    return 0;
}

void update_munition(Munition_Handler *h)
{
    for (int i = 0; i < h->munitions_number; i++)
    {
        if (h->munitions[i].available)
        {
            h->munitions[i].pos.y = h->munitions[i].pos.y - h->munitions[i].speed;
        }
    }
}

void check_munition(Munition_Handler *h, SDL_Rect player)
{
    int x = player.x;
    int y = player.y;
    for (int i = 0; i < h->munitions_number; i++)
    {
        if (h->munitions[i].available)
        {
            if (h->munitions[i].pos.y <= 0)
            {
                h->munitions[i].pos.y = y;
                h->munitions[i].available = 0;
            }
        }
    }
}