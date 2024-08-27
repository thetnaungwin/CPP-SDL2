//g++ -I src/include -L src/lib main.cpp -o main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
using namespace std;

const int Width=1e3;
const int Height=6e2;
bool GameRunning=true;
void Initialization();
void Renderer(SDL_Renderer* renderer);
void Text(SDL_Renderer* renderer,string message, string fontFilePath, int fontSize,int x, int y);
void playMusic(string filePath,int loops);
void imageRender(SDL_Renderer* renderer, string imagePath);

int WinMain(int argc, char* argv[]){
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    SDL_Event e;
    
    Initialization();
    window=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width, Height, SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);

    while (GameRunning)
    {
        Renderer(renderer);
        while (SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT){
                GameRunning=false;
            }
                
            switch (e.key.keysym.sym)
                {
                case SDLK_1:
                    playMusic("music/stranger-things.MP3", -1);
                    break;
                case SDLK_2:
                    playMusic("music/main_theme.mp3", -1);
                    break;
                case SDLK_p:
                    Mix_PauseMusic();
                    break;
                case SDLK_r:
                    Mix_ResumeMusic();
                    break;
                }
        }
    };
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   TTF_Quit();
   SDL_Quit();
    return 0;
};
//Function
void Initialization(){
    int flag=IMG_INIT_PNG;
    int initialStatus=IMG_Init(flag);
    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"SDL could not be initialized"<<SDL_GetError()<<endl;
    }else if(TTF_Init()<0){
        cout<<"Text is not ready to run."<<TTF_GetError()<<endl;
    }else if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        cout<<"Music is not ready to run."<<Mix_GetError()<<endl;
    }else if((initialStatus & flag) != flag){
        cout<<"Image is not ready to run."<<IMG_GetError()<<endl;
    }else{
        cout<<"SDL video system is ready to go\n";
    };
};
void Renderer(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    Text(renderer,"Leave me alone", "font/ARIAL.TTF", 50, 200, 100);
    imageRender(renderer,"image/img.jpg");

    SDL_RenderPresent(renderer);
};
void Text(SDL_Renderer* renderer,string message, string fontFilePath, int fontSize,int x, int y){
   SDL_Color color={0,0,0,0};
   TTF_Font* font=TTF_OpenFont(fontFilePath.c_str(), fontSize);
   SDL_Surface* surface=TTF_RenderText_Solid(font, message.c_str(), color);
   SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
   SDL_Rect box={x,y, surface->w, surface->h};

   SDL_RenderCopy(renderer,texture,NULL,&box);
   TTF_CloseFont(font);
   SDL_DestroyTexture(texture);
   SDL_FreeSurface(surface);
};
void playMusic(string filePath,int loops){
    Mix_Music* music=nullptr;
    music=Mix_LoadMUS(filePath.c_str());
    Mix_PlayMusic(music, loops);
};
void imageRender(SDL_Renderer* renderer, string imagePath){
   SDL_Surface* image=IMG_Load(imagePath.c_str());
   SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
   SDL_Rect boxForImg={200, 200, 400 , 300};
   SDL_RenderCopy(renderer,texture,NULL,&boxForImg); 

   SDL_DestroyTexture(texture);
   SDL_FreeSurface(image);
};