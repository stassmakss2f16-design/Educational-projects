#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

using namespace sf;

class Game
{
private:
	
	bool IsGameStop = false;

	float blockSize = 20.f;

public:
	

	void Run();
	void Restart(Snake* snake, Food* food, RenderWindow* window);
	void Reset();
	void ResultGame(RenderWindow* window, bool result);

};

