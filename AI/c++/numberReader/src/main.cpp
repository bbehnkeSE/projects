#include "headers/display.hpp"

int main()
{
    srand(time(nullptr));

    // Create window
    // sf::Style::Close prevents resize
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Number Reader", sf::Style::Close);
    window.setFramerateLimit(MAX_FPS);

    // Create divider
    sf::Vector2f dividerSize(W_WIDTH, 2);
    sf::RectangleShape divider(dividerSize);
    divider.setFillColor(sf::Color::Black);
    divider.setPosition(0, W_HEIGHT - DIVIDER_OFFSET);

    // Create brush
    sf::CircleShape brush(TMP_BRUSH_SIZE);
    brush.setFillColor(sf::Color::Black);

    // Create font
    sf::Font font;
    if(!font.loadFromFile("resources/fonts/arial.ttf"))
        return EXIT_FAILURE;

    // Setup text to display on the window
    sf::Text displayValues;
    displayValues.setFont(font);
    displayValues.setCharacterSize(26);
    displayValues.setFillColor(sf::Color::Black);
    displayValues.setPosition(TEXT_OFFSET, (W_HEIGHT - DIVIDER_OFFSET - TEXT_OFFSET));

    // Buffer for circles to be drawn on the screen
    std::vector<sf::Shape*> points;

    // Buffer to store training data before saving to file
    std::vector<sf::Image> trainingImgs;
    std::vector<char>      trainingValues;

    // Path info to store training/test data
    std::vector<std::string> trainingImgNames;
    const std::string        trainingImgPath = "resources/training_images/";
    const std::string        trainingValPath = "resources/training_values.txt";
    const std::string        testImgPath     = "resources/test_images/";
    const std::string        testValPath     = "resources/test_values.txt";

    // Ranges for random numbers
    int max = 999999;
    int min = 100000;

    // Main loop
    bool running = true;
    while(running)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                running = false;

            if(event.type == sf::Event::KeyPressed)
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        running = false;
                        break;

                    // Frees memory and clears points
                    case sf::Keyboard::BackSpace:
                        clearPoints(points);
                        break;

                    // Key codes to save training data
                    // TODO: Consolidate into functions
                    case sf::Keyboard::Num1:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('1');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num2:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('2');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num3:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('3');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num4:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('4');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num5:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('5');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num6:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('6');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num7:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('7');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num8:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('8');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num9:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('9');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    case sf::Keyboard::Num0:
                        trainingImgs.push_back(textToImg(cropTexture(takeScreenshot(window))));
                        trainingValues.push_back('0');
                        trainingImgNames.push_back(nameImg(trainingValues.back(), getRandNumberInRange(rand(), max, min)));
                        displayValues.setString(createString(trainingValues));
                        clearPoints(points);
                        break;

                    // Undo
                    case sf::Keyboard::U:
                        if(!trainingImgs.empty() && !trainingValues.empty())
                        {
                            trainingImgs.pop_back();
                            trainingImgNames.pop_back();
                            trainingValues.pop_back();
                            displayValues.setString(createString(trainingValues));
                        }
                        else
                            std::cout << "Either trainingImgs or trainingValues is already empty!";
                        
                        break;
                    
                    case sf::Keyboard::Enter:
                        for(int i = 0; i < trainingImgs.size(); ++i)
                        {
                            trainingValues.clear();
                            trainingImgs[i].saveToFile(trainingImgPath + trainingImgNames[i]);
                        }
                        break;
                }
        }
        
        window.clear(sf::Color::White);
        window.draw(divider);

        // Update brush position if mouse is in drawing area
        if(sf::Mouse::getPosition(window).y < divider.getPosition().y)
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

            //window.draw(brush);
        }

        for(auto point: points)
            window.draw(*point);

        window.draw(displayValues);
        
        window.display();
    }
    window.close();

    // Free memory
    for(auto point: points)
        delete point;

    return EXIT_SUCCESS;
}