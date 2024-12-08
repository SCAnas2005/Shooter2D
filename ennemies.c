
#include <stdio.h>
#include <SDL.h>
#include "ennemies.h"
#include "munitions.h"
#include "time.h"

Meteor_Handler initMeteorHandler(void)
{
    Meteor_Handler h;
    h.meteors_number = 6;

    SDL_Rect r = {500, -100, 100, 100};
    
    for (int i = 0; i < h.meteors_number; i++)
    {
        h.meteors[i].rect = r;
        h.meteors[i].life = 1;
        h.meteors[i].speed = 10;
        h.meteors[i].show = 1;
    }

    return h;
}

void importImage(Meteor_Handler *h, SDL_Texture *t)
{
    for (int i = 0; i < h->meteors_number; i++)
    {
        h->meteors[i].texture = t;
    }
}

int drawMeteors(SDL_Renderer *render, Meteor_Handler *h)
{
    for (int i = 0; i < h->meteors_number; i++)
    {
        if (h->meteors[i].show)
            {if (SDL_RenderCopy(render, h->meteors[i].texture, NULL, &h->meteors[i].rect) != 0) return -1;}
    }

    return 0;
}

void updateMeteors(Meteor_Handler *handler)
{
    for (int i = 0; i < handler->meteors_number; i++)
    {
        handler->meteors[i].rect.y = handler->meteors[i].rect.y + handler->meteors[i].speed;
    }
}

void checkMeteors(Meteor_Handler *h)
{
    
    int ecart = (1080 - (h->meteors[0].rect.w)*h->meteors_number) / (h->meteors_number+1);
    for (int i = 0; i < h->meteors_number; i++)
    {
        if (h->meteors[i].life == 0)
        {
            h->meteors[i].show = 0;
        }
        if ((h->meteors[i].rect.y+h->meteors[i].speed) > 720)
        {
            h->meteors[i].rect.y = -(rand() % 600);
            h->meteors[i].rect.x = ecart*(i+2) + h->meteors[i].rect.w*(i-1);
            h->meteors[i].life = 1;
            h->meteors[i].show = 1;
        }
    }  
}


void collidBullet(Meteor_Handler *m_handler, Munition_Handler *mun_handler, SDL_Rect player, int *score)
{
    SDL_Rect munition;
    SDL_Rect meteor;
    for (int i = 0; i < m_handler->meteors_number; i++)
    {
        for (int j = 0; j < mun_handler->munitions_number; j++)
        {
            if (m_handler->meteors[i].show && mun_handler->munitions[j].available)
            {
                munition = mun_handler->munitions[j].pos;
                meteor = m_handler->meteors[i].rect;
                if (munition.x >= (meteor.x+2) && (munition.x+munition.w) <= (meteor.x+meteor.w-2))
                {
                    if (munition.y <= (meteor.y+meteor.h) && munition.y >= meteor.y)
                    {
                        mun_handler->munitions[j].available = 0;
                        mun_handler->munitions[j].pos.y = player.y;
                        m_handler->meteors[i].life = m_handler->meteors[i].life - 1;
                        if (m_handler->meteors[i].life == 0) {(*score)++;}
                    }
                }
            }
        }
    }
}

int collideSpaceShip(Meteor_Handler *handler, SDL_Rect spaceship)
{
    SDL_Rect meteor;
    for (int i = 0; i < handler->meteors_number; i++)
    {
        if (handler->meteors[i].show)
        {   
            meteor = handler->meteors[i].rect;
            if ((spaceship.x+5 >= meteor.x+10 && spaceship.x+5 <= (meteor.x+meteor.w+-10)) 
            || ((spaceship.x+spaceship.w-5) >= meteor.x+10 && (spaceship.x+spaceship.w-5) <= (meteor.x+meteor.w-10)))
            {
                if (spaceship.y <= (meteor.y+meteor.h) && spaceship.y >= (meteor.y+(meteor.h/2))) // Haut spaceship
                {
                    handler->meteors[i].show = 0;
                    return 1;
                }
                else if (spaceship.y+spaceship.h >= (meteor.y) && spaceship.y+spaceship.h <= (meteor.y+(meteor.h/2)))
                {
                    handler->meteors[i].show = 0;
                    return 1;
                }
            }
            else if ((spaceship.y >= meteor.y && spaceship.y <= (meteor.y+meteor.h)) 
            || ((spaceship.y+spaceship.h) >= meteor.y && (spaceship.y+spaceship.h) <= (meteor.y+meteor.h)))
            {
                if ((spaceship.x+spaceship.w) >= meteor.x && (spaceship.x+spaceship.w) <= (meteor.x+(meteor.h/2)))
                {
                    handler->meteors[i].show = 0;
                    return 1;
                }
                else if ((spaceship.x) <= (meteor.x+meteor.w) && (spaceship.x) >= (meteor.x+(meteor.x/2)))
                {
                    handler->meteors[i].show = 0;
                    return 1;
                }
            }
        }
    }

    return 0;
}


int drawDebugRect(SDL_Renderer *render ,SDL_Rect player, Meteor_Handler handler)
{
    if (SDL_SetRenderDrawColor(render, 255,255,255, 0) != 0) return -1;
    if (SDL_RenderDrawRect(render, &player) != 0) return -1;

    for (int i = 0; i < handler.meteors_number; i++)
    {
        if (handler.meteors[i].show)
        {
            if (SDL_RenderDrawRect(render, &handler.meteors[i].rect) != 0) return -1;
        }
    }

    return 0;
}

void updateScore(Meteor_Handler h, int *score)
{
    for (int i = 0; i < h.meteors_number; i++)
    {
        if (h.meteors[i].life == 0)
        {
            (*score)++;
            break;
        }
    }
}