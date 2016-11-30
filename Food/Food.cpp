//
// Food.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Wed Mar 25 09:02:32 2015 Thibaud Auzou
// Last update Wed Mar 25 09:23:35 2015 Thibaud Auzou
//

#include "Food.hpp"

//
// CTORS, DTORS, COPLIEN & FRIENDS
//

Food::Food				()
  : _x(0), _y(0)
{
}

Food::Food				(unsigned int x, unsigned int y)
  : _x(x), _y(y)
{
}

Food::Food				(const Food &other)
  : _x(other._x), _y(other._y)
{
}

Food					&Food::operator=(const Food &)
{
  return (*this);
}

Food::~Food				()
{
}

//
// GETTERS
//

unsigned int				Food::getX(void) const
{
  return (this->_x);
}

unsigned int				Food::getY(void) const
{
  return (this->_y);
}
