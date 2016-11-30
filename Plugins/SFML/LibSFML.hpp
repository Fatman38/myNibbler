//
// Graph.hpp for  in /home/vieira_q/cpp/cpp_nibbler/vieira_q/src
// 
// Made by quentin vieira
// Login   <vieira_q@epitech.net>
// 
// Started on  Tue Mar 24 20:08:23 2015 quentin vieira
// Last update Sun Nov 20 23:47:10 2016 Fatman
//

#ifndef LIBSFML_HPP_
# define LIBSFML_HPP_

# include "Nibbler.hpp"
# include "IDisplayPlugin.hpp"
# include "Error.hpp"

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Audio/Music.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Audio/Sound.hpp>

class LibSFML : public IDisplayPlugin
{
  sf::RenderWindow		*_window;

  sf::Music			*_music;
  sf::Music			*_musicPauseOP;
  sf::Music			*_musicPauseCL;

  float				SizeX;
  float				SizeY;

  sf::Texture			*_food;
  sf::Texture			*_fond;
  sf::Texture			*_fond2;

  float				boardX;
  float				boardY;
  int				esc;
  bool				_pause;

  std::map<int, EventType>	_event;

public:
  // Constructors
  LibSFML						();
  LibSFML						(const LibSFML &);
  LibSFML&			operator=		(const LibSFML &);
  virtual ~LibSFML					();

  // Public methods
  virtual void			init			(unsigned int, unsigned int);
  virtual void			stop			();
  virtual EventType		waitEvent		();
  virtual void			display			(std::vector<char> const &, GameData const &);
  virtual void			getNewScoreName		(char *);
private :
  // Private methods
  void				draw_menu		(GameData const &) const;
  void				draw_back		();
  void				draw_pause		() const;
  void				draw_square		(int, int, int) const;
  void				draw_food		(int, int) const;
  void				game_over		();
};

extern "C" IDisplayPlugin *loading();

#endif /* !LIBSFML_HPP_ */
