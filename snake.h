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

	SnakeNode(SDL_Rect r) {
		box.x = r.x;
		box.y = r.y;
		box.w = r.w;
		box.h = r.h;
	}

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

class Snake {
public:

	SnakeNode getHead() {
		return snake[0];
	}

	std::deque<SnakeNode> getSnake() const {
		return snake;
	}

	std::deque<SnakeNode>& getRawSnake() {
		return snake;
	}

	void add(SnakeNode node) {
		snake.push_back(node);
	}


private:
	std::deque<SnakeNode> snake;
};


void prepare_snake(Snake&);
void move_snake(Snake&);
SDL_Rect calculate_position(const SnakeNode, const SnakeDirection);
bool check_opposite_turn(const SnakeNode&, const SnakeDirection);
void handle_event(Snake& head, SDL_Event* event);
SnakeDirection rand_direction();
bool snake_eats_food(const SnakeNode& head, const Food& food);
Food generate_food();
bool food_on_snake_check(const Snake& snake, const Food& food);


//
void render_food(SDL_Renderer* renderer, const Food food);
void render_snake(SDL_Renderer* renderer, const Snake& snake);

#endif // !SNAKE_H
