//
// Graph.cpp for  in /home/vieira_q/cpp/cpp_nibbler/vieira_q/src
// 
// Made by quentin vieira
// Login   <vieira_q@epitech.net>
// 
// Started on  Tue Mar 24 20:08:32 2015 quentin vieira
// Last update Sun Apr  5 18:20:15 2015 Thibaud Auzou
//

#include <iostream>
#include <string>
#include "LibSFML.hpp"

//
// Constructors
//
LibSFML::LibSFML()
{
  this->_window = NULL;
  this->_music  = NULL;
  this->_musicPauseOP = NULL;
  this->_musicPauseCL = NULL;
  this->SizeX   = 0;
  this->SizeY   = 0;
  this->_food   = NULL;
  this->_fond   = NULL;
  this->_fond2  = NULL;
  this->esc     = 0;
  this->boardX  = BOARD_X;
  this->boardY  = BOARD_Y;
  this->_pause  = false;

  this->_event[sf::Keyboard::Left] = E_KEY_LEFT;
  this->_event[sf::Keyboard::Up] = E_KEY_UP;
  this->_event[sf::Keyboard::Down] = E_KEY_DOWN;
  this->_event[sf::Keyboard::Right] = E_KEY_RIGHT;
  this->_event[sf::Keyboard::Z] = E_KEY_Z;
  this->_event[sf::Keyboard::Q] = E_KEY_Q;
  this->_event[sf::Keyboard::S] = E_KEY_S;
  this->_event[sf::Keyboard::D] = E_KEY_D;
  this->_event[sf::Keyboard::A] = E_KEY_PREV;
  this->_event[sf::Keyboard::E] = E_KEY_NEXT;
  this->_event[sf::Keyboard::Space] = E_KEY_SPACE;
  this->_event[sf::Keyboard::Escape] = E_KEY_ESC;
}

LibSFML::LibSFML(const LibSFML &other)
{
  this->_window = other._window;
  this->_music  = other._music;
}

LibSFML & LibSFML::operator=(const LibSFML &other)
{
  if (&other != this)
    {
      this->_window = other._window;
      this->_music  = other._music;
    }
  return (*this);
}

LibSFML::~LibSFML()
{
}

extern "C" IDisplayPlugin	*loading()
{
  return (new LibSFML);
}
