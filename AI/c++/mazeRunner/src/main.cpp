#include "headers/display.hpp"

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Maze Runner");
    window.setFramerateLimit(MAX_FPS);

    // Create and initialize dot
    sf::CircleShape dot(DOT_RADIUS);
    dot.setFillColor(sf::Color::Black);
    dot.setPosition(((W_WIDTH / 2) - DOT_RADIUS), (W_HEIGHT - 50));

    // Create and initialize goal area
    sf::Vector2f size(50, 50);
    sf::RectangleShape goal(size);
    goal.setFillColor(sf::Color::Green);
    goal.setPosition((W_WIDTH / 2) - 25, (W_HEIGHT - 780));

    // Game loop
    bool running = true;
    while(running)
    {
        // Check events during game
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;
                
                // Keyboard presses
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        // Close window
                        case sf::Keyboard::Escape:
                            running = false;
                            break;

                        // Move dot
                        case sf::Keyboard::W:
                            dot.setPosition(dot.getPosition().x, dot.getPosition().y - 5);
                            break;
                        case sf::Keyboard::A:
                            dot.setPosition(dot.getPosition().x - 5, dot.getPosition().y);
                            break;
                        case sf::Keyboard::S:
                            dot.setPosition(dot.getPosition().x, dot.getPosition().y + 5);
                            break;
                        case sf::Keyboard::D:
                            dot.setPosition(dot.getPosition().x + 5, dot.getPosition().y);
                            break;
                        
                        // Don't worry about other events
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        // Check collision
        if(dot.getGlobalBounds().intersects(goal.getGlobalBounds()))
            std::cout << "GOAL!\n";

        // Update window
        window.clear(sf::Color::White);
        window.draw(goal);
        window.draw(dot);
        window.display();
    }
    window.close();

    return 0;
}