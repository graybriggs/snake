#pragma once
#ifndef MY_APP
#define MY_APP

#include <cstdlib>
#include <ctime>

#include <SDL.h>

#include "config.h"

class Snake;
struct Food;

class MyApp {
public:
	void setup();
	void shutdown();
	void render_snake(const Snake& snake);
	void render_food(const Food food);
	void render(const Snake& snake, const Food& food);
	void clear_screen();
	SDL_Renderer* getRenderer();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif