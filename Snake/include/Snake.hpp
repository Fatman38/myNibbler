//
// Snake.hpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t/Snake
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 18:49:51 2015 Thibaud Auzou
// Last update Sat Apr  4 20:06:03 2015 Thibaud Auzou
//

#ifndef SNAKE_HPP_
# define SNAKE_HPP_

# include "Nibbler.hpp"
# include "Board.hpp"
# include "Link.hpp"

class Snake
{
  typedef void (Snake::*moveFunction)	(Link *, Link *);

  std::list<Link *>			_links;
  std::map<Direction, moveFunction>	_moves;
  Direction				_direction;
  Speed					_speed;
  Board					*_board;
  bool					_alive;
  bool					_win;
  bool					_pause;

  Snake					();
  Snake			&operator=	(const Snake &);
  Snake					(const Snake &);

  void			goUp		(Link *, Link *);
  void			goDown		(Link *, Link *);
  void			goLeft		(Link *, Link *);
  void			goRight		(Link *, Link *);

public:
  Snake					(Board *);
  ~Snake				();

  Direction		getDirection	(void) const;
  Speed			getSpeed	(void) const;
  bool			isAlive		(void) const;
  bool			hasWon		(void) const;
  Board			*getBoard	(void) const;
  bool			getPause	(void) const;

  void			setDirection	(Direction);
  void			setSpeed	(Speed);
  void			killSnake	(void);
  void			snakeWin	(void);
  void			setPause	(bool);

  void			placeSnake	(void) const;
  void			removeSnake	(void) const;
  void			moveSnake	(void);

  Snake			&operator++	(void);

  class Event
  {
    typedef void (Snake::Event::*eventHandler) (void) const;

    std::map<EventType, eventHandler>	_events;
    Snake				*_snake;

    void		turnLeft	(void) const;
    void		turnRight	(void) const;
    void		turnDirectTop	(void) const;
    void		turnDirectBottom(void) const;
    void		turnDirectLeft	(void) const;
    void		turnDirectRight	(void) const;
    void		increaseSpeed	(void) const;
    void		decreaseSpeed	(void) const;
    void		killSnake	(void) const;
    void		pauseGame       (void) const;

    Event				(Event const &);
    Event		&operator=	(Event const &);
    Event				();

  public:
    Event				(Snake *);
    ~Event				();
    int			handleEvent	(EventType);
    Snake		*getSnake	(void) const;
  };
};

#endif /* !SNAKE_HPP_ */
