##
## Makefile for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
## 
## Made by Thibaud Auzou
## Login   <auzou_t@epitech.net>
## 
## Started on  Tue Mar 24 18:23:36 2015 Thibaud Auzou
## Last update Sun Apr  5 17:34:09 2015 Thibaud Auzou
##

CC		= g++

RM		= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror
CXXFLAGS	+= -I./include/ -I../include/
CXXFLAGS	+=

LDFLAGS		= -ldl

NAME		= nibbler

SRCS		= main.cpp \
		  GenericFunctions/printError.cpp \
		  Board/Board.cpp \
		  Food/Food.cpp \
		  Snake/Snake.cpp \
		  Snake/Event.cpp \
		  Snake/Link.cpp \
		  DLLoader/DLLoader.cpp \

OBJS		= $(SRCS:.cpp=.o)

GRAPHIC_CLEAN	= make clean -C Plugins/
GRAPHIC_FCLEAN	= make fclean -C Plugins/
GRAPHIC_RE	= make re -C Plugins/


all: $(NAME) graphic_libs

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

graphic_libs:
	make -C Plugins/ > /dev/null

clean:
		$(RM) $(OBJS)
		$(GRAPHIC_CLEAN) > /dev/null

fclean: clean
		$(RM) $(NAME)
		$(GRAPHIC_FCLEAN) > /dev/null

re: fclean all

.PHONY: all clean fclean re
