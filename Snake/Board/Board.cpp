//
// Board.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 19:13:02 2015 Thibaud Auzou
// Last update Sat Mar 28 17:57:09 2015 Thibaud Auzou
//

#include "Board.hpp"

//
// CTORS, DTORS, COPLIEN & FRIENDS
//

Board::Board				()
  : _sizeX(42), _sizeY(42)
{
}

Board::Board				(unsigned int sizeX, unsigned int sizeY)
  : _sizeX(sizeX), _sizeY(sizeY), _food(NULL)
{
  unsigned int				i = 0;

  for (; i < sizeX * sizeY; ++i)
    _board.push_back(' ');
  this->_score = 0;
  this->_bestScore = 0;
  this->_bestScoreName = "%NaN%";
  this->getScoreFromFile();
}

Board::Board				(const Board &other)
  : _sizeX(other._sizeX), _sizeY(other._sizeY), _food(other._food), _board(other._board)
{
}

Board					&Board::operator=(const Board &)
{
  return (*this);
}

Board::~Board				()
{
  this->removeFood();
}

//
// GETTERS
//

void					Board::getScoreFromFile(void)
{
  std::stringstream			s;
  std::ifstream				file(".score");
  std::string				line;
  std::string::size_type		pos;

  if (!file.fail() && !file.bad())
    {
      std::getline(file, line);
      pos = line.find(";");
      if (pos == std::string::npos)
	return;
      this->_bestScoreName = line.substr(0, pos);
      s << line.substr(pos + 1, std::string::npos);
      s >> this->_bestScore;
    }
}

unsigned int				Board::getSizeX(void) const
{
  return (this->_sizeX);
}

unsigned int				Board::getSizeY(void) const
{
  return (this->_sizeY);
}

Food					*Board::getFood(void) const
{
  return (this->_food);
}

std::vector<char> const			&Board::getBoard(void) const
{
  return (this->_board);
}

unsigned int				Board::getScore(void) const
{
  return (this->_score);
}

unsigned int				Board::getBestScore(void) const
{
  return (this->_bestScore);
}

std::string				*Board::getBestScoreName(void)
{
  return (&(this->_bestScoreName));
}

//
// SETTERS
//

void					Board::setLink(Link *link)
{
  char					c;

  c = '0';
  if (link->isHead())
    c = '@';
  else if (link->isTail())
    c = '~';
  this->_board[link->getX() + (link->getY() * this->_sizeX)] = c;
}

void					Board::unsetLink(Link *link)
{
  this->_board[link->getX() + (link->getY() * this->_sizeX)] = ' ';
}

void					Board::placeFood(void)
{
  int					x = 0;
  int					y = 0;

  if (!this->_food)
    {
      do
	{
	  x = rand() % this->_sizeX;
	  y = rand() % this->_sizeY;
	} while (this->_board[x + (this->_sizeX * y)] != ' ');
      this->_board[x + (this->_sizeX * y)] = '#';
      this->_food = new Food(x, y);
    }
}

void					Board::removeFood(void)
{
  if (this->_food)
    delete this->_food;
  this->_food = NULL;
  this->_score++;
}

//
// MISC
//

bool					Board::placeIsFree(int x, int y) const
{
  if (x < 0 || y < 0)
    return (false);
  if (static_cast<unsigned int>(x) >= this->_sizeX
      || static_cast<unsigned int>(y) >= this->_sizeY)
    return (false);
  return (this->_board[x + (this->_sizeX * y)] == ' ');
}

bool					Board::canMoveHere(int x, int y) const
{
  char					c;

  if (x < 0 || y < 0)
    return (false);
  if (static_cast<unsigned int>(x) >= this->_sizeX
      || static_cast<unsigned int>(y) >= this->_sizeY)
    return (false);
  c = this->_board[x + (this->_sizeX * y)];
  return (c == ' ' || c == '#');
}

//
// DISPLAY
//

void					Board::displayBoard(void) const
{
  std::vector<char>::const_iterator	it;
  unsigned int				i = 0;

  std::cout << " ";
  for (i = 0; i < this->_sizeX; ++i)
    std::cout << "-";
  std::cout << std::endl << "|";
  for (i = 1, it = this->_board.begin(); it != this->_board.end(); ++i, ++it)
    {
      std::cout << *it;
      if (it + 1 == this->_board.end())
	std::cout << "|" << std::endl;
      else if (i >= this->_sizeX)
	{
	  std::cout << "|" << std::endl << "|";
	  i = 0;
	}
    }
  std::cout << " ";
  for (i = 0; i < this->_sizeX; ++i)
    std::cout << "-";
  std::cout << std::endl;
}
