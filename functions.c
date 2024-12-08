
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#include "functions.h"

void setError(char *message)
{
    SDL_Log("Error : %s > %s\n", message, SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void destroy(SDL_Window *window, SDL_Renderer *render, SDL_Texture *t1, SDL_Texture *t2, SDL_Texture *t3)
{
    if (t1 != NULL) SDL_DestroyTexture(t1);
    if (t2 != NULL) SDL_DestroyTexture(t2);
    if (t3 != NULL) SDL_DestroyTexture(t3);
    if (render != NULL) SDL_DestroyRenderer(render); 
    if (window != NULL) SDL_DestroyWindow(window);
}

int showBackground(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect *drect, SDL_Rect *srect)
{
    if (SDL_RenderCopy(render, texture, NULL, drect) != 0) return -1;
    if (SDL_RenderCopy(render, texture, NULL, srect) != 0) return -1;
    return 0;
}

void updateBackground(SDL_Rect *drect1, SDL_Rect *drect2)
{
    if (drect1->y >= 720)
        drect1->y = -720;
    else
        drect1->y += 10;
    
    if (drect2->y >= 720)
        drect2->y = -720;
    else
        drect2->y += 10;
}

int drawSpaceShip(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect *rect_spaceship)
{
    if (SDL_RenderCopy(render, texture, NULL, rect_spaceship) != 0) return -1;
    return 0;
}

void setIcon(SDL_Window *window)
{
    SDL_Rect rect_icon = {0, 0, 32, 32};
    //SDL_Surface *surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);

    SDL_Surface *surface = IMG_Load("../meteor.png");
    
    SDL_FillRect(surface, &rect_icon, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}


void fps60(Uint32 start)
{
    if (1000/60 > (SDL_GetTicks() - start))
    {
        SDL_Delay(1000/60 - (SDL_GetTicks() - start));
    }
}


int drawScore(SDL_Renderer *render, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font, int *score, char str[], SDL_Color color, SDL_Rect position)
{
    sprintf(str, "%d", *score);

    surface = TTF_RenderText_Blended(font, str, color);
    if (surface == NULL) return -1;

    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) return -1;
    

    if (SDL_RenderCopy(render, texture, NULL, &position) != 0) return -1;
    return 0;
}

void saveScoreAndTime()
{
    //
}

void show_boom(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect rect, int *line, int *col, int *timePerFrame, int *is_explosion)
{
    SDL_Rect dest = rect;
    int timeX = (SDL_GetTicks() / 50) % 9;
    int timeY = (SDL_GetTicks() / 50) % 8;
    SDL_Rect image = {timeX*100, timeY*100, 100, 100};    


    SDL_RenderCopy(render, texture, &image, &dest);
    if ((*line) != 7 && (*col) != 8)
    {
        if (*timePerFrame == 0)
        {
            *timePerFrame = 6;
            if (*col+1 < 9)
                (*col)++;
            else
            {
                //(*col) = 0;
                if (*line+1 < 8)
                    (*line)++;
                else 
                {
                    //(*line) = 0;
                }
            }
        }
        else
        {
            (*timePerFrame)--;
        }
    }
    else 
    {
        *is_explosion = 0;
        *col = 0;
        *line = 0;
    }
}