#include "headers/box.hpp"

void Box::draw(sf::Image& image)
{
    for(int i = bX_origin; i < b_length; ++i)
        for(int j = bY_origin; j < b_width; ++j)
            image.setPixel(i, j, b_color);
}