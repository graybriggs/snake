#include <cstdlib>
#include <ctime>
#include <deque>

#include <SDL.h>

#include "config.h"
#include "snake.h"

void cleanup(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
	srand((unsigned int)time(nullptr));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	SDL_Window* window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		Config::SCREEN_WIDTH,
		Config::SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);

	SnakeDirection direction = SnakeDirection::RIGHT;  // start direction

	int timer = 0;
	bool isPaused = false;

	std::deque<SnakeNode> snake;

	SnakeNode head(320, 240, true);
	head.setDirection(SnakeDirection::RIGHT);
	head.setState(SnakeState::ALIVE);
	snake.push_back(head);

	//head.direction = rand_direction();
	
	SDL_Event event;
	bool done = false;

	Food food = generate_food();

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				done = true;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					done = true;
					break;
				}
				
				if (event.key.keysym.sym == SDLK_SPACE) {
					SnakeNode next(snake[0].getBox().x, snake[0].getBox().y);
					next.setDirection(snake[0].getDirection());
					next.setState(SnakeState::ALIVE);
					snake.push_back(next);
				}
				if (event.key.keysym.sym == SDLK_UP) {
					if (!check_opposite_turn(snake[0], SnakeDirection::UP))
						head.setDirection(SnakeDirection::UP);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					if (!check_opposite_turn(snake[0], SnakeDirection::DOWN))
						head.setDirection(SnakeDirection::DOWN);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					if (!check_opposite_turn(snake[0], SnakeDirection::LEFT))
						head.setDirection(SnakeDirection::LEFT);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					if (!check_opposite_turn(snake[0], SnakeDirection::RIGHT))
						head.setDirection(SnakeDirection::RIGHT);
				}

			}
		}

		////////////
		// Logic
		////////////

		if (snake_eats_food(snake[0], food)) {

			SnakeNode next(snake[0].getBox().x, snake[0].getBox().y);
			next.setDirection(snake[0].getDirection());
			next.setState(SnakeState::ALIVE);
			snake.push_back(next);

			food = generate_food();
		}

		move_snake(snake, head.getDirection());

		/////////////
		// Render
		/////////////

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &(food.box));

		for (auto& snakeNode : snake) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &(snakeNode.getBox()));
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		if ((SDL_GetTicks() - timer) < (1000 / 60)) {
			SDL_Delay((1000 / 60) - (SDL_GetTicks() - timer));
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}