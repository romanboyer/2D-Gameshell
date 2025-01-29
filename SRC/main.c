#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/map_base.h"
#include "../header/windows_settings.h"
#include <SDL_ttf.h> 
#include "../header/state.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <unistd.h> //pour utiliser sleep()
#include <stdbool.h>

///Flags missions
int mission1 = 0;
int mission2 = 0;
int mission3 = 0;

//Flags sons
int runsound = 0;

bool soundmenu = false;
bool soundmap0 = false; 
bool soundmap1 = false; 
bool soundmap2 = false;

///FLags permettant d'afficher/desafficher le terminal 
int affiche_map_base = 0;
int affiche_map_1 = 0;
int affiche_map_2 = 0;
int affiche_map_3 = 0;

int unaffiche_map_base = 0;
int unaffiche_map_1 = 0;
int unaffiche_map_2 = 0;
int unaffiche_map_3 = 0;

///Flags validation missions 1,2,3
int passage_chateau = 0;
int livre = 0;
int passage_secret = 0;



// Matrices 12x22 pour la gestion des maps (768/64=12, 1408/64=22)

//Map d'accueil
const int map_base[ROWS][COLS] = {
    {2, 2, 1, 1, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 2, 2, 2, 2, 2, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
    {1, 1, 2, 4, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 5},
    {1, 1, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
    {1, 1, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 2, 2, 2, 5, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 2, 2, 2, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


//Map 1
const int map_1[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1},
    {1, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 6, 6, 3, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6},
    {6, 6, 6, 5, 6, 6, 5, 5, 5, 5, 5, 5, 6, 1, 1, 1, 1, 1, 1, 1, 6, 6},
    {6, 6, 6, 5, 6, 6, 5, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 5, 5, 5, 5, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5},
    {6, 6, 6, 6, 6, 1, 1, 1, 6, 6, 6, 5, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 1, 1, 1, 1, 1, 6, 6, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
};

//Map 2
const int map_2[ROWS][COLS] = {
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
};


//Déclaration de la fonction SDL_ExitwithError 
void SDL_ExitwithError(const char *message);

//////////////////////GESTION EFFETS SONORES/MUSIQUES///////////////////////////////

//Define pour tableau chunk
#define NUM_SOUNDS 10

//Tableau pour stocker les effets sonores
Mix_Chunk *sounds[NUM_SOUNDS];

//Fonction pour charger les effets sonores
int load_sounds() {
    sounds[0] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/depositphotos_762313592-track-casual-pop-click-designed-menus.mp3");
    sounds[1] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/slow-whoop-bubble-pop.mp3");
    sounds[2] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/180904-woodland04-run-steps-skip-jump-clip-47486-2.mp3");
    sounds[3] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/bird-sound-249237.mp3");
    sounds[4] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/flowing-water-246403.mp3");
    sounds[5] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/button-124476 (mp3cut.net) (1).mp3");
    sounds[6] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/walkman-button-272973_M20KOzX5.mp3");
    sounds[7] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/wind-blowing-sfx-12809.mp3");
    sounds[8] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/niagara-falls-37014.mp3");
    sounds[9] = Mix_LoadWAV("/Users/romanboyer/2Dgameshell/Musique/SoundsEffects/ticking-clock-sound-effect-1-mp3-edition-264451.mp3");
    
    //Vérifier si le chargement a échoué
    for (int i = 0; i < NUM_SOUNDS; i++) {
        if (!sounds[i]) {
            printf("Erreur de chargement du son %d : %s\n", i, Mix_GetError());
            return -1; //Échec du chargement
        }
    }

    return 0; //Succès
}

//Define pour tableau music
#define NUM_MORCEAUX 3

//Tableau pour stocker les bandes musique
Mix_Music *morceaux[NUM_MORCEAUX];

//Fonction pour charger les morceaux musique
int load_morceaux(){
    morceaux[0]= Mix_LoadMUS("/Users/romanboyer/2Dgameshell/Musique/BandeSonnore/waiting-time-175800.mp3");
    morceaux[1]= Mix_LoadMUS("/Users/romanboyer/2Dgameshell/Musique/BandeSonnore/puzzle-game-bright-casual-video-game-music-249202.mp3");
    morceaux[2]= Mix_LoadMUS("Musique/BandeSonnore/wondrous-waters-119518.mp3");
    //Vérifier si le chargement a échoué
    for (int i = 0; i < NUM_MORCEAUX; i++) {
        if (!morceaux[i]) {
            printf("Erreur de chargement du son %d : %s\n", i, Mix_GetError());
            return -1; //Échec du chargement
        }
    }

    return 0; //Succès

}



//////////////////////////GESTION AFFICHAGE TEXTE ET INPUT////////////////////////////////////////

//Fonction pour afficher du texte avec SDL_ttf
void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        printf("Erreur de création de surface : %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur de création de texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

//Etat du jeu initialisé au menu 
GameState currentState = GAME_MENU;


int main (int argc, char **argv)
{
    (void)argc; //Supprimer l'avertissement 'unused parameter'
    (void)argv;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int GameIsRunning = 1;

    /////////////////////////////////Initialisation de SDL avec les sous-systèmes VIDEO et AUDIO
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError()); //Affiche une erreur si l'initialisation échoue
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        SDL_Log("Erreur initialisation SDL_image : %s", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1) {
        printf("Erreur SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    //Initialisation de SDL_mixer avec une configuration audio : Fréquence de 44100 Hz (standard pour l'audio), format par défaut, 2 canaux (stéréo), taille du buffer de 2048
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur SDL_mixer: %s\n", Mix_GetError()); // Affiche une erreur si l'initialisation échoue
        SDL_Quit(); // Ferme SDL proprement
        return -1;
    }

    // Charger les chunks
    if (load_sounds() == -1) {
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    // Charger les bandes musicales
    if (load_morceaux() == -1) {
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    /////////////////////////////////Création fenêtre
    window = SDL_CreateWindow("GameShell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEN, HEIGHT_SCREEN, 0);
    if (window == NULL)
    {
        SDL_ExitwithError("Création fenêtre échouée");
    }

    // Création renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_ExitwithError("Création renderer échouée");
    }

    
    /////////////////////////////////GESTION ECRAN D'ACCUEIL

    // Charger l'image de fond (accueil)
    SDL_Surface* backgroundSurface = IMG_Load("/Users/romanboyer/Downloads/GAMESHELL.png");
    if (!backgroundSurface) {
        SDL_Log("Erreur chargement de l'image de fond: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Création de sa surface
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        SDL_Log("Erreur création texture de fond: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Rectangle pour le bouton play
    SDL_Rect playButton = {604, 260, 200, 75};  // x, y, largeur, hauteur
    //SDL_Rect exitButton = {604, 230, 100, 75};
    
    // Charger l'image du bouton play 
    SDL_Surface* buttonSurface = IMG_Load("/Users/romanboyer/2Dgameshell/Boutons/Capture_d_écran_2024-12-12_à_23.27.24-removebg-preview.png");
    if (!buttonSurface) {
        SDL_Log("Erreur chargement de l'image du bouton: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture) {
        SDL_Log("Erreur création texture bouton: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /*
     // Charger l'image du bouton exit 
    SDL_Surface* buttonSurface2 = IMG_Load("/Users/romanboyer/2Dgameshell/Boutons/icons8-sortie-100.png");
    if (!buttonSurface2) {
        SDL_Log("Erreur chargement de l'image du bouton: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_FreeSurface(buttonSurface2);
    if (!buttonTexture) {
        SDL_Log("Erreur création texture bouton: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    */
   
    
    // Chargement de la police dialogues
    TTF_Font *font = TTF_OpenFont("/Users/romanboyer/2Dgameshell/Walter_Turncoat/WalterTurncoat-Regular.ttf", 20);
    if (!font) {
        printf("Erreur chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Chargement de la police réponse utilisateur
    TTF_Font *font_term = TTF_OpenFont("/Users/romanboyer/2Dgameshell/sf-mono/SFMonoRegular.otf", 20);
    if (!font_term) {
        printf("Erreur chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    //Rectangle Terminal pour les missions
    SDL_Rect terminal = {0, 600, 1408, 130};
    SDL_Texture *terminal_texture = load_texture("/Users/romanboyer/2Dgameshell/fond-ecran-abstrait-noir-grunge-photo-gratuit_1340-33834.jpg.avif", renderer);
    
    //SDL_Rect terminalblanc = {0, 600, 1408, 130};
    //SDL_Texture *terminalblanc_texture = load_texture("/Users/romanboyer/2Dgameshell/Fond_blanc.svg", renderer);
    
    
    
    //Rectangle Information pour les dialogues autres que missions
    SDL_Rect information = {0, 600, 1408, 130};
    SDL_Texture *information_texture = load_texture("/Users/romanboyer/2Dgameshell/fond-ecran-abstrait-noir-grunge-photo-gratuit_1340-33834.jpg.avif", renderer);

    // Variables de saisie
    static char inputText[256] = ""; // Texte saisi

    int running = 1;          // Boucle principale
    
    SDL_Color WhiteTextColor = {255, 255, 255, 255}; //Couleur blanche
    SDL_Color BlackTextColor = {0, 0, 0, 255}; // Couleur noir
    

    //Commandes correctes à comparer aux réponses utilisateur de chaque missions
    const char *correctCommand = "cd Chateau";
    const char *correctCommand2 = "mv Livre1 Livre2 Bibliotheque";
    const char *correctCommand3 = "rm Caisses";

    //Input utilisateur
    SDL_StartTextInput();

    //Gestion des channels sur lesquelles sont diffusés les sons
    Mix_Volume(5,MIX_MAX_VOLUME/5);
    Mix_Volume(6,MIX_MAX_VOLUME*2);

    //Variable de detection de la position de la souris 
    int isMouseOverButton=0;
    while (GameIsRunning)
    {
        // Gestion des événements
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                GameIsRunning = 0;
            } else if (event.type == SDL_TEXTINPUT) {
                // Ajouter le texte saisi à inputText
                if (strlen(inputText) + strlen(event.text.text) < sizeof(inputText) - 1) {
                    strcat(inputText, event.text.text);
                }
            } if (event.type == SDL_KEYDOWN && mission1==1 && mission2==0) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    // Supprimer le dernier caractère
                    inputText[strlen(inputText) - 1] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Comparer la réponse utilisateur à la commande correcte
                    printf("Saisie utilisateur : %s\n", inputText);
                    if (strcmp(inputText, correctCommand) == 0) {
                        printf("Commande correcte : Passage au Chateau !\n");
                        passage_chateau = 1; 
                        Mix_PlayChannel(5, sounds[5], 0);
                        inputText[0] = '\0';

                    } else {
                        printf("Commande incorrecte.\n");
                        inputText[0] = '\0';
                    }
                }
            } if (event.type == SDL_KEYDOWN && mission3==1) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    // Supprimer le dernier caractère
                    inputText[strlen(inputText) - 1] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Comparer la réponse utilisateur à la commande correcte
                    printf("Saisie utilisateur : %s\n", inputText);
                    if (strcmp(inputText, correctCommand3) == 0) {
                        printf("Commande correcte : Passage secret ok !\n");
                        Mix_PlayChannel(5, sounds[5], 0);
                        passage_secret = 1; 
                        
                        inputText[0] = '\0';
                    } else {
                        printf("Commande incorrecte.\n");
                        inputText[0] = '\0';
                    }
                }
            } if (event.type == SDL_KEYDOWN && mission2==1 && mission3 == 0) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    // Supprimer le dernier caractère
                    inputText[strlen(inputText) - 1] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Comparer la réponse utilisateur à la commande correcte
                    printf("Saisie utilisateur : %s\n", inputText);
                    if (strcmp(inputText, correctCommand2) == 0) {
                        Mix_PlayChannel(10, sounds[5], 0);
                        printf("Commande correcte : Livre ok !\n");
                        inputText[0] = '\0';
                        livre = 1; 
                        Mix_PlayChannel(5, sounds[5], 0);
                    } else {
                        printf("Commande incorrecte.\n");
                        inputText[0] = '\0';
                    }
                }
            } if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && affiche_map_base==1){
                unaffiche_map_base=1; //Si bouton entrer préssé et que l'affichage du rectangle terminal de la map 1 est affiché alors "desafficher le rectangle" en mettant le flag unaffiche à 1
                Mix_PlayChannel(6, sounds[6], 0);
            } if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && affiche_map_1==1){
                mission1=1; //Idem que précedemment ici avec l'affichage du script mission 1
                unaffiche_map_1 = 1;
                Mix_PlayChannel(6, sounds[6], 0);
            } if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && affiche_map_2==1){
                mission2=1; //Idem
                unaffiche_map_2 = 1;
                Mix_PlayChannel(5, sounds[6], 0); //Effet sonore
            } if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && affiche_map_3==1){
                mission3=1; //Idem
                unaffiche_map_3=1;
                Mix_PlayChannel(6, sounds[6], 0);//Effet sonore 
            }

            /////////////GESTION EVENNEMENT BOUTON PLAY 
            if (currentState == GAME_MENU)
            {
                //Detecter passage de la souris
                if (event.type == SDL_MOUSEMOTION) {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;

                    if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
                        mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
                        SDL_Log("La souris est au-dessus du bouton !");

                        if (!isMouseOverButton) { // Si ce n'est pas déjà détecté
                            isMouseOverButton = 1;
                            // Agrandissement du bouton
                            playButton.x -= 5;
                            playButton.y -= 5;
                            playButton.w += 10;
                            playButton.h += 10;
                            //Effet sonore
                            Mix_PlayChannel(-1,sounds[1],0);//Effet sonore
                        
                        }
                    }
                    else {
                        if (isMouseOverButton) { // Si la souris quitte le bouton
                            isMouseOverButton = 0;
                            // Rétablir la taille d'origine
                            playButton.x = 604;
                            playButton.y = 260;
                            playButton.w = 200;
                            playButton.h = 75;
                            
                        }
                    }
                    
                }
                // Détecter clic sur le bouton
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    // Vérifier si le clic est sur le bouton Play
                    if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
                        mouseY >= playButton.y && mouseY <= playButton.y + playButton.h)
                    {
                        printf("Bouton Play cliqué !\n");
                        // Jouer le son lors du clic sur le bouton
                        Mix_PlayChannel(-1, sounds[0], 0);//Effet sonore
                        sleep(1);//Temps de chargement (facultatif simplement pour donner un aspect supplementaire)
                        currentState = GAME_MAP;  // Changer l'état du jeu
                    }
                }
            }
            

            
        }

        // Initialisation du chevalier
        init_knight(renderer);
        
        
        SDL_RenderClear(renderer);  // Efface l'écran avec la couleur définie
        SDL_RenderCopy(renderer,backgroundTexture,NULL,NULL);//Affichage ecran d'accueil 

        //Flag etat "précédant" l'état actuel du jeu 
        static int previousState = GAME_MENU;
        
        ///////////////////////Rendu en fonction de l'état du jeu
        if (currentState == GAME_MENU) {
            // Affichage du bouton
            SDL_RenderCopy(renderer, buttonTexture, NULL, &playButton);
            //SDL_RenderCopy(renderer, buttonTexture2, NULL, &exitButton);
            if(!soundmenu){
                Mix_PlayMusic(morceaux[0], -1);
                soundmenu=true;
            }
        } 
        if (currentState == GAME_MAP) {
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            draw_map(renderer, map_base); //Appel à l'affichage de la map de base
            update_and_draw_knight(renderer, keyState, map_base);//Affichage du chevalier 
            if (previousState==GAME_MENU){
                Mix_HaltMusic();//Arret musique
                previousState=GAME_MAP;
            }
            if(!soundmap0){
                //Mix_PlayMusic(morceaux[2], -1);
                //Mix_VolumeMusic(MIX_MAX_VOLUME/3); // Volume de la musique (0 à MIX_MAX_VOLUME)
                
                Mix_PlayChannel(0,sounds[3],-1);
                Mix_Volume(0, MIX_MAX_VOLUME * 1);
                
                soundmap0=true;
            }
            if (affiche_map_base==1 && unaffiche_map_base==0){
                SDL_RenderCopy(renderer, information_texture, NULL, &information);
                renderText(renderer, font, "Salutation citoyen ! Si tu es ici aujourd'hui, c'est que tu souhaites poursuivre l'aventure GameShell ! Ce jeu te permettra", 50, 630, WhiteTextColor);
                renderText(renderer, font, "d'apprendre les commandes bash essentielles et tout ca de maniere ludique ! Oriente toi maintenant a l'est de la carte [ENTRER]", 50, 665, WhiteTextColor);
            }

            
        }
        if (currentState == GAME_MAP_1) {
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (previousState==GAME_MAP){
                Mix_HaltChannel(0);
                previousState=GAME_MAP_1;
            }
            if(!soundmap1){
                //Mix_PlayChannel(0,sounds[7],-1);
                //Mix_Volume(0, MIX_MAX_VOLUME /4);

                Mix_PlayChannel(0,sounds[8],-1);
                Mix_Volume(0, MIX_MAX_VOLUME /4);

                soundmap1=true;
            }
            draw_map_1(renderer, map_1);
            update_and_draw_knight(renderer, keyState, map_1);
            if (mission1==1 && passage_chateau==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &terminal);
                renderText(renderer, font, "Mission 1 : Aller a l'interieur du Chateau ! (Conseil : utilise la commande (cd Lieu) pour te deplacer)", 50, 620, WhiteTextColor);
                renderText(renderer, font_term, inputText, 50, 655, WhiteTextColor);
            }
            if (affiche_map_1==1 && unaffiche_map_1==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &information);
                renderText(renderer, font, "Te voici confronte a ta premiere mission. Ces petits panneaux te serviront au fil de ton epopee. C'est en les consultants", 50, 630, WhiteTextColor);
                renderText(renderer, font, "que tu pourras avancer dans ton aventure. Te voila fin pret, Gameshell t'attends ! [ENTRER]", 50, 665, WhiteTextColor);
            }
            
            
            
        }
        if (currentState == GAME_MAP_2) {
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (previousState==GAME_MAP_1){
                Mix_HaltChannel(0);
                previousState=GAME_MAP_2;
            }
            if(!soundmap2){
                //Mix_PlayChannel(0,sounds[7],-1);
                //Mix_Volume(0, MIX_MAX_VOLUME /4);

                Mix_PlayChannel(0,sounds[9],-1);
                Mix_Volume(0, MIX_MAX_VOLUME /2);

                soundmap2=true;
            }
            draw_map_2(renderer, map_2);
            update_and_draw_knight(renderer, keyState, map_2);
            if (affiche_map_2==1 && unaffiche_map_2==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &terminal);
                renderText(renderer, font, "Oh... Encore une personne qui a du tenter l'aventure Gameshell... Ces ignorants ne rangent jamais derriere eux. [ENTRER]", 50, 630, WhiteTextColor);

            } 
            if (mission2==1 && livre==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &terminal);
                renderText(renderer, font, "Mission 2 : Range ces deux livres dans les bibliotheques ! (Conseil : utilise la commande (mv Objet1 Objet2 Lieu) pour deplacer des objets.", 50, 620, WhiteTextColor);
                renderText(renderer, font_term, inputText, 50, 655, WhiteTextColor);
            }
            
            
            if (affiche_map_3==1 && unaffiche_map_3==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &terminal);
                renderText(renderer, font, "Ces caisses sont la depuis plusieurs annees... Personne n'avait encore eu le courage de venir jusqu'au chateau ! Ce qui", 50, 630, WhiteTextColor);
                renderText(renderer, font, "t'attends a l'issu de ce passage pourrait.. Oh.. Vite, retire ces caisses afin de passer ! [ENTRER]", 50, 665, WhiteTextColor); 
            }
            if (mission3==1 && passage_secret==0){
                SDL_RenderCopy(renderer, terminal_texture, NULL, &terminal);
                renderText(renderer, font, "Mission 3 : Retire les caisses de ton chemin ! (Conseil : utilise la commande (rm Objet) pour supprimer des objets.", 50, 620, WhiteTextColor);
                renderText(renderer, font_term, inputText, 50, 655, WhiteTextColor);
            }
        }
        if(currentState==GAME_MAP_3){
            draw_map_3(renderer);
            renderText(renderer, font, "....Je crois que notre aventure s'arrete la... On se reverra.", 70, 630, WhiteTextColor);
        }
        
        

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // Limiter à ~60 FPS
    }

    
    /////////////////////Destruction des textures
    SDL_DestroyTexture(buttonTexture);
    //SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(terminal_texture);
    SDL_DestroyRenderer(renderer);

    // Libère la mémoire utilisée par les chunks
    for (int i = 0; i < NUM_SOUNDS; i++) {
        Mix_FreeChunk(sounds[i]);  // Libère chaque chunk
    }

    // Libère la mémoire utilisée par les bandes sonores
    for (int i = 0; i < NUM_MORCEAUX; i++) {
        Mix_FreeMusic(morceaux[i]);  // Libère chaque bande sonnore
    }

    /////////////////////Fermeture de sdl ttf, destruction fenetre .....
    SDL_StopTextInput(); // Désactiver la saisie de texte
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    

    
    return EXIT_SUCCESS;

}

// Implémentation de SDL_ExitwithError
void SDL_ExitwithError(const char *message)
{
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
