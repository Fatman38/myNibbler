//
// snake_other.cpp for  in /home/vieira_q/cpp/cpp_nibbler/vieira_q/Plugins/SFML
// 
// Made by quentin vieira
// Login   <vieira_q@epitech.net>
// 
// Started on  Fri Apr  3 15:48:32 2015 quentin vieira
// Last update Sun Apr  5 13:11:25 2015 quentin vieira
//

#include <iostream>
#include <string>
#include "LibSFML.hpp"

//
// Private methods
//
void LibSFML::game_over()
{
  this->draw_back();

  sf::Sprite sprite_fond(*(this->_fond2));
  sprite_fond.setPosition(sf::Vector2f(0, 0));
  sprite_fond.setScale(sf::Vector2f(SIZE_X, SIZE_Y));
  sprite_fond.setColor(sf::Color(255, 255, 255, 60));
  this->_window->draw(sprite_fond);

  sf::Text text;
  sf::Font font;
  font.loadFromFile("./Plugins/SFML/font/MGS2MENU.TTF");
  text.setFont(font);
  text.setColor(sf::Color::Black);
  text.setCharacterSize(60);
  text.setStyle(sf::Text::Bold);
  text.setString("Game Over");
  text.setPosition(sf::Vector2f(220, 400));
  this->_window->draw(text);
  this->_window->display();

  delete this->_music;
  this->_music = new sf::Music;
  if (!this->_music->openFromFile("./Plugins/SFML/music/game_over.wav"))
    throw Error("music", "game_over() SFML");
  this->_music->setVolume(25);
  this->_music->play();
  this->_music->setLoop(false);
  while (this->_music->getStatus() != 0);
}
