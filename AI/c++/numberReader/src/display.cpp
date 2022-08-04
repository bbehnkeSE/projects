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


// Free memory and empty points vec
void clearPoints(std::vector<sf::Shape*>& points)
{
    for(auto point: points)
        delete point;
                        
    points.clear();
}


// Generates unique filename for an image
std::string nameImg(char value, int rando)
{
    std::string result = value + std::to_string(rando) + ".png";
    return result;
}


std::string createString(const std::vector<char>& values)
{
    std::string result = "";
    for(auto value: values)
        result += value;

    return result;
}


int getRandNumberInRange(int rando, int max, int min)
{
    return min + (rando % (max - min + 1));
}