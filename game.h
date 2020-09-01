#pragma once
#ifndef GAME_H
#define GAME_H

static SDL_Window* window;
static SDL_Renderer* renderer;

void setup();
void shutdown();

bool front_menu(GameStates& current_states);
bool snake_game(GameStates& current_state);
bool score_screen(GameStates& current_state);

void game();

void render(SDL_Renderer* renderer);

#endif