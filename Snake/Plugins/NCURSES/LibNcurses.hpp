//
// LibNcurses.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t/Plugins
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Fri Mar 27 16:28:28 2015 Thibaud Auzou
// Last update Sun Apr  5 18:11:28 2015 Thibaud Auzou
//

#ifndef LIBNCURSES_HPP_
# define LIBNCURSES_HPP_

# include <ncurses.h>
# include "IDisplayPlugin.hpp"
# include "Error.hpp"

# define KEY_ESC					27
# define KEY_Z						122
# define KEY_Q						113
# define KEY_S						115
# define KEY_D						100
# define KEY_SPACE					32
# define KEY_A						97
# define KEY_E						101

class LibNcurses : public IDisplayPlugin
{
  unsigned int						_x;
  unsigned int						_y;
  std::map<int, EventType>				_events;
  WINDOW						*_window;
  WINDOW						*_winData;
  int							_offset;

  void				displayElement	(char);
  void				displayGameData	(GameData const &);
  void				printDecoration	(void);

public:
  LibNcurses					();
  LibNcurses					(const LibNcurses &);
  LibNcurses			&operator=	(const LibNcurses &);
  virtual ~LibNcurses				();

  virtual void			init		(unsigned int, unsigned int);
  virtual void			stop		();
  virtual EventType		waitEvent	();
  virtual void			display		(std::vector<char> const &, GameData const &);
  virtual void			getNewScoreName	(char *);
};

extern "C" IDisplayPlugin	*loading	();

#endif /* !LIBNCURSES_HPP_ */
