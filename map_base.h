#ifndef MAP_BASE_H
#define MAP_BASE_H
#define ROWS 12
#define COLS 22
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Fonction pour charger une texture
SDL_Texture* load_texture(const char *path, SDL_Renderer *renderer);

// Fonction pour dessiner la carte de base
void draw_map(SDL_Renderer *renderer,const int map[ROWS][COLS]);

void draw_map_1(SDL_Renderer *renderer, const int map[ROWS][COLS]);

void draw_map_2(SDL_Renderer *renderer, const int map[ROWS][COLS]);

void draw_map_3(SDL_Renderer *renderer);

// Initialisation du chevalier
void init_knight(SDL_Renderer *renderer);

// Gestion et dessin du chevalier
void update_and_draw_knight(SDL_Renderer *renderer, const Uint8 *keyState,const int map[ROWS][COLS]);

typedef struct {
    int x;
    int y;
} TreePosition;

void draw_grid(SDL_Renderer *renderer);

void afficherArbres(SDL_Renderer* renderer, SDL_Texture* tree_texture, TreePosition* arbres, int nombreArbres);

int is_in_special_zone(int x, int y, const int map[ROWS][COLS]) ; //Eau par exemple 

int is_in_mission_zone(int x, int y, const int map[ROWS][COLS]) ; //Tiles de missions

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color);

extern int mission1; 
extern int mission2;
extern int mission3; 

extern int passage_chateau; 
extern int livre; 
extern int passage_secret; 


extern int runsound;

extern int affiche_map_base;
extern int affiche_map_1;
extern int affiche_map_2;
extern int affiche_map_3;

extern int unaffiche_map_base;
extern int unaffiche_map_1;
extern int unaffiche_map_2;
extern int unaffiche_map_3;



extern Mix_Chunk *sounds[10];


#endif






