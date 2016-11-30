//
// IDisplayModule.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Mon Mar 23 10:01:11 2015 Thibaud Auzou
// Last update Sun Mar 29 10:28:05 2015 quentin vieira
//

#ifndef IDISPLAYMODULE_HPP_
# define IDISPLAYMODULE_HPP_

# include "Nibbler.hpp"
# include "Board.hpp"

# define WIN_X				800
# define WIN_Y				800
# define WIN_NAME			"Nibbler"

class IDisplayPlugin
{

public:
  virtual		~IDisplayPlugin	() {};

  virtual void		init		(unsigned int, unsigned int) = 0;
  virtual void		stop		() = 0;
  virtual EventType	waitEvent	() = 0;
  virtual void		display		(std::vector<char> const &, GameData const &) = 0;
  virtual void		getNewScoreName	(char *) = 0;
};

#endif /* !IDISPLAYMODULE_HPP_ */
