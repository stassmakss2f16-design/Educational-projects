#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food(float blockSize, Vector2u windowSize)
    : m_blockSize(blockSize), m_windowSize(windowSize)
{
    m_shape.setSize(Vector2f(blockSize - 1, blockSize - 1));
    m_shape.setFillColor(Color::Red);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Food::Spawn(const deque<sf::RectangleShape>& snakeBody)
{
    unsigned maxX = m_windowSize.x / static_cast<unsigned>(m_blockSize);
    unsigned maxY = m_windowSize.y / static_cast<unsigned>(m_blockSize);

    bool valid = false;

    Vector2f position;

    while (!valid)
    {
        position.x = static_cast<float>((std::rand() % maxX) * m_blockSize);
        position.y = static_cast<float>((std::rand() % maxY) * m_blockSize);
        valid = true;

        for (const auto& segment : snakeBody)
        {
            if (segment.getPosition() == position)
            {
                valid = false;
                break;
            }
        }
    }

    m_shape.setPosition(position);
}

void Food::Draw(RenderWindow& window)
{
    window.draw(m_shape);
}

Vector2f Food::GetPosition() const
{
    return m_shape.getPosition();
}
