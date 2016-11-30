//
// Snake.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t/Snake
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 18:49:45 2015 Thibaud Auzou
// Last update Fri Apr  3 13:50:35 2015 Thibaud Auzou
//

#include "Snake.hpp"

//
// CTORS, DTORS, COPLIEN & FRIENDS
//

Snake::Snake			(Board *board)
  : _direction(TOP), _speed(NORMAL), _board(board), _alive(true), _win(false)
{
  int				i = 0;

  for (; i < NB_LINKS_START; ++i)
    _links.push_back(new Link(board->getSizeX() / 2, board->getSizeY() / 2 + i));
  this->_links.front()->setHead(true);
  this->_links.back()->setTail(true);
  this->_moves[TOP] = &Snake::goUp;
  this->_moves[BOTTOM] = &Snake::goDown;
  this->_moves[LEFT] = &Snake::goLeft;
  this->_moves[RIGHT] = &Snake::goRight;
  this->_pause = false;
}

Snake::Snake			(const Snake &other)
  : _direction(other._direction), _speed(other._speed), _board(other._board)
{
}

Snake				&Snake::operator=(const Snake &other)
{
  if (&other != this)
    {
      _links = other._links;
      _direction = other._direction;
      _speed = other._speed;
      _board = other._board;
      _alive = other._alive;
    }
  return (*this);
}

Snake::~Snake			()
{
  std::list<Link *>::iterator	it;

  for (it = this->_links.begin(); it != this->_links.end(); ++it)
    delete *it;
}

//
// GETTERS
//

Direction			Snake::getDirection(void) const
{
  return (this->_direction);
}

Speed				Snake::getSpeed(void) const
{
  return (this->_speed);
}

bool				Snake::isAlive(void) const
{
  return (this->_alive);
}

bool				Snake::hasWon(void) const
{
  return (this->_win);
}

Board				*Snake::getBoard(void) const
{
  return (this->_board);
}

bool				Snake::getPause(void) const
{
  return (this->_pause);
}
//
// SETTERS
//

void				Snake::setDirection(Direction direction)
{
  this->_direction = direction;
}

void				Snake::setSpeed(Speed speed)
{
  this->_speed = speed;
}

void				Snake::killSnake(void)
{
  this->_alive = false;
}

void				Snake::snakeWin(void)
{
  this->_win = true;
}

void				Snake::setPause(bool a)
{
  this->_pause = a;
}

//
// PLAYING GAME
//

void					Snake::placeSnake(void) const
{
  std::list<Link *>::const_iterator	it;

  for (it = this->_links.begin(); it != this->_links.end(); ++it)
    this->_board->setLink(*it);
}

void					Snake::removeSnake(void) const
{
  std::list<Link *>::const_iterator	it;

  for (it = this->_links.begin(); it != this->_links.end(); ++it)
    this->_board->unsetLink(*it);
}

static bool				headIsOnFood(Link *head, Food *food)
{
  if (!head || !food)
    return (false);
  if (head->getX() == food->getX() && head->getY() == food->getY())
    return (true);
  return (false);
}

void					Snake::moveSnake(void)
{
  Link					*new_head = this->_links.back();
  Link					*old_head = this->_links.front();
  Link tmp(*new_head);

  old_head->setHead(false);
  new_head->setHead(true);
  new_head->setTail(false);
  this->_links.pop_back();
  this->_links.back()->setTail(true);
  (this->*(_moves[this->_direction]))(new_head, old_head);
  this->_links.push_front(new_head);
  this->_board->unsetLink(new_head);
  this->_board->unsetLink(old_head);
  this->_board->unsetLink(this->_links.back());
  this->_board->unsetLink(&tmp);
  this->_board->setLink(new_head);
  this->_board->setLink(old_head);
  this->_board->setLink(this->_links.back());
  if (headIsOnFood(new_head, this->_board->getFood()))
    {
      ++(*this);
      this->_board->removeFood();
    }
}

//
// MOVING
//

void				Snake::goUp(Link *new_head, Link *head)
{
  new_head->setX(head->getX());
  if (!this->_board->canMoveHere(head->getX(), head->getY() - 1))
    this->killSnake();
  else
    new_head->setY(head->getY() - 1);
}

void				Snake::goDown(Link *new_head, Link *head)
{
  new_head->setX(head->getX());
  if (!this->_board->canMoveHere(head->getX(), head->getY() + 1))
    this->killSnake();
  else
    new_head->setY(head->getY() + 1);
}

void				Snake::goLeft(Link *new_head, Link *head)
{
  new_head->setY(head->getY());
  if (!this->_board->canMoveHere(head->getX() - 1, head->getY()))
    this->killSnake();
  else
    new_head->setX(head->getX() - 1);
}

void				Snake::goRight(Link *new_head, Link *head)
{
  new_head->setY(head->getY());
  if (!this->_board->canMoveHere(head->getX() + 1, head->getY()))
    this->killSnake();
  else
    new_head->setX(head->getX() + 1);
}

//
// OPERATORS
//

Snake				&Snake::operator++(void)
{
  int				x = this->_links.back()->getX();
  int				y = this->_links.back()->getY();
  std::list<Link *>::iterator	it;

  if (this->_board->placeIsFree(x + 1, y))
    this->_links.push_back(new Link(x + 1, y));
  else if (this->_board->placeIsFree(x - 1, y))
    this->_links.push_back(new Link(x - 1, y));
  else if (this->_board->placeIsFree(x, y + 1))
    this->_links.push_back(new Link(x, y + 1));
  else if (this->_board->placeIsFree(x, y - 1))
    this->_links.push_back(new Link(x, y - 1));
  else
    this->snakeWin();
  it = this->_links.end();
  --it;
  (*it)->setTail(true);
  --it;
  (*it)->setTail(false);
  return (*this);
}
