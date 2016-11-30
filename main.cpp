//
// main.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 18:24:58 2015 Thibaud Auzou
// Last update Sun Apr  5 17:45:07 2015 Thibaud Auzou
//

#include "Nibbler.hpp"
#include "Board.hpp"
#include "Snake.hpp"
#include "DLLoader.hpp"
#include "Error.hpp"

int			main(int argc, char **argv)
{
  std::stringstream	av1;
  std::stringstream	av2;
  unsigned int		sizeX;
  unsigned int		sizeY;

  if (argc != 4 || argv == NULL)
    return (printError("Usage : ./nibbler [width] [height] [lib]"));
  av1 << argv[1];
  av2 << argv[2];
  av1 >> sizeX;
  av2 >> sizeY;
  if (checkArg(sizeX, sizeY) == ERROR)
    return (ERROR);
  try
    {
      playNibbler(sizeX, sizeY, argv[3]);
    }
  catch (Error const &e)
    {
      std::cerr << "EXCEPTION IN " << e.who() << " [" << e.what() << "]" << std::endl;
      return (ERROR);
    }
  catch (std::exception const &e)
    {
      std::cerr << "EXCEPTION STD [" << e.what() << "]" << std::endl;
      return (ERROR);
    }
  return (RAS);
}

int			checkArg(unsigned int sizeX, unsigned int sizeY)
{
  if (sizeX > MAX_WIDTH || sizeX < MIN_WIDTH)
    {
      std::cerr << "The Width Has To Be Between " << MIN_WIDTH
		<< " and " << MAX_WIDTH << std::endl;
      return (ERROR);
    }
  if (sizeY > MAX_HEIGHT || sizeY < MIN_HEIGHT)
    {
      std::cerr << "The Height Has To Be Between " << MIN_HEIGHT
		<< " and " << MAX_HEIGHT << std::endl;
      return (ERROR);
    }
  return (RAS);
}

static int		swapLib(int action,
				DLLoader *loader,
				IDisplayPlugin **lib,
				unsigned int sizeX,
				unsigned int sizeY)
{
  if (action == 1)
    {
      (*lib)->stop();
      *lib = loader->getNextInstance();
      if (*lib == NULL)
	return (0);
      (*lib)->init(sizeX, sizeY);
    }
  else if (action == -1)
    {
      (*lib)->stop();
      *lib = loader->getPrevInstance();
      if (*lib == NULL)
	return (0);
      (*lib)->init(sizeX, sizeY);
    }
  return (*lib != NULL);
}

static void		my_usleep(int msec)
{
  std::clock_t		goal = msec + std::clock();
  while (goal > std::clock());
}

int			playNibbler(unsigned int sizeX,
				    unsigned int sizeY,
				    std::string const &lib_name)
{
  Board			board(sizeX, sizeY);
  Snake			snake(&board);
  Snake::Event		handler(&snake);
  IDisplayPlugin	*lib;
  DLLoader		loader;
  GameData		data;

  if ((lib = loader.getInstance(lib_name)) == NULL)
    return (ERROR);
  lib->init(sizeX, sizeY);
  snake.placeSnake();
  while (snake.isAlive() && !snake.hasWon())
    {
      lib->display(board.getBoard(), getGameData(data, snake));
      if (!swapLib(handler.handleEvent(lib->waitEvent()), &loader, &lib, sizeX, sizeY))
	return (ERROR);
      board.placeFood();
      if (!snake.getPause())
	snake.moveSnake();
      my_usleep((snake.getSpeed() + 1) * SPEED_COEF);
    }
  if (board.getScore() > board.getBestScore())
    saveNewScore(board.getScore(), lib);
  lib->stop();
  return (RAS);
}

int			saveNewScore(unsigned int score, IDisplayPlugin *lib)
{
  char			buff[512];
  std::ofstream		file(".score", std::ofstream::trunc);

  if (!file.fail() && !file.bad())
    {
      lib->getNewScoreName(buff);
      file << buff << ";" << score << std::endl;
    }
  return (RAS);
}

GameData const		&getGameData(GameData &data, Snake const &snake)
{
  data._score = snake.getBoard()->getScore();
  data._speed = snake.getSpeed();
  data._bestScoreName = snake.getBoard()->getBestScoreName();
  data._bestScore = snake.getBoard()->getBestScore();
  data._pause = snake.getPause();
  return (data);
}
