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
	head.setDirection(rand_direction());
	head.setState(SnakeState::ALIVE);
	snake.push_back(head);
	
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

				handle_event(snake, &event);
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

		move_snake(snake);

		/////////////
		// Render
		/////////////

		clear_screen(renderer);
		render_food(renderer, food);
		render_snake(renderer, snake);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		/*
		if ((SDL_GetTicks() - timer) < (1000 / 60)) {
			SDL_Delay((1000 / 60) - (SDL_GetTicks() - timer));
		}
		*/
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void clear_screen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void render_food(SDL_Renderer* renderer, const Food food) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &(food.box));
}

void render_snake(SDL_Renderer* renderer, const std::deque<SnakeNode>& snake) {
	for (auto& snakeNode : snake) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &(snakeNode.getBox()));
	}
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}