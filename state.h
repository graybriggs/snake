#pragma once
#ifndef STATE_H
#define STATE_H


enum class GameStates {
	MENU,
	GAME,
	SCORE
};

void change_state(GameStates& current, const GameStates to);


#endif