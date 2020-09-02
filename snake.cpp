
#include "config.h"
#include "snake.h"

void move_snake(Snake& snake) {

	SnakeNode& head = snake.getRawSnake()[0];
	SnakeDirection direction = head.getDirection();

	if (snake.getSnakeLength() < 2) {
		head.setBox(calculate_position(head, direction));
	}
	else {
		SnakeNode& back = snake.getRawSnake().back();
		snake.getRawSnake().pop_back();
		back.setBox(calculate_position(head, direction));
		back.setDirection(direction);
		snake.getRawSnake().push_front(back);
	}
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

bool check_opposite_turn(const SnakeNode& snake_head, const SnakeDirection next_direction)
{
	bool oppMove = false;

	auto pos = snake_head.getDirection();

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


 void handle_event(Snake& snake, SDL_Event* event) {
	 SnakeDirection direction = snake.getHead().getDirection();

	 SnakeNode& head = snake.getRawSnake()[0];

	 SDL_Keycode key = event->key.keysym.sym;

	 if (key == SDLK_UP) {
		 //if (!check_opposite_turn(snake[0], SnakeDirection::UP))
		 head.setDirection(SnakeDirection::UP);
	 }
	 else if (key == SDLK_DOWN) {
		 //if (!check_opposite_turn(snake[0], SnakeDirection::DOWN))
		 head.setDirection(SnakeDirection::DOWN);
	 }
	 else if (key == SDLK_LEFT) {
		 //if (!check_opposite_turn(snake[0], SnakeDirection::LEFT))
		 head.setDirection(SnakeDirection::LEFT);
	 }
	 else if (key == SDLK_RIGHT) {
		 //if (!check_opposite_turn(snake[0], SnakeDirection::RIGHT))
		 head.setDirection(SnakeDirection::RIGHT);
	 }

	 for (auto& sn : snake.getSnake()) {
		 sn.setDirection(head.getDirection());
	 }
	
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

bool food_on_snake_check(const Snake& snake, const Food& food) {

	for (auto& sn : snake.getSnake()) {
		if (sn.getBox().x == food.box.x && sn.getBox().y == food.box.y)
			return true;
	}
	return false;
}

