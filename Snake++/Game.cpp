#include "Game.h"

void Game::Run()
{

    RenderWindow window(VideoMode(400, 400), L"Snake++", Style::Default);

    window.setFramerateLimit(60);

    float moveDelay = 0.15f;
    Clock moveClock;

    Snake snake(blockSize);
    Food food(blockSize, window.getSize());
    food.Spawn(snake.GetBodySnake());

    //Рабочий цикл
    while (window.isOpen())
    {
        Event event;

        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

#pragma region Управление

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            snake.SetDirection({ 0, -1 });
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            snake.SetDirection({ 0, 1 });
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            snake.SetDirection({ -1, 0 });
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            snake.SetDirection({ 1, 0 });
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))  
        {
            Restart(&snake, &food, &window);
        }
#pragma endregion

        if (moveClock.getElapsedTime().asSeconds() >= moveDelay && !IsGameStop)
        {
            snake.Move();
            moveClock.restart();

            if (snake.IsOutOfBounds(window.getSize()) || snake.CheckSelfCollision())
            {
                ResultGame(&window, false);
            }
            else if (snake.GetBodySnake().size() >= 400)
            {
                ResultGame(&window, true);
            }
        }

        Vector2f headPos = snake.GetHeadPosition();
        Vector2f foodPos = food.GetPosition();

        if (headPos.x == foodPos.x && headPos.y == foodPos.y)
        {
            snake.Grow();
            food.Spawn(snake.GetBodySnake());
        }

        if (!IsGameStop)
        {
            window.clear(Color::Black);
            snake.Draw(window);
            food.Draw(window);
            window.display();
        }
    }
}

void Game::Restart(Snake* snake, Food* food, RenderWindow* window)
{
    snake->SetDirection({ 0, 0 });
    window->clear(Color::Black);

    *snake = Snake(blockSize);
    *food = Food(blockSize, window->getSize());

    food->Spawn(snake->GetBodySnake());

    window->display();

    Reset();
}

void Game::Reset()
{
    IsGameStop = false;
}
//result = TRUE - Win, result = FALSE - Defeat
void Game::ResultGame(RenderWindow* window, bool result)
{
    Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    Text text("TEXT", font, 32);

    if (result)
    {
        text = Text("You win!\nPress Esc to Restart", font, 32);
    }
    else
    {
        text = Text("Game Over!\nPress Esc to Restart", font, 32);
    }

    IsGameStop = true;

    window->clear(Color::Black);
    window->draw(text);
    window->display();
}


