//
// LibNcurses.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t/Plugins
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Fri Mar 27 16:28:20 2015 Thibaud Auzou
// Last update Sun Apr  5 18:19:52 2015 Thibaud Auzou
//

#include "LibNcurses.hpp"

//
// CTORS, DTORS, ETC
//

LibNcurses::LibNcurses			()
{
  this->_events[KEY_LEFT] = E_KEY_LEFT;
  this->_events[KEY_RIGHT] = E_KEY_RIGHT;
  this->_events[KEY_UP] = E_KEY_UP;
  this->_events[KEY_DOWN] = E_KEY_DOWN;
  this->_events[KEY_ESC] = E_KEY_ESC;
  this->_events[KEY_Z] = E_KEY_Z;
  this->_events[KEY_Q] = E_KEY_Q;
  this->_events[KEY_S] = E_KEY_S;
  this->_events[KEY_D] = E_KEY_D;
  this->_events[KEY_SPACE] = E_KEY_SPACE;
  this->_events[KEY_A] = E_KEY_PREV;
  this->_events[KEY_E] = E_KEY_NEXT;
  this->_window = NULL;
  this->_winData = NULL;
}

LibNcurses::LibNcurses			(const LibNcurses &o)
{
  this->_x = o._x;
  this->_y = o._y;
  this->_events = o._events;
  this->_window = o._window;
  this->_winData = o._winData;
  this->_offset = o._offset;
}

LibNcurses				&LibNcurses::operator=(const LibNcurses &o)
{
  if (this != &o)
    {
      this->_x = o._x;
      this->_y = o._y;
      this->_events = o._events;
      this->_window = o._window;
      this->_winData = o._winData;
      this->_offset = o._offset;
    }
  return (*this);
}

LibNcurses::~LibNcurses			()
{
}

//
// LIB FUNCTIONS
//

void					LibNcurses::init(unsigned int sizeX,
							 unsigned int sizeY)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(FALSE);
  timeout(0);
  start_color();
  init_color(COLOR_BLACK, 0, 0, 0);
  init_color(COLOR_MAGENTA, 50, 50, 50);
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_BLUE, COLOR_BLUE);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLUE);
  init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
  this->_x = sizeX;
  this->_y = sizeY;
  this->printDecoration();
}

void					LibNcurses::stop()
{
  if (this->_window)
    delwin(this->_window);
  if (this->_winData)
    delwin(this->_winData);
  endwin();
}

EventType				LibNcurses::waitEvent()
{
  int					c;

  if ((c = getch()) != ERR && this->_events.find(c) != this->_events.end())
    return (this->_events[c]);
  return (E_NULL);
}

void					LibNcurses::display(std::vector<char> const &board,
							    GameData const &data)
{
  std::vector<char>::const_iterator	it;
  int					col;
  int					row;

  getmaxyx(stdscr, row, col);
  ++row;
  delwin(this->_window);
  this->_window = newwin(this->_y + 2, this->_x + 2, this->_offset, (col - _x) / 2 - 15);
  wbkgd(this->_window, COLOR_PAIR(6));
  wattron(this->_window, COLOR_PAIR(1));
  box(this->_window, 'X', 'X');
  wattroff(this->_window, COLOR_PAIR(1));
  for (it = board.begin(); it != board.end(); ++it)
    this->displayElement(*it);
  this->displayGameData(data);
  wrefresh(this->_window);
  wrefresh(this->_winData);
  refresh();
}

void					LibNcurses::displayElement(char c)
{
  static unsigned int			i = 0;
  int					color;
  unsigned int				x;
  unsigned int				y;

  color = 1;
  if (c == FOOD)
    color = 3;
  else if (c == SNAKE_HEAD)
    color = 2;
  if (c != FREE_SPACE)
    {
      x = (i % this->_x) + 1;
      (x > this->_x) ? (x = 1) : (x = x);
      y = (i / this->_x) + 1;
      wattron(this->_window, COLOR_PAIR(color));
      mvwprintw(this->_window, y, x, " ");
      wattroff(this->_window, COLOR_PAIR(color));
    }
  ++i;
  if (i == this->_x * this->_y)
    i = 0;
}

void					LibNcurses::displayGameData(GameData const &data)
{
  int					row;
  int					col;

  getmaxyx(stdscr, row, col);
  ++row;
  delwin(this->_winData);
  this->_winData = newwin(this->_y + 2, 30, this->_offset, ((col - _x) / 2 - 15) + _x + 3);
  wattron(this->_winData, A_BOLD);
  mvwprintw(this->_winData, 2, 2, "SPEED : %d\n", 4 - data._speed);
  mvwprintw(this->_winData, 3, 2, "SCORE : %u\n", data._score);
  mvwprintw(this->_winData, 5, 2, "----------\n");
  mvwprintw(this->_winData, 7, 2, "BEST SSCORE : %u\n", data._bestScore);
  mvwprintw(this->_winData, 8, 2, "BY : %s\n", data._bestScoreName->c_str());
  wattroff(this->_winData, A_BOLD);
  wattron(this->_winData, COLOR_PAIR(3));
  box(this->_winData, ' ', ' ');
  wattroff(this->_winData, COLOR_PAIR(3));
}

//
// DECORATION
//

static int			strlen(char *str)
{
  int				i;

  for (i = 0; str && str[i]; ++i);
  return (i);
}

void				LibNcurses::printDecoration(void)
{
  int				col;
  int				row;
  int				y;
  char				buff[512];
  std::ifstream			file("Plugins/NCURSES/AsciiArt/nibbler.ascii");

  attron(COLOR_PAIR(4));
  attron(A_BOLD);
  getmaxyx(stdscr, row, col);
  y = 0;
  while (file.getline(buff, 512))
    {
      mvprintw(y, (col - strlen(buff)) / 2, "%s", buff);
      y++;
    }
  this->_offset = y + 2;
  attroff(A_BOLD);
  attroff(COLOR_PAIR(4));
  ++row;
  refresh();
}

//
// SCORE
//

void				LibNcurses::getNewScoreName(char *buff)
{
  int				row;
  int				col;
  std::string			msg("Congratulation This Is A New Reccord !");
  std::string			name("Please Enter Your Name : ");

  delwin(this->_winData);
  delwin(this->_window);
  this->_winData = NULL;
  this->_window = NULL;
  clear();
  refresh();
  getmaxyx(stdscr, row, col);
  mvprintw(row / 2, (col - msg.size()) / 2, "%s", msg.c_str());
  mvprintw(row / 2 + 1, (col - msg.size()) / 2, "%s", name.c_str());
  echo();
  curs_set(TRUE);
  timeout(-1);
  getstr(buff);
}

//
// LOADING
//

extern "C" IDisplayPlugin		*loading()
{
  return (new LibNcurses);
}
