#include "../header/map_base.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../header/windows_settings.h"
#include "../header/state.h"
#include <SDL_mixer.h>
#include <stdbool.h>


//(fonction affichage grille blanche 1408x768 de petits carreaux de 64x64 pour aider le design de la map)
void draw_grid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Couleur blanche
    for (int x = 0; x <= 1408; x += 64) { // Lignes verticales
        SDL_RenderDrawLine(renderer, x, 0, x, 768);
    }
    for (int y = 0; y <= 768; y += 64) { // Lignes horizontales
        SDL_RenderDrawLine(renderer, 0, y, 1408, y);
    }
}

//Variables pour le chevalier
SDL_Texture* knight_texture = NULL;
SDL_Rect knight_src_rect = {0, 0, 192, 192};  // Sprite initial
SDL_Rect knight_dest_rect; 

//Fonction pour charger une texture
SDL_Texture* load_texture(const char *path, SDL_Renderer *renderer) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (!texture) {
        printf("Erreur de chargement de la texture %s : %s\n", path, IMG_GetError());
    }
    return texture;
}


// Creation des rectangles elements non gérés par les matrices 
SDL_Rect sign = {320, 416, 55, 55}; 
SDL_Rect bush = {377, 448, 64, 64};
//SDL_Rect redbigchamp = {760, 360, 64, 64}; // Position et taille du gros champignon rouge


//////Affichage des arbres facilité en vu du nombre d'arbre à afficher
#define MAX_ARBRES 100
int nombreArbres = 12; // Nombre d'arbres dans le tableau

void afficherArbres(SDL_Renderer* renderer, SDL_Texture* tree_texture, TreePosition* arbres, int nombreArbres) {
    SDL_Rect tree;
    for (int i = 0; i < nombreArbres; i++) {
        tree.x = arbres[i].x;
        tree.y = arbres[i].y;
        tree.w = 45; // Largeur
        tree.h = 79; // Hauteur
        SDL_RenderCopy(renderer, tree_texture, NULL, &tree);
    }
}



