//
// Nibbler.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Sat Apr  4 16:53:20 2015 Thibaud Auzou
// Last update Sun Apr  5 22:03:50 2015 Thibaud Auzou
//

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <list>
# include <map>
# include <algorithm>
# include <stdexcept>
# include <ctime>
# include <dlfcn.h>

/*
** ERROR CODES
*/
# define RAS		0
# define NOK		1
# define ERROR		-1

/*
** DEFAULT SETUPS
*/
# define NB_LINKS_START	4
# define MIN_WIDTH	20
# define MIN_HEIGHT	20
# define MAX_WIDTH	100
# define MAX_HEIGHT	100
# define SPEED_COEF	20000
# define BUFF_SIZE	512

/*
** CHARS KIND
*/
# define FOOD		'#'
# define SNAKE_HEAD	'@'
# define SNAKE_LINK	'0'
# define SNAKE_TAIL	'~'
# define FREE_SPACE	' '

/*
** Window
*/
# define SIZE_X		1200
# define SIZE_Y		900
# define MARGIN_X	50
# define MARGIN_Y	100
# define BOARD_X       	(SIZE_X - MARGIN_X * 2)
# define BOARD_Y	(SIZE_Y - (MARGIN_Y + MARGIN_X))

/*
** EVENT TYPE ENUM
*/
typedef enum		EventType
  {
    E_KEY_LEFT,
    E_KEY_RIGHT,
    E_KEY_Z,
    E_KEY_S,
    E_KEY_Q,
    E_KEY_D,
    E_KEY_UP,
    E_KEY_DOWN,
    E_KEY_ESC,
    E_KEY_SPACE,
    E_KEY_NEXT,
    E_KEY_PREV,
    E_NULL,
  }			EventType;

/*
** DIRECTIONAL ENUM
*/
typedef enum		Direction
  {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
  }			Direction;

/*
** SPEED ENUM
*/
typedef enum		Speed
  {
    VERY_FAST,
    FAST,
    NORMAL,
    SLOW,
    VERY_SLOW,
  }			Speed;

/*
** IG DATA STRUCTURE
*/
typedef struct		GameData
{
  unsigned int		_score;
  Speed			_speed;
  std::string		*_bestScoreName;
  unsigned int		_bestScore;
  bool			_pause;
}			GameData;

/*
** Generic Functions
*/
class			Snake;
class			IDisplayPlugin;
int			checkArg(unsigned int, unsigned int);
int			playNibbler(unsigned int, unsigned int, std::string const &);
int			printError(std::string const &);
int			saveNewScore(unsigned int, IDisplayPlugin *);
GameData const          &getGameData(GameData &, Snake const &);

#endif /* !NIBBLER_HPP_ */
