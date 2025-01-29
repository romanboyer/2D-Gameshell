#include "../header/map_base.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../header/windows_settings.h" 
#include "../header/state.h"
#include <SDL_ttf.h> 
#include <SDL_mixer.h>

//////////////////////////////GESTION FONCTION MAP 2/////////////////////////////////

//Creation des rectangles pour affichage elements de map non gérés par les matrices 

SDL_Rect box={704,162,64,64};
//SDL_Rect sign2={665,200,40,40};
SDL_Rect bibli={1169,190,120,90};
SDL_Rect bibli2={1049,190,120,90};
SDL_Rect profbibli={1255,280,30,120};
SDL_Rect profbibli2={1255,400,30,120};
SDL_Rect profbibli3={1255,520,30,120};
SDL_Rect book={1010,230,30,30};
SDL_Rect book2={1100,290,30,30};
SDL_Rect tapis={632,440,390,200};

void draw_map_2(SDL_Renderer *renderer, const int map[ROWS][COLS]){

    //Chargement des textures
    SDL_Texture *floor_texture = load_texture("/Users/romanboyer/2Dgameshell/TinyDungeonTopDown/castlefloor2.png",renderer);
    SDL_Texture *box_texture = load_texture("/Users/romanboyer/2Dgameshell/DampDungeons/Tiles/box.png",renderer);
    SDL_Texture *blackrect_texture = load_texture("/Users/romanboyer/2Dgameshell/fond-ecran-abstrait-noir-grunge-photo-gratuit_1340-33834.jpg.avif",renderer);
    //SDL_Texture *sign_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Deco/sign.png", renderer);
    SDL_Texture *bibli_texture = load_texture("/Users/romanboyer/2Dgameshell/DampDungeons/Tiles/bibli.png", renderer);
    SDL_Texture *profbibli_texture = load_texture("/Users/romanboyer/2Dgameshell/DampDungeons/Tiles/profilebibli.png", renderer);
    SDL_Texture *book_texture = load_texture("/Users/romanboyer/2Dgameshell/DampDungeons/Tiles/book.png", renderer);
    SDL_Texture *tapis_texture = load_texture("/Users/romanboyer/2Dgameshell/DampDungeons/Tiles/tapis.png", renderer);
    
    SDL_Rect tile;
    tile.w = 64;
    tile.h = 64;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 22; j++) {
            tile.x = j * 64;
            tile.y = i * 64;

            switch (map[i][j]) {
                case 8:
                    SDL_RenderCopy(renderer, floor_texture, NULL, &tile);
                    break;
                case 9:
                    SDL_RenderCopy(renderer, blackrect_texture, NULL, &tile);
                    break;
            }
        }
    }

    //Collisions avec les caisses (box) tant que la mission n'est pas validée 
    if(passage_secret!=1){
        SDL_RenderCopy(renderer,box_texture,NULL,&box);
    }
    //Livre affichés et non rangés dans la bibliothèque tant que missions non réussie
    if(livre!=1){
        SDL_RenderCopy(renderer, book_texture,NULL,&book);
        SDL_RenderCopy(renderer, book_texture,NULL,&book2);

    }

    ////////Affichages des rectangles 

    //SDL_RenderCopy(renderer, sign_texture,NULL,&sign2); 
    SDL_RenderCopy(renderer, bibli_texture,NULL,&bibli); 
    SDL_RenderCopy(renderer, bibli_texture,NULL,&bibli2);
    SDL_RenderCopy(renderer, profbibli_texture,NULL,&profbibli);
    SDL_RenderCopy(renderer, profbibli_texture,NULL,&profbibli2);
    SDL_RenderCopy(renderer, profbibli_texture,NULL,&profbibli3);
    SDL_RenderCopy(renderer, tapis_texture,NULL,&tapis);

    ////////Destruction des textures 

   // SDL_DestroyTexture(sign_texture);
    SDL_DestroyTexture(profbibli_texture);
    SDL_DestroyTexture(floor_texture);
    SDL_DestroyTexture(box_texture);
    SDL_DestroyTexture(bibli_texture);
    SDL_DestroyTexture(book_texture);
    SDL_DestroyTexture(tapis_texture);
}