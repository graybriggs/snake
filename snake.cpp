
#include "config.h"
#include "snake.h"

void move_snake(std::deque<SnakeNode>& s, SnakeDirection direction) {

	SnakeNode& head = s[0];

	if (s.size() < 2) {
		SDL_Rect new_pos = calculate_position(head, direction);
		head.setBox(new_pos);
	}
	else {
		SnakeNode back = s.back();
		s.pop_back();
		back.setBox(calculate_position(head, direction));
		s.push_front(back);
	}
	head.setDirection(direction);
}

SDL_Rect check_screen_collision(SDL_Rect r)
{
	SDL_Rect newPosRect = r;

	if (newPosRect.x >= Config::SCREEN_WIDTH)
		newPosRect.x = 0;

	if (newPosRect.x < 0)
		newPosRect.x = Config::SCREEN_WIDTH - SQUARE_W;

	if (newPosRect.y >= Config::SCREEN_HEIGHT)
		newPosRect.y = 0;

	if (newPosRect.y < 0)
		newPosRect.y = Config::SCREEN_HEIGHT - SQUARE_H;

	return newPosRect;
}

SDL_Rect calculate_position(const SnakeNode s, const SnakeDirection direction) {

	SDL_Rect newPosRect = s.getBox();

	switch (direction) {
	case SnakeDirection::UP:
		newPosRect.y -= SQUARE_H;
		break;
	case SnakeDirection::DOWN:
		newPosRect.y += SQUARE_H;
		break;
	case SnakeDirection::LEFT:
		newPosRect.x -= SQUARE_W;
		break;
	case SnakeDirection::RIGHT:
		newPosRect.x += SQUARE_W;
		break;
	default:
		;

	}
	newPosRect = check_screen_collision(newPosRect);

	return newPosRect;
}

bool check_opposite_turn(const SnakeNode& snake_cur_pos, const SnakeDirection next_direction)
{
	bool oppMove = false;

	auto pos = snake_cur_pos.getDirection();

	if ((pos == SnakeDirection::UP) && (next_direction == SnakeDirection::DOWN))
		oppMove = true;

	else if ((pos == SnakeDirection::DOWN) && (next_direction == SnakeDirection::UP))
		oppMove = true;

	else if ((pos == SnakeDirection::LEFT) && (next_direction == SnakeDirection::RIGHT))
		oppMove = true;

	else if ((pos == SnakeDirection::RIGHT) && (next_direction == SnakeDirection::LEFT))
		oppMove = true;

	return oppMove;
}


SnakeDirection handle_event(SDL_Event event) {
	SnakeDirection direction;

	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		direction = SnakeDirection::UP;
		break;
	case SDLK_DOWN:
		direction = SnakeDirection::DOWN;
		break;
	case SDLK_LEFT:
		direction = SnakeDirection::LEFT;
		break;
	case SDLK_RIGHT:
		direction = SnakeDirection::RIGHT;
		break;
	default:
		;
	}
	return direction;
}

SnakeDirection rand_direction() {

	int dir = rand() % 4;

	SnakeDirection direction;

	switch (dir)
	{
	case 0:
		direction = SnakeDirection::UP;
		break;
	case 1:
		direction = SnakeDirection::DOWN;
		break;
	case 2:
		direction = SnakeDirection::LEFT;
		break;
	case 3:
		direction = SnakeDirection::RIGHT;
		break;
	default:
		;
	}
	return direction;
}


Food generate_food() {

	int x = rand() % 20;
	int y = rand() % 15;

	x *= 32;
	y *= 32;

	Food f;
	f.box.x = x;
	f.box.y = y;
	f.box.w = 32;
	f.box.h = 32;

	return f;
}

bool snake_eats_food(const SnakeNode& head, const Food& food) {

	return (head.getBox().x == food.box.x) && (head.getBox().y == food.box.y);
}

