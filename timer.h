
#ifndef __TIMER__C__
#define __TIMER__C__

typedef struct chrono
{
    int minuts1;
    int minuts2;
    int seconds1;
    int seconds2;

    int timeMillis;
} chrono;


int drawTimer(SDL_Renderer *render, TTF_Font *font, SDL_Surface *surface, SDL_Texture *texture, char str[], SDL_Color color, SDL_Rect rect);
void updateTimer(chrono *c, int *time, char str[]);

#endif