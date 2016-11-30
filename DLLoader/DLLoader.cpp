#include <iostream>
#include <string>
#include <dlfcn.h>
#include "DLLoader.hpp"

//
// CTOR DTOR
//

DLLoader::DLLoader		()
  : _handler(NULL), _instance(NULL)
{
  this->loadLibDataBase();
  this->_pos = _libDataBase.begin();
}

DLLoader::DLLoader		(const DLLoader &)
{
}

DLLoader			&DLLoader::operator=(const DLLoader &)
{
  return (*this);
}

DLLoader::~DLLoader		()
{
  this->cleanInstance();
  this->cleanHandler();
}

//
// DATABSE
//

void				DLLoader::loadLibDataBase(void)
{
  std::ifstream			file(".lib");
  char				line[BUFF_SIZE];

  if (file.fail() || file.bad())
    throw Error("Unable To Load Plugins DataBase", "DLLOADER");
  while (file.getline(line, BUFF_SIZE))
    this->_libDataBase.push_back(line);
  file.close();
}

//
// CLEANING
//

void				DLLoader::cleanHandler(void)
{
  if (this->_handler)
    {
      if (dlclose(this->_handler) != 0)
	throw Error(dlerror(), "DLLoader");
    }
  this->_handler = NULL;
}

void				DLLoader::cleanInstance(void)
{
  if (this->_instance)
    delete (this->_instance);
  this->_instance = NULL;
}

//
// DL GETTERS
//

void				DLLoader::getHandler(std::string const &lib_name)
{
  this->_handler = dlopen(lib_name.c_str(), RTLD_LAZY);
  if (this->_handler == NULL)
    throw Error(dlerror(), "DLLoader");
}

DLLoader::LoadingF		DLLoader::getSym(void)
{
  DLLoader::LoadingF		loading_f;
  char				*error;

  dlerror();
  *(void **) (&loading_f) = dlsym(this->_handler, SYM);
  error = dlerror();
  if (error)
    throw Error(error, "DLLoader");
  return (loading_f);
}

//
// LOADER
//

IDisplayPlugin				*DLLoader::loadFromPos(void)
{
  DLLoader::LoadingF			loading_f;
  std::string				lib_name;

  lib_name = *(this->_pos);
  this->cleanHandler();
  this->getHandler(lib_name);
  loading_f = this->getSym();
  this->cleanInstance();
  this->_instance = (*loading_f)();
  return (this->_instance);
}

IDisplayPlugin				*DLLoader::getInstance(std::string const &name)
{
  std::vector<std::string>::iterator	it;
  std::string				lib_name("./");

  lib_name += name;
  it = std::find(_libDataBase.begin(), _libDataBase.end(), lib_name);
  if (it == _libDataBase.end())
    {
      std::cerr << name << " Is Not In Plugin Data Base" << std::endl;
      return (NULL);
    }
  this->_pos = it;
  return (this->loadFromPos());
}

IDisplayPlugin				*DLLoader::getNextInstance(void)
{
  this->cleanInstance();
  this->cleanHandler();
  ++(this->_pos);
  if (this->_pos == this->_libDataBase.end())
    this->_pos = this->_libDataBase.begin();
  return (this->loadFromPos());
}

IDisplayPlugin				*DLLoader::getPrevInstance(void)
{
  this->cleanInstance();
  this->cleanHandler();
  if (this->_pos == this->_libDataBase.begin())
    {
      this->_pos = this->_libDataBase.end();
      --(this->_pos);
    }
  else
    --(this->_pos);
  return (this->loadFromPos());
}
