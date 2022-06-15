#ifndef _BOX_HPP
#define _BOX_HPP

#include "display.hpp"

class Box
{
public:
    Box(int length = 1, int width = 1, int x_origin = 0, int y_origin = 0, sf::Color color = sf::Color::Black):
        b_length(length), b_width(width), b_color(color) {}

    void draw(sf::Image&);

private:
    int       b_length,  b_width,
              bX_origin, bY_origin;
    sf::Color b_color;
};

#endif