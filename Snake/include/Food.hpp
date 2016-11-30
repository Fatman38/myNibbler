//
// Food.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Wed Mar 25 09:02:38 2015 Thibaud Auzou
// Last update Wed Mar 25 09:08:29 2015 Thibaud Auzou
//

#ifndef FOOD_HPP_
# define FOOD_HPP_

# include "Nibbler.hpp"

class Food
{
  unsigned int const		_x;
  unsigned int const		_y;

  Food				();
  Food		&operator=	(const Food &);

public:
  Food				(unsigned int, unsigned int);
  Food				(const Food &);
  ~Food				();

  unsigned int	getX		(void) const;
  unsigned int	getY		(void) const;
};

#endif /* !FOOD_HPP_ */
