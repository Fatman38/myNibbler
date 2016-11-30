##
## Makefile for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
## 
## Made by Thibaud Auzou
## Login   <auzou_t@epitech.net>
## 
## Started on  Tue Mar 24 18:23:36 2015 Thibaud Auzou
## Last update Sun Nov 20 23:51:41 2016 Fatman
##

CC		= g++

RM		= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I./include/ -I../include/ -I../../include/
CXXFLAGS	+= -fPIC -shared
CXXFLAGS	+= -D SFML_NO_DEPRECATED_WARNINGS

LDFLAGS		= -I/usr/local/include -L/usr/local/lib


NCURSES		= lib_nibbler_ncurses.so
NCURSES_SRC	= NCURSES/LibNcurses.cpp
NCURSES_OBJ	= $(NCURSES_SRC:.cpp=.o)


SFML		= lib_nibbler_sfml.so
SFML_SRC	= SFML/LibSFML.cpp \
		  SFML/snake_public.cpp \
		  SFML/snake_draw.cpp \
		  SFML/snake_other.cpp
SFML_OBJ	= $(SFML_SRC:.cpp=.o)


OPENGL		= lib_nibbler_opengl.so
OPENGL_SRC	= OPENGL/LibOpengl.cpp
OPENGL_OBJ	= $(OPENGL_SRC:.cpp=.o)


all: $(NCURSES) $(SFML) $(OPENGL)

$(NCURSES): $(NCURSES_OBJ)
		$(CC) $(NCURSES_OBJ) -fPIC -shared -o $(NCURSES) -lncurses

$(SFML): $(SFML_OBJ)
		$(CC) $(SFML_OBJ) -fPIC -shared -o $(SFML) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(OPENGL): $(OPENGL_OBJ)
		$(CC) $(OPENGL_OBJ) -fPIC -shared -o $(OPENGL) $(LDFLAGS) -lGL -lGLU -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

clean:
		$(RM) $(NCURSES_OBJ) $(SFML_OBJ) $(OPENGL_OBJ)

fclean: clean
		$(RM) $(NCURSES) $(SFML) $(OPENGL)

re: fclean all

.PHONY: all clean fclean re
