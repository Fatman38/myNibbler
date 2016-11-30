//
// LibOpengl.hpp for nibbler in /home/montre_n/tech2/cpp/cpp_nibbler/opengl
// 
// Made by nicolas montredon
// Login   <montre_n@epitech.net>
// 
// Started on  Sun Mar 29 19:29:54 2015 nicolas montredon
// Last update Sun Apr  5 21:59:49 2015 nicolas montredon
//

#ifndef LIBOPENGL_HPP_
# define LIBOPENGL_HPP_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_audio.h>
# include <SDL/SDL_mixer.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include "IDisplayPlugin.hpp"
# include "Error.hpp"
# include "Nibbler.hpp"

class LibOpengl : public IDisplayPlugin
{
private:
  unsigned int						SizeX;
  unsigned int						SizeY;
  std::map<int, EventType>				_events;
  std::map<int, char>					_name;
  int							esc;
  SDL_Surface						*_window;
  Mix_Music						*_music;
  Mix_Chunk						*_toasty;

  LibOpengl					(const LibOpengl &);
  LibOpengl			&operator=	(const LibOpengl &);

  void				displayElement	(char) const;
  void				drawMap         (void) const;
  void				drawCube        (int, int) const;
  void				drawHead        (int, int) const;
  void				drawTail        (int, int) const;
  void				drawFood        (int, int) const;
  void			        drawPause	() const;
  void				gameOver	() const;

public:
  LibOpengl					();
  virtual ~LibOpengl				();

  virtual void			init		(unsigned int, unsigned int);
  virtual void			stop		();
  virtual EventType		waitEvent	();
  virtual void			display		(std::vector<char> const &,
						 GameData const &);
  virtual void			getNewScoreName	(char *);
};

extern "C" IDisplayPlugin	*loading	();

#endif /* !LIBOPENGL_HPP_ */
