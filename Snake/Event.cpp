//
// Event.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Thu Mar 26 19:42:25 2015 Thibaud Auzou
// Last update Sat Apr  4 20:17:57 2015 Thibaud Auzou
//

#include "Snake.hpp"

//
// CTORS ETC
//

Snake::Event::Event		()
  : _snake(NULL)
{
}

Snake::Event::Event		(Snake *snake)
  : _snake(snake)
{
  this->_events[E_KEY_LEFT] = &Snake::Event::turnLeft;
  this->_events[E_KEY_RIGHT] = &Snake::Event::turnRight;
  this->_events[E_KEY_Z] = &Snake::Event::turnDirectTop;
  this->_events[E_KEY_S] = &Snake::Event::turnDirectBottom;
  this->_events[E_KEY_Q] = &Snake::Event::turnDirectLeft;
  this->_events[E_KEY_D] = &Snake::Event::turnDirectRight;
  this->_events[E_KEY_UP] = &Snake::Event::increaseSpeed;
  this->_events[E_KEY_DOWN] = &Snake::Event::decreaseSpeed;
  this->_events[E_KEY_ESC] = &Snake::Event::killSnake;
  this->_events[E_KEY_SPACE] = &Snake::Event::pauseGame;
}

Snake::Event::Event		(Snake::Event const &)
{
}

Snake::Event			&Snake::Event::operator=(Snake::Event const &)
{
  return (*this);
}

Snake::Event::~Event		()
{
}

//
// EVENTS
//

int				Snake::Event::handleEvent(EventType event)
{
  if (event == E_KEY_NEXT)
    return (1);
  else if (event == E_KEY_PREV)
    return (-1);
  if (event != E_NULL && !this->_snake->getPause())
    (this->*(_events[event]))();
  else if (event != E_NULL && this->_snake->getPause() &&
	   (event == E_KEY_SPACE || event == E_KEY_ESC))
    (this->*(_events[event]))();
  return (0);
}

void				Snake::Event::pauseGame(void) const
{
  if (this->_snake->getPause() == true)
    this->_snake->setPause(false);
  else
    this->_snake->setPause(true);
}

void				Snake::Event::turnLeft(void) const
{
  int				dir;

  dir = this->_snake->getDirection();
  (dir - 1 < 0) ? (dir = LEFT) : (--dir);
  this->_snake->setDirection(static_cast<Direction>(dir));
}

void				Snake::Event::turnRight(void) const
{
  int				dir;

  dir = this->_snake->getDirection();
  (dir + 1 > 3) ? (dir = TOP) : (++dir);
  this->_snake->setDirection(static_cast<Direction>(dir));
}

void				Snake::Event::turnDirectTop(void) const
{
  if (this->_snake->getDirection() != BOTTOM)
    this->_snake->setDirection(TOP);
}

void				Snake::Event::turnDirectBottom(void) const
{
  if (this->_snake->getDirection() != TOP)
    this->_snake->setDirection(BOTTOM);
}

void				Snake::Event::turnDirectLeft(void) const
{
  if (this->_snake->getDirection() != RIGHT)
    this->_snake->setDirection(LEFT);
}

void				Snake::Event::turnDirectRight(void) const
{
  if (this->_snake->getDirection() != LEFT)
    this->_snake->setDirection(RIGHT);
}

void				Snake::Event::increaseSpeed(void) const
{
  int				speed;

  speed = this->_snake->getSpeed();
  (speed - 1 < 0) ? (speed = VERY_FAST) : (--speed);
  this->_snake->setSpeed(static_cast<Speed>(speed));
}

void				Snake::Event::decreaseSpeed(void) const
{
  int				speed;

  speed = this->_snake->getSpeed();
  (speed + 1 > 4) ? (speed = VERY_SLOW) : (++speed);
  this->_snake->setSpeed(static_cast<Speed>(speed));
}

void				Snake::Event::killSnake(void) const
{
  this->_snake->killSnake();
}

//
// GETTERS
//

Snake				*Snake::Event::getSnake(void) const
{
  return (this->_snake);
}
