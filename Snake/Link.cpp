#include <iostream>
#include <string>
#include "Link.hpp"

//
// CTORS, DTORS, COPLIEN & FRIENDS
//

Link::Link			()
  : _x(0), _y(0), _head(false), _tail(false)
{
}

Link::Link			(unsigned int x, unsigned int y)
  : _x(x), _y(y), _head(false), _tail(false)
{
}

Link::Link			(const Link &other)
  : _x(other._x), _y(other._y), _head(other._head), _tail(other._tail)
{
}

Link				&Link::operator=(const Link &other)
{
  if (&other != this)
    {
      this->_x = other._x;
      this->_y = other._y;
      this->_head = other._head;
      this->_tail = other._tail;
    }
  return (*this);
}

Link::~Link()
{
}

//
// GETTERS
//

unsigned int			Link::getX(void) const
{
  return (this->_x);
}

unsigned int			Link::getY(void) const
{
  return (this->_y);
}

bool				Link::isHead(void) const
{
  return (this->_head);
}

bool				Link::isTail(void) const
{
  return (this->_tail);
}

//
// SETTERS
//

void				Link::setX(unsigned int x)
{
  this->_x = x;
}

void				Link::setY(unsigned int y)
{
  this->_y = y;
}

void				Link::setHead(bool head)
{
  this->_head = head;
}

void				Link::setTail(bool tail)
{
  this->_tail = tail;
}
