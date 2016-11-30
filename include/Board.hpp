//
// Board.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 19:12:42 2015 Thibaud Auzou
// Last update Sat Mar 28 16:24:57 2015 Thibaud Auzou
//

#ifndef BOARD_HPP_
# define BOARD_HPP_

# include "Nibbler.hpp"
# include "Link.hpp"
# include "Food.hpp"

class Board
{
  unsigned int const					_sizeX;
  unsigned int const					_sizeY;
  Food							*_food;
  std::vector<char>					_board;

  unsigned int						_score;
  unsigned int						_bestScore;
  std::string						_bestScoreName;

  Board							();
  Board				&operator=		(const Board &);
  void				getScoreFromFile	(void);

public:
  Board							(unsigned int, unsigned int);
  Board							(const Board &);
  ~Board						();

  unsigned int			getSizeX		(void) const;
  unsigned int			getSizeY		(void) const;
  Food				*getFood		(void) const;
  std::vector<char> const	&getBoard		(void) const;
  std::string			*getBestScoreName	(void);
  unsigned int			getBestScore		(void) const;
  unsigned int			getScore		(void) const;

  void				setLink			(Link *);
  void				unsetLink		(Link *);
  void				placeFood		(void);
  void				removeFood		(void);

  bool				placeIsFree		(int, int) const;
  bool				canMoveHere		(int, int) const;

  void				displayBoard		(void) const;

};

#endif /* !BOARD_HPP_ */
