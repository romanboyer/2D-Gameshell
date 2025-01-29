#ifndef STATE_H
#define STATE_H

typedef enum {
    GAME_MENU,
    GAME_MAP_1,
    GAME_MAP_2,
    GAME_MAP_3,
    GAME_MAP
} GameState;

extern GameState currentState;

#endif
