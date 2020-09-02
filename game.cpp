
#include <SDL.h>

#include "app.h"
#include "config.h"
#include "game.h"
#include "snake.h"
#include "state.h"

bool menu(MyApp& app, GameStates& state) {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return true;

		if (event.type == SDL_KEYDOWN) {
			SDL_Keycode key = event.key.keysym.sym;
			if (key == SDLK_ESCAPE) {
				return true;
			}
			if (key == SDLK_SPACE) {
				change_state(state, GameStates::GAME);
			}
		}
	}
	return false;
}

void score() {

}


bool score_screen(MyApp& app, GameStates& current_state) {
	return false;
}

bool snake_game(MyApp& app, GameStates& current_state) {
	Snake snake;
	Food food = generate_food();
	SDL_Event event;
	bool done = false;

	while (!done) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				done = true;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					done = true;
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

		app.clear_screen();
		app.render(snake, food);

		SDL_Delay(100);
	}

	return true;
}


void game() {

	MyApp app;
	app.setup();

	GameStates current_state = GameStates::GAME;

	bool done = false;

	while (!done) {
		switch (current_state) {

		case GameStates::MENU: {
			done = menu(app, current_state);
			break;
		}
		case GameStates::GAME: {
			done = snake_game(app, current_state);
			break;
		}
		case GameStates::SCORE: {
			// to do
			done = score_screen(app, current_state);
			break;
		}
		default:
			break;
		}
	}

	app.shutdown();
}

