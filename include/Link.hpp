#ifndef LINK_HPP_
# define LINK_HPP_

# include "Nibbler.hpp"

class Link
{
  unsigned int			_x;
  unsigned int			_y;
  bool				_head;
  bool				_tail;

  Link				();

public:
  Link				(unsigned int, unsigned int);
  Link				(const Link &);
  Link				&operator=(const Link &);
  ~Link				();

  unsigned int			getX(void) const;
  unsigned int			getY(void) const;
  bool				isHead(void) const;
  bool				isTail(void) const;

  void				setX(unsigned int);
  void				setY(unsigned int);
  void				setHead(bool);
  void				setTail(bool);
};

#endif /* !LINK_HPP_ */
