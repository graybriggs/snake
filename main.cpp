
#include <deque>

#include <SDL.h>

#include "game.h"
void clear_screen(SDL_Renderer* renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {

	game();

	return 0;
}


