#ifndef _DISPLAY_HPP
#define _DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>

#define W_WIDTH        200
#define W_HEIGHT       230
#define MAX_FPS        120
#define DIVIDER_OFFSET  30
#define TEXT_OFFSET      3

// TODO: Make this a variable
#define TMP_BRUSH_SIZE   5

// Utility functions
sf::Texture takeScreenshot(const sf::RenderWindow&);
sf::Texture cropTexture   (const sf::Texture&);
sf::Image   textToImg     (const sf::Texture&);
void clearPoints          (std::vector<sf::Shape*>&);

std::string nameImg       (char, int);
std::string createString  (const std::vector<char>&);

int getRandNumberInRange  (int, int, int);

#endif      // _DISPLAY_HPP