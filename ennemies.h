
#include "munitions.h"

#ifndef __MAIN__C__
#define __MAIN__C__

typedef struct Meteor
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int speed;
    int life;
    int show;
} Meteor;

typedef struct Meteor_Handler
{
    int meteors_number;
    Meteor meteors[6];
} Meteor_Handler;

Meteor_Handler initMeteorHandler(void);
void importImage(Meteor_Handler *h, SDL_Texture *t);
int drawMeteors(SDL_Renderer *render, Meteor_Handler *h);
void updateMeteors(Meteor_Handler *handler);
void checkMeteors(Meteor_Handler *h);

void updateScore(Meteor_Handler h, int *score);

void collidBullet(Meteor_Handler *m_handler, Munition_Handler *mun_handler, SDL_Rect player, int *score);
int collideSpaceShip(Meteor_Handler *handler, SDL_Rect spaceship);
void addDifficult(Meteor_Handler *handler, SDL_Rect player);

int drawDebugRect(SDL_Renderer *render ,SDL_Rect player, Meteor_Handler handler);

#endif