// Fonction pour dessiner la carte de base
void draw_map(SDL_Renderer *renderer, const int map[ROWS][COLS]) {
    
    //Chargement des textures
    SDL_Texture *water_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Water/Water1.png", renderer);
    SDL_Texture *ground_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/Ground2.png", renderer);
    SDL_Texture *goalpoint_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/CheckPoint/ground_goal.png", renderer);
    SDL_Texture *sign_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Deco/sign.png", renderer);
    SDL_Texture *redbigchamp_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Deco/03.png", renderer);
    SDL_Texture *fire_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Effects/Fire/Fire.png", renderer);
    SDL_Texture *tree_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/trees.png", renderer);
    SDL_Texture *road_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/Chemin.png", renderer);
    SDL_Texture *flower_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Terrain/Ground/fleurs.png", renderer);
    SDL_Texture *bush_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Deco/08.png", renderer);
    

    
    //Positions des arbres
    TreePosition arbres[MAX_ARBRES] = {
        {305, 0},
        {350, 0},
        {260, 0},
        {896, 0},
        {941, 0},
        {986, 0},
        {1031, 0},
        {1076, 0},
        {1076, 40},
        {1121, 40},
        {305, 40},
        {260, 40},
    };
    
    
    SDL_Rect tile;
    tile.w = 64;
    tile.h = 64;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 22; j++) {
            tile.x = j * 64;
            tile.y = i * 64;

            switch (map[i][j]) {
                case 1:
                    SDL_RenderCopy(renderer, water_texture, NULL, &tile);
                    break;
                case 2:
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
    afficherArbres(renderer, tree_texture, arbres, nombreArbres);
    SDL_RenderCopy(renderer, bush_texture, NULL, &bush);
    SDL_RenderCopy(renderer, sign_texture, NULL, &sign);
    
    //SDL_RenderCopy(renderer, redbigchamp_texture, NULL, &redbigchamp);


    //draw_grid(renderer);

    // Nettoyage des textures
    SDL_DestroyTexture(water_texture);
    SDL_DestroyTexture(ground_texture);
    SDL_DestroyTexture(sign_texture);
    SDL_DestroyTexture(goalpoint_texture);
    //SDL_DestroyTexture(redbigchamp_texture);
    SDL_DestroyTexture(tree_texture);
    SDL_DestroyTexture(flower_texture);
    SDL_DestroyTexture(road_texture);
    SDL_DestroyTexture(bush_texture);
    
}

// Initialisation du chevalier
void init_knight(SDL_Renderer *renderer) {
    knight_texture = load_texture("/Users/romanboyer/2Dgameshell/TinySwords/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png", renderer);
    if (!knight_texture) {
        printf("Erreur lors du chargement du chevalier\n");
        return;
    }
}

/////////Fonction pour gérér les zones spéciales non pratiquables par le chevalier 
int is_in_special_zone(int x, int y, const int map[ROWS][COLS]) {
    // Calcul des coordonnées du centre réel du rectangle
    int centerX = x + knight_dest_rect.w / 2; // Centre horizontal
    int centerY = y + knight_dest_rect.h / 2; // Centre vertical

    // Conversion en coordonnées de tuile
    int tileX = centerX / 64;
    int tileY = centerY / 64;

    // Vérification si la tuile centrale est de type 1 ou 6
    if (tileX >= 0 && tileX < COLS && tileY >= 0 && tileY < ROWS) {
        int tileType = map[tileY][tileX];
        return (tileType == 1 || tileType == 6 || tileType == 9); // Retourne vrai si la tuile est de type 1 ou 6 ou 9
    }

    return 0; // En dehors des limites de la carte
}


//Définir les limites globales de la zone spéciale (zone de collision)
int ZONE_X_MIN;
int ZONE_Y_MIN;
int ZONE_X_MAX;
int ZONE_Y_MAX;

///Meme systeme que is_in_special_zone mais gestion des zones de collisions non en fonction des tuiles de matrices mais en fonction des pixels définis dans ZONE_X_MIN ....
int is_in_pixel_special_zone(int x, int y) {
    // Vérifie si les coordonnées (x, y) sont dans la zone spéciale
    if (x >= ZONE_X_MIN && x <= ZONE_X_MAX && y >= ZONE_Y_MIN && y <= ZONE_Y_MAX) {
        return 1; // Dans la zone spéciale
    }
    return 0; // En dehors de la zone spéciale
}


///Meme systeme que les deux fonctions précédente mais detection uniquement de la tuile "mission" permettant la teleportation de map 1 vers map 2. Possibilité d'utiliser une zone special pixel et de supprimer l'utilisation de cette tuile 
int is_in_mission_zone(int x, int y, const int map[ROWS][COLS]) {
    // Coordonnées de la tuile sur laquelle le chevalier devrait se trouver
    int tileX = x / 64; 
    int tileY = y / 64; 

    // Vérifie si la tuile correspond à une tuile spéciale
    if (tileX >= 0 && tileX < COLS && tileY >= 0 && tileY < ROWS) {
        if (map[tileY][tileX] == 4 || map[tileY][tileX] == 3) {
            return 1;
        }
    }
    return 0; // Pas sur une tuile spéciale ou pas aligné
}

// Variables globales pour indiquer si la position initiale est définie
bool knight_position_initialized_map = false;
bool knight_position_initialized_map_1 = false;
bool knight_position_initialized_map_2 = false;

Uint32 lastSoundTime = 0;  // Déclaration globale ou dans la fonction update_and_draw_knight



////////////////////DEPLACEMENT CHEVALIER///////////////////////////////////

// Mise à jour du chevalier avec gestion des événements
void update_and_draw_knight(SDL_Renderer *renderer, const Uint8 *keyState, const int map[ROWS][COLS]) {
    int knight_speed = 4;
    if (currentState==GAME_MAP_2){
        knight_speed = 6;
    }


    // Récupérer le temps actuel en millisecondes
    Uint32 currentTime = SDL_GetTicks();

    
    // Définir la position initiale du chevalier une seule fois par état
    if (currentState == GAME_MAP && !knight_position_initialized_map) {
        knight_dest_rect = (SDL_Rect){128, 128, 64, 64}; // Position pour GAME_MAP
        knight_position_initialized_map = true; // Position initialisée
    }
    if (currentState == GAME_MAP_1 && !knight_position_initialized_map_1) {
        knight_dest_rect = (SDL_Rect){1320, 512, 64, 64}; // Position pour GAME_MAP_1
        knight_position_initialized_map_1 = true; // Position initialisée
    } 
    if (currentState == GAME_MAP_2 && !knight_position_initialized_map_2) {
        knight_dest_rect = (SDL_Rect){640, 702, 64, 64}; // Position pour GAME_MAP_1
        knight_position_initialized_map_2 = true; // Position initialisée
    }                                                          

    // Stockage de la position initiale
    int old_x = knight_dest_rect.x;
    int old_y = knight_dest_rect.y;

    // Gestion des mouvements
    if (keyState[SDL_SCANCODE_UP] && knight_dest_rect.y > 0) {
        runsound = 1;
        knight_dest_rect.y -= knight_speed;
        knight_src_rect.y = 192; // Ligne 192 pour les sprites gauche
        knight_src_rect.x += 192; // Avance dans la ligne
        knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
    }
    if (keyState[SDL_SCANCODE_DOWN] && knight_dest_rect.y + knight_dest_rect.h < 768) {
        runsound = 1;
        knight_dest_rect.y += knight_speed;
        knight_src_rect.y = 192; // Ligne 192 pour les sprites gauche
        knight_src_rect.x += 192; // Avance dans la ligne
        knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
    }
    if (keyState[SDL_SCANCODE_LEFT] && knight_dest_rect.x > 0) {
        runsound = 1;
        knight_dest_rect.x -= knight_speed;
        knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
        knight_src_rect.x += 192; // Avance dans la ligne
        knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
    }
    if (keyState[SDL_SCANCODE_RIGHT] && knight_dest_rect.x + knight_dest_rect.w < 1408) {
        runsound = 1;
        knight_dest_rect.x += knight_speed;
        knight_src_rect.y = 192; // Ligne 192 pour les sprites droite
        knight_src_rect.x += 192;
        knight_src_rect.x %= 192 * 6;
    }

    // Vérification de l'intervalle entre deux sons
    if (runsound == 1 && (currentTime - lastSoundTime) > 240) {  // 100 ms de délai
        Mix_PlayChannel(3, sounds[2], 0);
        Mix_Volume(3, MIX_MAX_VOLUME / 1.5);
        lastSoundTime = currentTime;  // Mise à jour du temps
        runsound = 0;  // Réinitialisation pour éviter les répétitions rapides
    }

    

    // Vérification si le chevalier entre dans une zone mission
    if (is_in_mission_zone(knight_dest_rect.x + knight_dest_rect.w/2, knight_dest_rect.y + knight_dest_rect.h/2, map)) {
        if(currentState==GAME_MAP_1){
            currentState=GAME_MAP_2 ;  
        }
        if(currentState==GAME_MAP){
            currentState=GAME_MAP_1 ;
        }  
    }
    if (is_in_special_zone(knight_dest_rect.x, knight_dest_rect.y, map)){
        // Annulation du mouvement
        knight_dest_rect.x = old_x;
        knight_dest_rect.y = old_y;
    }


    //////////////ZONE COLLISION MAP SELON ETAT DU JEU///////////////////////////////

    if (currentState==GAME_MAP){
        // Définir les limites globales de la zone spéciale
        ZONE_X_MIN = 278;
        ZONE_Y_MIN = 375;
        ZONE_X_MAX = 355;
        ZONE_Y_MAX = 444;
    }
    if (currentState==GAME_MAP_1){
        // Définir les limites globales de la zone spéciale
        ZONE_X_MIN = 1184;
        ZONE_Y_MIN = 480;
        ZONE_X_MAX = 1239;
        ZONE_Y_MAX = 512;
    }
    if (currentState==GAME_MAP_2){
        // Définir les limites globales de la zone spéciale
        ZONE_X_MIN = 940;
        ZONE_Y_MIN = 190;
        ZONE_X_MAX = 1289;
        ZONE_Y_MAX = 280;
    }
    if (currentState==GAME_MAP_2 && mission2==1 && mission3==0){
        // Définir les limites globales de la zone spéciale
        ZONE_X_MIN = 665;
        ZONE_Y_MIN = 130;
        ZONE_X_MAX = 735;
        ZONE_Y_MAX = 183;
    }

    if (is_in_pixel_special_zone(knight_dest_rect.x, knight_dest_rect.y)) {
        // Annulation du mouvement
        knight_dest_rect.x = old_x;
        knight_dest_rect.y = old_y;
        
        if (currentState==GAME_MAP) {
            affiche_map_base = 1;
        }
        if (currentState==GAME_MAP_1) {
            affiche_map_1 = 1;
        }
        if (currentState==GAME_MAP_2) {
            affiche_map_2 = 1;
        }
        if (currentState==GAME_MAP_2 && mission2==1) {
            affiche_map_3 = 1;
        }
    }
    
    ///////////////////GESTION DU DEPLACEMENT AUTOMATIQUE DU CHEVALIER LORS DU SUCCES DE LA MISSIONS 1////////////////////////////

    //Flag pour gestion des if dans le deplacement du chevalier
    static int pass = 0;

    if (currentState==GAME_MAP_1 && passage_chateau==1){
        if (pass==0){
            if(knight_dest_rect.x>975){
            runsound = 1;
            knight_dest_rect.x -= 2*knight_speed;
            knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
            knight_src_rect.x += 192; // Avance dans la ligne
            knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            
            }
            if(knight_dest_rect.y<645 && knight_dest_rect.x<975){
                runsound = 1;
                knight_dest_rect.y += 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 192 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames  
            }
            if(knight_dest_rect.y>645 && knight_dest_rect.x>710){
                runsound = 1;
                knight_dest_rect.x -= 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            }
            if(knight_dest_rect.y>645 && knight_dest_rect.x<710){
                pass=1;
            }
        }
        if (pass==1){
            if(knight_dest_rect.y>325){
                runsound = 1;
                knight_dest_rect.y -= 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 192 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            }
            if(knight_dest_rect.y<325 && knight_dest_rect.x>390){
                runsound = 1;
                knight_dest_rect.x -= 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames

            }
            if(knight_dest_rect.y<325 && knight_dest_rect.x<390){
                pass=2;
            }
        }
        if (pass==2){
            if(knight_dest_rect.y<450){
                runsound = 1;
                knight_dest_rect.y += 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 192 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            }
            if(knight_dest_rect.y>449 && knight_dest_rect.x>200){
                runsound = 1;
                knight_dest_rect.x -= 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            }
            if(knight_dest_rect.y>449 && knight_dest_rect.x<=200){
                pass=3;
            }
            
        }
        if (pass==3){
            if(knight_dest_rect.y>216 && knight_dest_rect.x<=200){
                runsound = 1;
                knight_dest_rect.y -= 2*knight_speed;
                knight_src_rect.y = 192; // Ligne 0 pour les sprites gauche
                knight_src_rect.x += 192; // Avance dans la ligne
                knight_src_rect.x %= 192 * 6; // Boucle sur 6 frames
            }
        }
        
    }

    /////////////////ENTREE DANS LA MAP 3 SANS L'UTILISATION D'UNE TUILE MISSION COMME DANS LA FONCTION is_in_mission_zone///////////////////////
    if(currentState==GAME_MAP_2 && passage_secret==1){
        
        if(knight_dest_rect.x == 1300){
            printf("position ok");
            currentState=GAME_MAP_3;
        }
    }


    // Dessin du chevalier
    SDL_RenderCopy(renderer, knight_texture, &knight_src_rect, &knight_dest_rect);
}











