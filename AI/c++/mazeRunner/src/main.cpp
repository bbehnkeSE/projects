#include "headers/box.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Maze Runner");
    window.setFramerateLimit(MAX_FPS);

    sf::CircleShape dot(7);
    dot.setFillColor(sf::Color::Black);

    bool running = true;
    while(running)
    {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                running = false;


        dot.setPosition(sf::Mouse::getPosition(window).x - 7, sf::Mouse::getPosition(window).y - 7);
        window.clear(sf::Color::White);
        window.draw(dot);
        window.display();
    }
    window.close();

    return 0;
}