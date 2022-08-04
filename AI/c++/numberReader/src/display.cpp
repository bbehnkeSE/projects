#include "headers/display.hpp"

// Creates texture to store window display, then makes smaller texture to crop the larger texture,
// then stores image in vector
void takeScreenshot(const sf::RenderWindow& window, std::vector<sf::Image>& images)
{
    sf::Texture texture;
    texture.create(W_WIDTH, W_HEIGHT);
    texture.update(window);

    sf::Texture cropped;
    cropped.create(W_WIDTH, W_HEIGHT - DIVIDER_OFFSET);
    cropped.update(texture);

    sf::Image result = cropped.copyToImage();

    images.push_back(result);
}


void clearPoints(std::vector<sf::Shape*>& points)
{
    for(auto point: points)
        delete point;
                        
    points.clear();
}