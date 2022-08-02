#include "headers/display.hpp"

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Number Reader");
    window.setFramerateLimit(MAX_FPS);

    // Create divider
    sf::Vector2f dividerSize(W_WIDTH, 2);
    sf::RectangleShape divider(dividerSize);
    divider.setFillColor(sf::Color::Black);
    divider.setPosition(0, W_HEIGHT/2);

    // Create brush
    sf::CircleShape brush(TMP_BRUSH_SIZE);
    brush.setFillColor(sf::Color::Black);
    brush.setPosition(((W_WIDTH / 2) - TMP_BRUSH_SIZE), (W_HEIGHT - 50));

    // Vector to store/draw circles to the screen
    std::vector<sf::Shape*> points;

    // Main loop
    bool running = true;
    while(running)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;

                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            running = false;
                            break;

                        // Frees memory and clears points
                        case sf::Keyboard::BackSpace:
                            for(auto point: points)
                                delete point;
                            
                            points.clear();
                            break;
                    }
                    break;
            }
        }
        
        window.clear(sf::Color::White);
        window.draw(divider);

        // Update brush position if mouse is in drawing area
        if(sf::Mouse::getPosition(window).y > W_HEIGHT/2)
        {
            brush.setPosition((float)sf::Mouse::getPosition(window).x - TMP_BRUSH_SIZE, 
                              (float)sf::Mouse::getPosition(window).y - TMP_BRUSH_SIZE);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::CircleShape *point = new sf::CircleShape(TMP_BRUSH_SIZE);
                point->setPosition(brush.getPosition());
                point->setFillColor(brush.getFillColor());
                points.push_back(point);
            }

            window.draw(brush);
        }

        for(auto point: points)
        {
            window.draw(*point);
        }
        window.display();
    }
    window.close();

    // Free memory
    for(auto point: points)
        delete point;

    return 0;
}