#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

enum class GameStates;
class MyApp;

bool menu(MyApp& app, GameStates& current_states);
bool snake_game(MyApp& app, GameStates& current_state);
bool score_screen(MyApp& app, GameStates& current_state);

void game();


#endif