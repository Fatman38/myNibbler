//
// LibOpengl.cpp for nibbler in /home/montre_n/tech2/cpp/cpp_nibbler/opengl
// 
// Made by nicolas montredon
// Login   <montre_n@epitech.net>
// 
// Started on  Sun Mar 29 19:27:03 2015 nicolas montredon
// Last update Sun Apr  5 22:00:21 2015 nicolas montredon
//

#include "LibOpengl.hpp"

//
// CTORS, DTORS, ETC
//

LibOpengl::LibOpengl			()
{
  this->_events[SDLK_LEFT] = E_KEY_LEFT;
  this->_events[SDLK_RIGHT] = E_KEY_RIGHT;
  this->_events[SDLK_UP] = E_KEY_UP;
  this->_events[SDLK_DOWN] = E_KEY_DOWN;
  this->_events[SDLK_ESCAPE] = E_KEY_ESC;
  this->_events[SDLK_SPACE] = E_KEY_SPACE;
  this->_events[SDLK_z] = E_KEY_Z;
  this->_events[SDLK_q] = E_KEY_Q;
  this->_events[SDLK_s] = E_KEY_S;
  this->_events[SDLK_d] = E_KEY_D;
  this->_events[SDLK_a] = E_KEY_PREV;
  this->_events[SDLK_e] = E_KEY_NEXT;

  this->esc = false;
  this->_toasty = NULL;
}

LibOpengl::LibOpengl			(const LibOpengl &)
{
}

LibOpengl				&LibOpengl::operator=(const LibOpengl &)
{
  return (*this);
}

LibOpengl::~LibOpengl			()
{
}

//
// LIB FUNCTIONS
//

void					LibOpengl::init(unsigned int sizeX,
							unsigned int sizeY)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    throw Error ("SDL_Init", "init() OPENGL");

  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    throw Error ("Mix_OpenAudio", "init() OPENGL");

  SDL_WM_SetCaption("Nibbler - OpenGL", NULL);
  this->_window = SDL_SetVideoMode(1536, 720, 32, SDL_OPENGL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, static_cast<double>(1536/720), 1, 1000);

  glEnable(GL_DEPTH_TEST);

  this->SizeX = sizeX;
  this->SizeY = sizeY;

  if ((this->_music = Mix_LoadMUS("./Plugins/OPENGL/music/music.wav")) == NULL)
    throw Error ("music", "init() OPENGL");

  this->_toasty = Mix_LoadWAV("./Plugins/OPENGL/music/toasty.wav");
   if (this->_toasty == NULL)
     throw Error ("music", "init() OPENGL");
}

void					LibOpengl::stop()
{
  Mix_PauseMusic();
  if (this->esc == false)
    this->gameOver();
  Mix_FreeMusic(this->_music);
  Mix_FreeChunk(this->_toasty);
  Mix_CloseAudio();
  SDL_Quit();
}

EventType				LibOpengl::waitEvent()
{
  SDL_Event				event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN && this->_events.find(event.key.keysym.sym) != this->_events.end())
	{
	  if (this->_events[event.key.keysym.sym] == E_KEY_ESC)
	    {
	      this->esc = true;
	    }
	  else if (this->_events[event.key.keysym.sym] == E_KEY_NEXT
		   || this->_events[event.key.keysym.sym] == E_KEY_PREV)
	    this->esc = true;
	  return (this->_events[event.key.keysym.sym]);
	}
    }
  return (E_NULL);
}

void					LibOpengl::display(std::vector<char> const &board, GameData const &data)
{
  std::vector<char>::const_iterator	it;

  if (Mix_PlayingMusic() == 0 && data._pause == false)
    if( Mix_PlayMusic(this->_music, -1) == -1)
      throw Error ("music", "display OPENGL");

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(7 * (this->SizeX / 2 + 7 * this->SizeY / 3) / 15 + 10, this->SizeX / 2, 30 + 3 * (this->SizeX + this->SizeY) / 20,
  	    -30, this->SizeX / 2, -30,
  	    0, 0, 1);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  this->drawMap();

  for (it = board.begin(); it != board.end(); ++it)
    this->displayElement(*it);

  if (data._pause == true)
    drawPause();
  else if (Mix_PausedMusic() == 1 && data._pause == false)
    Mix_ResumeMusic();

  glFlush();
  SDL_GL_SwapBuffers();
}

void					LibOpengl::getNewScoreName(char *dest)
{
  (void)(dest);
}

//
// LOADING
//

extern "C" IDisplayPlugin		*loading()
{
  return (new LibOpengl);
}

//
// Private methode
//

void				        LibOpengl::displayElement(char c) const
{
  static unsigned int			i = 0;

  if (c == FOOD)
    drawFood(i / this->SizeX, i % this->SizeX);
  else if (c == SNAKE_HEAD)
    drawHead(i / this->SizeX, i % this->SizeX);
  else if (c != FREE_SPACE)
    drawTail(i / this->SizeX, i % this->SizeX);
  ++i;
  if (i == this->SizeX * this->SizeY)
    i = 0;
}

void					LibOpengl::gameOver() const
{
  if (Mix_PlayChannel(-1, this->_toasty, 0) == -1)
    throw Error ("Mix_PlauChanel", "displayElement() OPENGL");
  SDL_Delay(1300);
  return ;
}


void					LibOpengl::drawPause() const
{
  if (Mix_PausedMusic() != 1)
    Mix_PauseMusic();
}

void					LibOpengl::drawMap         (void) const
{
  glBegin(GL_QUADS);

  glColor3ub(255, 255, 255);
  glVertex3d(this->SizeY, this->SizeX, 0);
  glVertex3d(this->SizeY, 0, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, this->SizeX, 0);

  glEnd();
}

void					LibOpengl::drawCube        (int x, int y) const
{
  glBegin(GL_QUADS);

  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x, y + 1, 0);
  glVertex3d(x, y + 1, 1);

  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x + 1, y + 1, 0);
  glVertex3d(x + 1, y + 1, 1);

  glVertex3d(x, y, 1);
  glVertex3d(x, y, 0);
  glVertex3d(x + 1, y, 0);
  glVertex3d(x + 1, y, 1);

  glVertex3d(x, y + 1, 1);
  glVertex3d(x, y + 1, 0);
  glVertex3d(x, y, 0);
  glVertex3d(x, y, 1);

  glVertex3d(x + 1, y, 1);
  glVertex3d(x + 1, y + 1, 1);
  glVertex3d(x, y + 1, 1);
  glVertex3d(x, y, 1);

  glEnd();
}

void					LibOpengl::drawHead        (int x, int y) const
{
  glColor3ub(255, 0, 0);
  this->drawCube(x, y);
}

void					LibOpengl::drawTail        (int x, int y) const
{
  glColor3ub(0, 255, 255);
  this->drawCube(x, y);
}

void					LibOpengl::drawFood        (int x, int y) const
{
  glColor3ub(0, 255, 0);
  this->drawCube(x, y);
}
