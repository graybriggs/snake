#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <deque>

constexpr int SQUARE_W = 32;
constexpr int SQUARE_H = 32;

struct Food {
	SDL_Rect box;
};


enum class SnakeDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STATIONARY
};

enum class SnakeState {
	ALIVE,
	DEAD
};

class SnakeNode {
public:

	SnakeNode(int posx, int posy, bool head = false) {
		box.x = posx;
		box.y = posy;
		box.w = SQUARE_W;
		box.h = SQUARE_H;
	}

	SnakeNode getPenultimateNode(std::deque<SnakeNode>& s) const {
		return s[s.size() - 1];
	}

	SnakeNode getLastNode(std::deque<SnakeNode>& s) const {
		return s.back();
	}

	SDL_Rect getBox() const {
		return box;
	}

	void setBox(const SDL_Rect b) {
		box = b;
	}
	
	SnakeDirection getDirection() const {
		return direction;
	}

	void setDirection(SnakeDirection dir) {
		direction = dir;
	}

	void setState(const SnakeState s) {
		state = s;
	}

private:
	bool is_head;
	SDL_Rect box;
	int pos;
	SnakeDirection direction;
	SnakeState state;
};



void move_snake(std::deque<SnakeNode>&, SnakeDirection);
SDL_Rect calculate_position(const SnakeNode, const SnakeDirection);
bool check_opposite_turn(const SnakeNode&, const SnakeDirection);
SnakeDirection handle_event(SDL_Event event);
SnakeDirection rand_direction();
bool snake_eats_food(const SnakeNode& head, const Food& food);
Food generate_food();


#endif // !SNAKE_H
