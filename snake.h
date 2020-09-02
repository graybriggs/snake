#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <deque>

constexpr int SQUARE_W = 32;
constexpr int SQUARE_H = 32;


enum class SnakeDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STATIONARY
};

SnakeDirection rand_direction();

enum class SnakeState {
	ALIVE,
	DEAD
};


struct Food {
	SDL_Rect box;
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

	Snake() {
		SnakeNode head(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, true);
		head.setDirection(rand_direction());
		head.setState(SnakeState::ALIVE);
		snake.push_back(head);
	}



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

	std::size_t getSnakeLength() const {
		return snake.size();
	}


private:
	std::deque<SnakeNode> snake;
};

void move_snake(Snake&);
SDL_Rect calculate_position(const SnakeNode, const SnakeDirection);
bool check_opposite_turn(const SnakeNode&, const SnakeDirection);
void handle_event(Snake& head, SDL_Event* event);
bool snake_eats_food(const SnakeNode& head, const Food& food);
Food generate_food();
bool food_on_snake_check(const Snake& snake, const Food& food);


#endif // !SNAKE_H
