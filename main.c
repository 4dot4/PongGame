#include <SDL2\SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


void pysic(SDL_Rect* player, SDL_Rect* ball,SDL_Rect* bot,bool* gravity,bool* direction){
    if(ball->y + ball->h >= 800)
        *gravity = false;
    else if(ball->y <= 0)
        *gravity = true;

    if(*gravity){
        ball->y += 5;
    }else{
        ball->y -= 5;
    }


    if(ball->x <= player->x + player->w && ball->y - ball->h >= player->y && ball->y <= player->y + player->h)
        *direction = false;
    else if(ball->x + ball->w >= bot->x && ball->y - ball->h >= bot->y && ball->y <= bot->y + bot->h)
        *direction = true;

    if(*direction){
        ball->x -= 3;
    }else{
        ball->x += 3;
        
    }
}
void render(SDL_Rect* player, SDL_Rect* ball,SDL_Rect* bot,SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawRect(renderer,player);

        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_RenderDrawRect(renderer,bot);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawRect(renderer,ball);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
}

int main(int argc,char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title",50,50,800,800,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
    SDL_ShowWindow(window);
    
    SDL_Rect player;
    player.h = 60;
    player.w = 10;
    player.x = 60;
    player.y = 400 - player.h / 2;
    SDL_Rect bot;
    bot.h = 60;
    bot.w = 10;
    bot.x = 730;
    bot.y = 400 - bot.h / 2;
    SDL_Rect ball;
    ball.h = 10;
    ball.w = 10;
    ball.x = 400 - ball.w;
    ball.y = 400;
    bool gravity = true;
    bool direction = true;
    bool running = true;
    while(running){
        
        
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
            const uint8_t* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_W]){
                if(player.y > 0){
                    player.y -= 10;
                }
            }
            if(state[SDL_SCANCODE_S]){
                if(player.y + player.h < 800){
                    player.y += 10;
                }
            }
            if(state[SDL_SCANCODE_UP]){
                if(bot.y > 0){
                    bot.y -= 10;
                }
            }
            if(state[SDL_SCANCODE_DOWN]){
                if(bot.y + bot.h < 800){
                    bot.y += 10;
                }
            }
            
        }
       
        pysic(&player,&ball,&bot,&gravity,&direction);
    
        render(&player,&ball,&bot,renderer);
        
        
    

        
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}   