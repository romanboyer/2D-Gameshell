#include "../header/map_base.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../header/windows_settings.h" 
#include "../header/state.h"
#include <SDL_ttf.h> 
#include <SDL_mixer.h>

//////////////////////////////GESTION FONCTION MAP 1/////////////////////////////////

//Creation des rectangles pour affichage elements de map non gérés par les matrices 
SDL_Rect house={830,460,128,192};
SDL_Rect castle={64,0,320,256};
SDL_Rect sign1={1216,480,55,55};

///Variables pour l'affichage des arbres
#define MAX_ARBRES 100
int nombreArbresD = 46; // Nombre d'arbres dans le tableau

// Fonction pour dessiner la map 1
void draw_map_1(SDL_Renderer *renderer, const int map[ROWS][COLS]) {
    //Chargement des textures
    SDL_Texture *water_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Water/Water1.png", renderer);
    SDL_Texture *ground_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/autumn.png", renderer);
    SDL_Texture *goalpoint_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/CheckPoint/ground_goal.png", renderer);
    SDL_Texture *sign_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Deco/sign.png", renderer);
    SDL_Texture *tree_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/autumtree.png", renderer);
    SDL_Texture *road_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/road_aut.png", renderer);
    SDL_Texture *flower_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/fleurs.png", renderer);
    SDL_Texture *house_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Factions/Knights/Buildings/House/House_Yellow.png", renderer);
    SDL_Texture *castle_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Factions/Knights/Buildings/Castle/Castle_Yellow.png", renderer);
    
 
    //Positions des arbres (utilisation simmilaire à la fonction de map_base.c)
    TreePosition arbres[MAX_ARBRES] = {
        {650,360},
        {600,360},
        {550,360},
        {500,360},
        {450,360},
        {650,232},
        {600,232},
        {550,232},
        {500,232},
        {450,232},
        {400,232},
        {350,232},
        {300,232},
        {275,264},
        {780,420},
        {830,420},
        {880,420},
        {930,420},
        {980,420},
        {1030,420},
        {1080,420},
        {1130,420},
        {1180,420},
        {780,460},
        {780,500},
        {780,540},
        {780,704},
        {830,704},
        {880,704},
        {930,704},
        {980,704},
        {1030,704},
        {1080,704},
        {1130,704},
        {1180,704},
        {1230,704},
        {1280,704},
        {1330,704},
        {1380,704},
        {0,344},
        {0,404},
        {0,524},
        {0,584},
        {0,644},
        {0,704},
        {64,584},
        
       
       
    };
    
    SDL_Rect tile;
    tile.w = 64;
    tile.h = 64;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 22; j++) {
            tile.x = j * 64;
            tile.y = i * 64;
            ///Attribution des textures selon les numéros de case
            switch (map[i][j]) {
                case 1:
                    SDL_RenderCopy(renderer, water_texture, NULL, &tile);
                    break;
                case 6:
                    SDL_RenderCopy(renderer, ground_texture, NULL, &tile);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, goalpoint_texture, NULL, &tile);
                    break;
                case 4:
                    SDL_RenderCopy(renderer,flower_texture,NULL,&tile);
                    break;
                case 5:
                    SDL_RenderCopy(renderer,road_texture,NULL,&tile);
                    break;
                
            }
        }
    }
    
    

    //Dessin des textures
    afficherArbres(renderer, tree_texture, arbres, nombreArbresD);
    SDL_RenderCopy(renderer, house_texture,NULL,&house);
    SDL_RenderCopy(renderer, castle_texture,NULL,&castle);
    SDL_RenderCopy(renderer, sign_texture,NULL,&sign1);

    //draw_grid(renderer); (fonction affichage grille blanche 1408x768 de petits carreaux de 64x64 pour aider le design de la map)

    // Nettoyage des textures
    SDL_DestroyTexture(ground_texture);
    SDL_DestroyTexture(water_texture);
    SDL_DestroyTexture(sign_texture);
    SDL_DestroyTexture(goalpoint_texture);
    SDL_DestroyTexture(tree_texture);
    SDL_DestroyTexture(flower_texture);
    SDL_DestroyTexture(road_texture);
    SDL_DestroyTexture(house_texture);
    SDL_DestroyTexture(castle_texture);
    
    
}











