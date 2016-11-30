#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

# include "IDisplayPlugin.hpp"
# include "Error.hpp"

# define SYM				"loading"

class DLLoader
{
  typedef IDisplayPlugin		*(*LoadingF)(void);

  void					*_handler;
  IDisplayPlugin			*_instance;
  std::vector<std::string>		_libDataBase;
  std::vector<std::string>::iterator	_pos;

  DLLoader				(const DLLoader &);
  DLLoader		&operator=	(const DLLoader &);

  void			loadLibDataBase	(void);

  void			cleanHandler	(void);
  void			cleanInstance	(void);

  void			getHandler	(std::string const &);
  LoadingF		getSym		(void);
  IDisplayPlugin	*loadFromPos	(void);

public:
  DLLoader				();
  ~DLLoader				();

  IDisplayPlugin	*getInstance	(std::string const &);
  IDisplayPlugin	*getNextInstance(void);
  IDisplayPlugin	*getPrevInstance(void);

};

#endif /* !DLLOADER_HPP_ */
