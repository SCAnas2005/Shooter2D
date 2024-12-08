
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_ttf.h>

#include "timer.h"

int drawTimer(SDL_Renderer *render, TTF_Font *font, SDL_Surface *surface, SDL_Texture *texture, char str[], SDL_Color color, SDL_Rect rect)
{
    surface = TTF_RenderText_Blended(font, str, color);
    if (surface == NULL) {printf("Surface_txt == NULL\n"); return -1;}

    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {printf("texture_txt == NULL\n"); return -1;}

    if (SDL_RenderCopy(render, texture, NULL, &rect) != 0)
    {SDL_DestroyTexture(texture); printf("SDL_RenderCopy()\n"); return -1;}

    SDL_DestroyTexture(texture);
    return 0;
}

void updateTimer(chrono *c, int *time, char str[])
{
    if ((*time) > 1000)
    {
        (*time) = 0; 
        c->seconds2++;
        if (c->seconds2 == 10)
        {
            c->seconds2 = 0;
            c->seconds1++;
            if (c->seconds1 == 6)
            {
                c->seconds1 = 0;
                c->minuts2++;
                if (c->minuts2 == 10)
                {
                    c->minuts2 = 0;
                    c->minuts1++;
                }
            }
        }
        sprintf(str, "%d%d:%d%d", c->minuts1, c->minuts2, c->seconds1, c->seconds2);
    }
}