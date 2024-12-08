
#include <SDL.h>

#ifndef __FUNCTIONS__C__
#define __FUNCTIONS__C__



void setError(char *message);
void destroy(SDL_Window *window, SDL_Renderer *render, SDL_Texture *t1, SDL_Texture *t2, SDL_Texture *t3);

int showBackground(SDL_Renderer *render, SDL_Texture *SDL_Texture, SDL_Rect *drect, SDL_Rect *srect);
void updateBackground(SDL_Rect *drect1, SDL_Rect *drect2);
int drawSpaceShip(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect *rect_spaceship);

void setIcon(SDL_Window *window);


void fps60(Uint32 start);

int drawScore(SDL_Renderer *render, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font, int *score, char str[], SDL_Color color, SDL_Rect position);

void show_boom(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect rect, int *line, int *col, int *timePerFrame, int *is_explosion);
#endif