
#include "app.h"
#include "snake.h"

void MyApp::setup() {

	srand((unsigned int)time(nullptr));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		Config::SCREEN_WIDTH,
		Config::SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
}


void MyApp::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MyApp::render_snake(const Snake& snake) {
	for (auto& snakeNode : snake.getSnake()) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &(snakeNode.getBox()));
	}
}

void MyApp::render_food(const Food food) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &(food.box));
}

void MyApp::render(const Snake& snake, const Food& food) {
	clear_screen();
	render_food(food);
	render_snake(snake);

	SDL_RenderPresent(renderer);
}

void MyApp::clear_screen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

SDL_Renderer* MyApp::getRenderer() {
	return renderer;
}