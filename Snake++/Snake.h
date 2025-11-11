#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

using namespace sf;
using namespace std;

class Snake
{
private:

	deque<RectangleShape> m_body; // сегменты тела
	Vector2i m_direction;         // направление движения
	float m_blockSize;            // размер сегмента

public:

	Snake(float blockSize);

	void Move();
	void Grow();
	void Draw(RenderWindow& window);
	void SetDirection(Vector2i dir);

	bool IsBackwards(Vector2i dir);

	bool IsOutOfBounds(sf::Vector2u windowSize) const;
	bool CheckSelfCollision() const;

	Vector2i GetDirection() const;
	Vector2f GetHeadPosition() const;
	deque<RectangleShape> GetBodySnake();
};

