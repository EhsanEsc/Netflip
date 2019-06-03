#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class Logout : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowUser : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowPub : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowProfile : public RequestHandler {
public:
  Response *callback(Request *);
};

class AddMoney : public RequestHandler {
public:
  Response *callback(Request *);
};

class AddFilmHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class DeleteFilm : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowFilm : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
