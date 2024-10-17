#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include "game.h"

int main(int argc, char *argv[]) {
    Game game;
    game.run();
    return 0;
}