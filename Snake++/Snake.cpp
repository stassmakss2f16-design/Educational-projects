#include "Snake.h"

Snake::Snake(float blockSize) : m_blockSize(blockSize), m_direction(0, 0)
{
    RectangleShape head(Vector2f(blockSize - 1, blockSize - 1));
    head.setFillColor(Color::Green);
    head.setPosition(100, 100);
    m_body.push_back(head);
}

void Snake::Move()
{
    RectangleShape newHead = m_body.front();
    newHead.move(m_direction.x * m_blockSize, m_direction.y * m_blockSize);

    m_body.push_front(newHead);

    m_body.pop_back();
}

void Snake::Grow()
{
    RectangleShape newSegment = m_body.back();
    m_body.push_back(newSegment);
}

void Snake::Draw(RenderWindow& window)
{
    for (auto& segment : m_body)
        window.draw(segment);
}

void Snake::SetDirection(Vector2i dir)
{
    if (!IsBackwards(dir))
    {
        m_direction = dir;
    }
}

bool Snake::IsBackwards(Vector2i dir)
{
    return (dir.x == -m_direction.x && dir.y == -m_direction.y);
}

Vector2i Snake::GetDirection() const
{
    return m_direction;
}

Vector2f Snake::GetHeadPosition() const
{
    return m_body.front().getPosition();
}

deque<RectangleShape> Snake::GetBodySnake()
{
    return m_body;
}

bool Snake::IsOutOfBounds(Vector2u windowSize) const
{
    Vector2f headPos = GetHeadPosition();

    return (
        headPos.x < 0 ||
        headPos.y < 0 ||
        headPos.x + m_blockSize > windowSize.x ||
        headPos.y + m_blockSize > windowSize.y
        );
}

bool Snake::CheckSelfCollision() const
{
    //Чтобы лишний раз не гонять по циклу.
    if (m_body.size() < 5)
    {
        return false;
    }

    Vector2f headPos = m_body.front().getPosition();

    for (int i = 1; i < m_body.size(); ++i)
    {
        if (m_body[i].getPosition() == headPos)
        {
            return true;
        }
    }

    return false;

}
