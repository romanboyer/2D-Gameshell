#include "../header/map_base.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../header/windows_settings.h" 
#include "../header/state.h"
#include <SDL_ttf.h> 
#include <SDL_mixer.h>

SDL_Rect map_3={0,0,1408,768};
SDL_Rect script={0, 600, 1408, 130};

void draw_map_3(SDL_Renderer *renderer){


    
    SDL_Texture *map_3_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/maplast.png", renderer);
    SDL_Texture *script_texture = load_texture("/Users/romanboyer/2Dgameshell/fond-ecran-abstrait-noir-grunge-photo-gratuit_1340-33834.jpg.avif", renderer);

    SDL_RenderCopy(renderer, map_3_texture,NULL,&map_3);
    SDL_RenderCopy(renderer,script_texture,NULL,&script);
    
    
    SDL_DestroyTexture(map_3_texture);

   
    
}
