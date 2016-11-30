#ifndef ERROR_HPP_
# define ERROR_HPP_

# include "Nibbler.hpp"

class Error : public std::exception
{
  std::string const		_what;
  std::string const		_who;

public:
  Error				() throw() {};
  Error		&operator=	(Error const &) throw() {return (*this);};
  Error				(Error const &) throw() {};
  virtual ~Error		() throw() {};

  Error				(std::string const &wa, std::string const &wo) throw()
    : _what(wa), _who(wo) {};

  virtual const char	*what	(void) const throw()
  {
    return (_what.c_str());
  }
  const char	*	who	(void) const throw()
  {
    return (_who.c_str());
  }
};

#endif /* !ERROR_HPP_ */
