
#include <cstdlib>
#include <ctime>
#include <SDL.h>

#include "config.h"
#include "game.h"
#include "snake.h"
#include "state.h"

void setup() {

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

void shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void render_food(SDL_Renderer* renderer, const Food food) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &(food.box));
}

void render(SDL_Renderer* renderer, const Snake& snake, const Food& food) {
	clear_screen(renderer);
	render_food(renderer, food);
	render_snake(renderer, snake);

	SDL_RenderPresent(renderer);
}

void clear_screen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}


void menu() {

	// render snake menu
	// press space to start

}

void score() {

}

bool front_menu(const GameStates& current_state) {}
bool score_screen(const GameStates& current_state) {}

bool snake_game(const GameStates& current_state) {
	Snake snake;
	Food food = calculate_position();
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return true;

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return true;
			}

			handle_event(snake, &event);
		}
	}


	if (snake_eats_food(snake.getHead(), food)) {
		SnakeNode next(snake.getSnake()[0]);
		// might reveal an error
		next.setDirection(next.getDirection());
		next.setState(SnakeState::ALIVE);
		snake.add(next);

		food = generate_food();
		bool result = food_on_snake_check(snake, food);
		while (result) {
			food = generate_food();
			result = food_on_snake_check(snake, food);
		}

	}

	move_snake(snake);

	return false;
}


void game() {

	setup();

	GameStates current_state = GameStates::MENU;

	SDL_Event event;
	bool done = false;

	while (!done) {

		switch (current_state) {

		case GameStates::MENU: {

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					done = true;

				if (event.type == SDL_KEYDOWN) {
					SDL_Keycode key = event.key.keysym.sym;
					if (key == SDLK_ESCAPE) {
						done = true;
						break;
					}
					if (key == SDLK_SPACE) {
						change_state(GameStates::GAME);
					}
				}
			}

			break;
		}
		case GameStates::GAME: {

			snake_game(current_state);

			break;
		}
		case GameStates::SCORE: {
			// to do
			score_screen(current_state);
		}
			break;

		default:
			break;
		}
	}

	shutdown();
}

