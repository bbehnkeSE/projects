#include "headers/display.hpp"

// Creates texture to store window display
sf::Texture takeScreenshot(const sf::RenderWindow& window)
{
    sf::Texture texture;
    texture.create(W_WIDTH, W_HEIGHT);
    texture.update(window);

    return texture;
}


// Crops texture based on divider offset
sf::Texture cropTexture(const sf::Texture& texture)
{
    sf::Texture cropped;
    cropped.create(W_WIDTH, W_HEIGHT - DIVIDER_OFFSET);
    cropped.update(texture);

    return cropped;
}


// Converts texture to image
sf::Image textToImg(const sf::Texture& texture)
{
    sf::Image img = texture.copyToImage();
    return img;
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


// Creates string from vector of chars
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