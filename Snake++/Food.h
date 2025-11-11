#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

using namespace sf;
using namespace std;

class Food
{

private:

    RectangleShape m_shape;
    float m_blockSize;
    Vector2u m_windowSize;

public:

    Food(float blockSize, Vector2u windowSize);

    void Spawn(const deque<sf::RectangleShape>& snakeBody);
    void Draw(RenderWindow& window);
    Vector2f GetPosition() const;
};

