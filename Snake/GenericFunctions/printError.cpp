//
// print_error.cpp for Nibbler in /home/lks/rendu/cpp_nibbler/auzou_t
// 
// Made by Thibaud Auzou
// Login   <auzou_t@epitech.net>
// 
// Started on  Tue Mar 24 18:30:21 2015 Thibaud Auzou
// Last update Tue Mar 24 18:39:46 2015 Thibaud Auzou
//

#include "Nibbler.hpp"

int		printError(std::string const &error)
{
  std::cerr << error << std::endl;
  return (ERROR);
}
