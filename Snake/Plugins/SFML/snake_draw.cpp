//
// snake_draw.cpp for  in /home/vieira_q/cpp/cpp_nibbler/vieira_q/Plugins/SFML
// 
// Made by quentin vieira
// Login   <vieira_q@epitech.net>
// 
// Started on  Fri Apr  3 15:47:19 2015 quentin vieira
// Last update Sun Apr  5 21:43:00 2015 quentin vieira
//

#include <iostream>
#include <string>
#include "LibSFML.hpp"

//
// Private methods
//
void LibSFML::draw_menu(GameData const &data) const
{
  sf::RectangleShape rectangle(sf::Vector2f(SIZE_X, SIZE_Y));
  rectangle.setFillColor(sf::Color(0, 153, 0));
  rectangle.setPosition(sf::Vector2f(0, 0));
  rectangle.setTexture(this->_fond);
  this->_window->draw(rectangle);

  sf::Text text;
  sf::Font font;
  font.loadFromFile("./Plugins/SFML/font/sabomaster.ttf");
  text.setFont(font);
  text.setColor(sf::Color::Black);
  text.setCharacterSize(40);
  text.setStyle(sf::Text::Bold);
  text.setString("Score");
  text.setPosition(sf::Vector2f(40, 20));
  this->_window->draw(text);
  std::ostringstream ss;
  ss << data._score;
  text.setString(ss.str());
  text.setPosition(sf::Vector2f(140, 20));
  this->_window->draw(text);
  text.setString("Speed");
  text.setPosition(sf::Vector2f(200, 20));
  this->_window->draw(text);
  ss.str(std::string());
  ss << data._speed;
  text.setString(ss.str());
  text.setPosition(sf::Vector2f(310, 20));
  this->_window->draw(text);
  text.setString("Best Score");
  text.setPosition(sf::Vector2f(SIZE_X - 260, 20));
  this->_window->draw(text);
  ss.str(std::string());
  ss << data._bestScore;
  text.setString(ss.str());
  text.setPosition(sf::Vector2f(SIZE_X - 260 + 180, 20));
  this->_window->draw(text);

  text.setString("By :");
  text.setCharacterSize(20);
  text.setPosition(sf::Vector2f(SIZE_X - 260, 60));
  this->_window->draw(text);


  text.setString(*(data._bestScoreName));
  text.setPosition(sf::Vector2f(SIZE_X - 210, 60));
  this->_window->draw(text);


  text.setCharacterSize(40);
  font.loadFromFile("./Plugins/SFML/font/MGS2MENU.TTF");
  text.setFont(font);
  text.setString("NIBBLER");
  text.setPosition(sf::Vector2f((SIZE_X / 2) - 180, 20));
  this->_window->draw(text);

  return ;
}

void LibSFML::draw_back()
{
  sf::RectangleShape rectangle;
  float max;
  this->boardX  = BOARD_X;
  this->boardY  = BOARD_Y;
  if (this->SizeX > this->SizeY)
    {
      max = this->SizeX / this->SizeY;
      this->boardY /= max;
    }
  else if (this->SizeY > this->SizeX)
    {
      max = this->SizeY / this->SizeX;
      this->boardX /= max;
    }
  rectangle = sf::RectangleShape(sf::Vector2f(this->boardX, this->boardY));
  rectangle.setFillColor(sf::Color(200, 200, 200));
  rectangle.setPosition(sf::Vector2f(MARGIN_X, MARGIN_Y));
  rectangle.setTexture(this->_fond);
  rectangle.setOutlineThickness(5);
  rectangle.setOutlineColor(sf::Color(0, 0, 0));
  this->_window->draw(rectangle);
  return ;
}

void  LibSFML::draw_pause() const
{
  sf::Text text;
  sf::Font font;

  sf::Sprite sprite_fond(*(this->_fond2));
  sprite_fond.setPosition(sf::Vector2f(0, 0));
  sprite_fond.setScale(sf::Vector2f(SIZE_X, SIZE_Y));
  sprite_fond.setColor(sf::Color(255, 255, 255, 60));
  this->_window->draw(sprite_fond);

  font.loadFromFile("./Plugins/SFML/font/MGS2MENU.TTF");
  text.setFont(font);
  text.setColor(sf::Color::Black);
  text.setCharacterSize(100);
  text.setStyle(sf::Text::Bold);
  text.setString("Pause");
  text.setPosition(sf::Vector2f(250, 350));
  this->_window->draw(text);
  return ;
}

void LibSFML::draw_square(int pos_x, int pos_y, int color) const
{
  sf::RectangleShape rectangle(sf::Vector2f((this->boardX / this->SizeX) - 1.0,
					    (this->boardY / this->SizeY) - 1.0));
  if (color == 0)
    rectangle.setFillColor(sf::Color(0, 0, 0));
  else
    rectangle.setFillColor(sf::Color(200, 0, 0));
  rectangle.setPosition(sf::Vector2f(MARGIN_X + ((this->boardX / this->SizeX) * static_cast<float>(pos_x)),
				     MARGIN_Y + ((this->boardY / this->SizeY) * static_cast<float>(pos_y))));
  this->_window->draw(rectangle);
  return ;
}

void LibSFML::draw_food(int pos_x, int pos_y) const
{
  int max = this->SizeX;
  if (max < this->SizeY)
    max = this->SizeY;
  sf::Sprite sprite_food(*(this->_food));
  sprite_food.setPosition(sf::Vector2f(MARGIN_X + ((this->boardX / this->SizeX) * pos_x),
				       MARGIN_Y + ((this->boardY / this->SizeY) * pos_y)));
  sprite_food.setScale(sf::Vector2f(1.5 / (max / 20), 1.5 / (max / 20)));
  this->_window->draw(sprite_food);
  return ;
}
