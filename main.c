#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct i8Vector2 {
    char x, y;
} i8Vector2;

bool colisionCheck(SDL_Rect* rect_a, SDL_Rect* rect_b);

void physics(SDL_Rect* player, SDL_Rect* ball, SDL_Rect* bot, i8Vector2* ball_direction, bool *keys_pressed);
void render(SDL_Renderer *renderer, SDL_Rect *player, SDL_Rect *ball, SDL_Rect *bot);

int main(int argc, char* argv[]){
    bool keys_pressed[512];

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("title", 50, 50, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Rect player = { 60, 0, 10, 60 };
    player.y = 400 - player.h / 2;
    SDL_Rect bot = { 730, 0, 10, 60 };
    bot.y = 400 - bot.h / 2;
    SDL_Rect ball = { 0, 400, 10, 10};
    ball.x = 400 - ball.w;

    i8Vector2 ball_direction = { 1, 1 };

    bool running = true;

    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    if(!event.key.repeat){
                        keys_pressed[event.key.keysym.scancode] = true;
                    }
                    break;
                case SDL_KEYUP:
                    keys_pressed[event.key.keysym.scancode] = false;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
       
        physics(&player, &ball, &bot, &ball_direction, keys_pressed);
        render(renderer, &player, &ball, &bot);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void physics(SDL_Rect* player, SDL_Rect* ball, SDL_Rect* bot, i8Vector2* ball_direction, bool *keys_pressed){
    if(keys_pressed[SDL_SCANCODE_W]) player->y -= 3;
    if(keys_pressed[SDL_SCANCODE_S]) player->y += 3;
    if(keys_pressed[SDL_SCANCODE_UP]) bot->y -= 3;
    if(keys_pressed[SDL_SCANCODE_DOWN]) bot->y += 3;

    if(ball->y >= 800 - ball->h){
        ball_direction->y = -ball_direction->y;
    }
    if(ball->y <= 0){
        ball_direction->y = -ball_direction->y;
    }

    if(ball->x >= 1600 - ball->x){
        ball->x = 400 - ball->w / 2;
        ball->y = 400 - ball->h / 2;
    }
    if(ball->x <= 0){
        ball->x = 400 - ball->w / 2;
        ball->y = 400 - ball->h / 2;
    }

    if(colisionCheck(ball, player) || colisionCheck(ball, bot)) ball_direction->x = -ball_direction->x;

    ball->x += ball_direction->x * 3;
    ball->y += ball_direction->y * 3;
}

void render(SDL_Renderer *renderer, SDL_Rect *player, SDL_Rect *ball, SDL_Rect *bot){
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer, player);

    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    SDL_RenderDrawRect(renderer, bot);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer, ball);
    
    SDL_RenderPresent(renderer);
}

bool colisionCheck(SDL_Rect* rect_a, SDL_Rect* rect_b){
    if(rect_a->x < rect_b->x + rect_b->w
    && rect_a->x + rect_a->w > rect_b->x
    && rect_a->y < rect_b->y + rect_b->h
    && rect_a->y + rect_a->h > rect_b->y) return true;
    return false;
}