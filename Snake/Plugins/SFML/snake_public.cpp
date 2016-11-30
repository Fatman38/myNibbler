//
// snake_public.cpp for  in /home/vieira_q/cpp/cpp_nibbler/vieira_q/Plugins/SFML
// 
// Made by quentin vieira
// Login   <vieira_q@epitech.net>
// 
// Started on  Fri Apr  3 15:43:04 2015 quentin vieira
// Last update Mon Nov 21 00:04:48 2016 Fatman
//

#include <iostream>
#include <string>
#include "LibSFML.hpp"

//
// Public methods
//
void LibSFML::init(unsigned int SizeX,
		   unsigned int SizeY)
{
  this->SizeX =  SizeX;
  this->SizeY =  SizeY;

  this->_music = new sf::Music;
  if (!this->_music->openFromFile("./Plugins/SFML/music/encounter.wav"))
    throw Error("music", "init() SFML");
  this->_music->setVolume(25);
  this->_music->play();
  this->_music->setLoop(true);

  this->_musicPauseOP = new sf::Music;
  if (!this->_musicPauseOP->openFromFile("./Plugins/SFML/music/Opening.wav"))
    throw Error("music", "init() SFML");
  this->_musicPauseOP->setVolume(35);
  this->_musicPauseOP->setLoop(false);

  this->_musicPauseCL = new sf::Music;
  if (!this->_musicPauseCL->openFromFile("./Plugins/SFML/music/Closing.wav"))
    throw Error("music", "init() SFML");
  this->_musicPauseCL->setVolume(35);
  this->_musicPauseCL->setLoop(false);

  this->_window = new sf::RenderWindow;
  this->_window->create(sf::VideoMode(SIZE_X, SIZE_Y), "Nibbler");
  this->_window->setPosition(sf::Vector2i(400, 80));
  this->_window->setFramerateLimit(60);

  this->_food   = new sf::Texture;
  if (!this->_food->loadFromFile("./Plugins/SFML/image/apple.png"))
    throw Error("food sprite", "init() SFML");
  this->_food->setSmooth(true);

  this->_fond   = new sf::Texture;
  if (!this->_fond->loadFromFile("./Plugins/SFML/image/metal.jpeg"))
    throw Error("image", "init() SFML");
  this->_fond->setSmooth(true);

  this->_fond2   = new sf::Texture;
  if (!this->_fond2->loadFromFile("./Plugins/SFML/image/blank.jpg"))
    throw Error("image", "init() SFML");
  this->_fond2->setSmooth(true);
}

void LibSFML::stop()
{
  if (this->esc == 0)
    this->game_over();
  this->_window->close();
  delete this->_window;
  delete this->_music;
  delete this->_musicPauseOP;
  delete this->_musicPauseCL;
  delete this->_food;
  delete this->_fond;
  delete this->_fond2;
}

EventType LibSFML::waitEvent()
{
  sf::Event event;
  while (this->_window->pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
	{
	  if (this->_event.find(event.key.code) != this->_event.end())
	    {
	      if (event.key.code == sf::Keyboard::Escape ||
		  event.key.code == sf::Keyboard::A ||
		  event.key.code == sf::Keyboard::E)
		this->esc = 1;
	      else if (event.key.code == sf::Keyboard::Space)
		{
		  if (this->_pause == false)
		    {
		      this->_music->pause();
		      this->_musicPauseOP->play();
		      this->_pause = true;
		    }
		  else
		    {
		      this->_musicPauseOP->stop();
		      this->_musicPauseCL->play();
		      this->_music->play();
		      this->_pause = false;
		    }
		}
	      return (this->_event[event.key.code]);
	    }
	}
      if (event.type == sf::Event::Closed)
	return (E_KEY_ESC);
    }
  return (E_NULL);
}

void LibSFML::display(std::vector<char> const &board, GameData const &data)
{
  std::vector<char>::const_iterator	it;
  unsigned int 		       		i = 0;
  int					pos_x = 0;
  int					pos_y = 0;

  this->_pause = data._pause;
  this->draw_menu(data);
  this->draw_back();
  for (i = 0, it = board.begin(); it != board.end(); i++, it++)
    {
      if (pos_x == static_cast<int>(this->SizeX))
	{
	  pos_x = 0;
	  pos_y++;
	}
      if (*it == FOOD)
	draw_food(pos_x, pos_y);
      else if (*it == SNAKE_HEAD)
	draw_square(pos_x, pos_y, 1);
      else if (*it != FREE_SPACE)
	draw_square(pos_x, pos_y, 0);
      pos_x++;
    }
  if (this->_pause == true)
    draw_pause();
  this->_window->display();
  return ;
}

void LibSFML::getNewScoreName(char *dest)
{
  int i = 0;
  sf::Event event;
  this->esc = 1;
  this->draw_back();

  sf::Sprite sprite_fond(*(this->_fond2));
  sprite_fond.setPosition(sf::Vector2f(0, 0));
  sprite_fond.setScale(sf::Vector2f(SIZE_X, SIZE_Y));
  sprite_fond.setColor(sf::Color(255, 255, 255, 60));
  this->_window->draw(sprite_fond);

  sf::Text text;
  sf::Font font;
  font.loadFromFile("./Plugins/SFML/font/MGS2MENU.TTF");
  text.setFont(font);
  text.setColor(sf::Color::Black);
  text.setCharacterSize(60);
  text.setStyle(sf::Text::Bold);
  text.setString("New Record");
  text.setPosition(sf::Vector2f(190, 250));
  this->_window->draw(text);

  text.setCharacterSize(40);
  text.setString("Enter your name");
  text.setPosition(sf::Vector2f(190, 350));
  this->_window->draw(text);

  this->_window->display();

  while (this->_window->waitEvent(event))
    {
      if (event.type == sf::Event::TextEntered)
	{
	  if (i > 511)
	    return ;
	  if (event.text.unicode < 128 && event.text.unicode > 32)
	    dest[i++] = event.text.unicode;
	}
      if (event.key.code == sf::Keyboard::Return)
	{
	  dest[i + 1] = '\0';
	  return ;
	}
    }
	  dest[i + 1] = '\0';
  return ;
}
