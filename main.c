
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "functions.h"
#include "munitions.h"
#include "ennemies.h"
#include "timer.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

int main(int argv, char **argc)
{
    srand(time(NULL));

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Surface *surface_bg = NULL, *surface_spaceship = NULL;
    SDL_Texture *texture_bg = NULL, *texture_spaceship = NULL;
    SDL_Texture *texture_meteor = NULL;
    SDL_bool keys[SDL_NUM_SCANCODES] = {SDL_FALSE};
    TTF_Font *font = NULL;
    SDL_Surface *text = NULL;
    SDL_Texture *texture_score = NULL;
    int is_explosion = 0;
    int explosion_line = 0;
    int explosion_col = 0;
    int timePerFrame = 6;
    int showSpaceship = 1;

    Uint32 start, end;
    int score = 0;
    int active = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {setError("SDL_Init()");}
    if (TTF_Init() != 0) {setError("TTF_Init()");}
    
    // ====================================================================================================
    window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
    if (window == NULL) {setError("window == NULL");}

    setIcon(window);


    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (render == NULL) {destroy(window, NULL, NULL, NULL, NULL); setError("render == NULL");} 
    // ====================================================================================================

    // ====================================================================================================
    surface_bg = IMG_Load("../space.jpg");
    if (surface_bg == NULL) {destroy(window, render, NULL, NULL, NULL); setError("surface_bg == NULL");}

    texture_bg = SDL_CreateTextureFromSurface(render, surface_bg);
    SDL_FreeSurface(surface_bg);
    if (texture_bg == NULL) {destroy(window, render, NULL, NULL, NULL); setError("texture_bg == NULL");}
    // ====================================================================================================

    // ====================================================================================================
    surface_spaceship = IMG_Load("../s3.png");
    if (surface_spaceship == NULL) {destroy(window, render, texture_bg, NULL, NULL); setError("spacehip == NULL");}

    texture_spaceship = SDL_CreateTextureFromSurface(render, surface_spaceship);
    SDL_FreeSurface(surface_spaceship);
    if (texture_spaceship == NULL) {destroy(window, render, texture_bg, NULL, NULL); setError("texture_bg == NULL");}
    // ====================================================================================================

    // ====================================================================================================
    font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 100);
    SDL_Rect rect_score = {0, 0, 75, 100};
    SDL_Color score_color = {255,255,255,255};
    char str_score[10];
    // ====================================================================================================

    // ====================================================================================================
    SDL_Surface *surface_timer = NULL;
    SDL_Texture *texture_timer = NULL;
    SDL_Color color_timer = {255,255,255,255};
    SDL_Rect rect_timer = {10, 100, 75, 50};
    char str_timer[5];
    chrono timer = {0, 0, 0, 0, 0};
    sprintf(str_timer, "%d%d:%d%d", timer.minuts1, timer.minuts2, timer.seconds1, timer.seconds2);
    // ====================================================================================================

    // ====================================================================================================
    SDL_Surface *surface_asteroid = IMG_Load("../meteor.png");
    if (surface_asteroid == NULL) {destroy(window, render, texture_bg, texture_spaceship, NULL); setError("t_m == NULL");}

    SDL_Texture *texture_ast = SDL_CreateTextureFromSurface(render, surface_asteroid);
    SDL_FreeSurface(surface_asteroid);
    if (texture_ast == NULL) {destroy(window, render, texture_bg, texture_spaceship, NULL); setError("t_a == NULL");}
    // ====================================================================================================


    // ====================================================================================================
    SDL_Rect rect_image1 = {0,0,1080,720};
    SDL_Rect rect_image2 = {0, -720, 1080, 720};

    SDL_Rect rect_spaceship = {(WINDOW_WIDTH+50)/2, (WINDOW_HEIGHT+50)/2, 50, 50};

    Munition_Handler handler = initHandler(rect_spaceship);
    
    Meteor_Handler m_handler = initMeteorHandler();
    importImage(&m_handler, texture_ast);
    // ====================================================================================================
    
    
    SDL_bool started = SDL_TRUE;
    while (started)
    {
        start = SDL_GetTicks();
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                started = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                keys[event.key.keysym.scancode] = SDL_TRUE;
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) active = 1;
                break;

            case SDL_KEYUP:
                keys[event.key.keysym.scancode] = SDL_FALSE;
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && active)
                {
                    for (int i = 0; i < handler.munitions_number; i++)
                    {
                        if (handler.munitions[i].available == 0)
                        {
                            handler.munitions[i].pos.x = rect_spaceship.x+((rect_spaceship.w-handler.munitions[i].pos.w) / 2);
                            handler.munitions[i].pos.y = rect_spaceship.y;
                            handler.munitions[i].available = 1;
                            break;
                        }
                    }
                    active = 0;
                } 
                break;
            
            default:
                break;
            }    
        }
        if (showSpaceship) 
        {
            if (keys[SDL_SCANCODE_RIGHT]) {
                if (rect_spaceship.x+10 <= 1080-50) rect_spaceship.x += 10;
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                if (rect_spaceship.x-10 >= 0) rect_spaceship.x -= 10;
            }
            if (keys[SDL_SCANCODE_DOWN]) {
                if (rect_spaceship.y+10 <= 720-50) rect_spaceship.y += 10;
            }
            if (keys[SDL_SCANCODE_UP]) {
                if (rect_spaceship.y-10 >= 0) rect_spaceship.y -= 10;
            }
        }
    


        if (showBackground(render, texture_bg, &rect_image1, &rect_image2) != 0) 
        { destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("showBackground()");}
        updateBackground(&rect_image1, &rect_image2);

        check_munition(&handler, rect_spaceship);
        if (show_munition(handler, render, rect_spaceship) != 0)
        { destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("show_munition()");}
        update_munition(&handler);
    
        if (showSpaceship)
        {
            if (drawSpaceShip(render, texture_spaceship, &rect_spaceship) != 0) 
            { destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("drawSpacesShip()");}
        }
        

        checkMeteors(&m_handler);
        if (drawMeteors(render, &m_handler) != 0)
        { destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("drawSpacesShip()"); }
        updateMeteors(&m_handler);


        //if (drawDebugRect(render, rect_spaceship, m_handler) != 0) 
        //{ destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("drawDebugRect()"); }


        if (drawScore(render, text, texture_score, font, &score, str_score, score_color, rect_score) != 0)
        {   TTF_CloseFont(font); SDL_FreeSurface(text); SDL_DestroyTexture(texture_score);
            destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("drawDebugRect()"); 
        }

        if (drawTimer(render, font, surface_timer, texture_timer, str_timer, color_timer, rect_timer) != 0)
        {
            TTF_CloseFont(font); SDL_FreeSurface(text); SDL_DestroyTexture(texture_score);
            destroy(window, render, texture_bg, texture_spaceship, texture_meteor); setError("drawDebugRect()");
        }
        updateTimer(&timer, &timer.timeMillis, str_timer);


        collidBullet(&m_handler, &handler, rect_spaceship, &score);

        if (collideSpaceShip(&m_handler, rect_spaceship))
        {
            is_explosion = 1;
            showSpaceship = 0;
        }

        if (is_explosion) {
            //show_boom(render, texture_spaceship, rect_spaceship, &explosion_line, &explosion_col, &timePerFrame, &is_explosion);
            printf("perdu !\n");
            started = 0;
        }
        
        SDL_RenderPresent(render);

        fps60(start);
        end = SDL_GetTicks();
        timer.timeMillis += (end-start);
        
    }

    destroy(window, render, texture_bg, texture_spaceship, texture_meteor);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}