#include "handlers.hpp"
#include "command_handler.h"
using namespace std;

Response *LoginHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST login ? ";
  input += "username " + req->getBodyParam("username") + " ";
  input += "password " + req->getBodyParam("password") + " ";

  handler->run_command(input);
  cout << "Successfully login!" << endl;

  Response *res = Response::redirect("/showuser");
  res->setSessionId(req->getBodyParam("username"));
  return res;
}

Response *SignupHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST signup ? ";
  input += "username " + req->getBodyParam("username") + " ";
  input += "password " + req->getBodyParam("password") + " ";
  input += "age " + req->getBodyParam("age") + " ";
  input += "email " + req->getBodyParam("email") + " ";
  if(req->getBodyParam("is_publisher") == "on") //*
    input += "publisher true ";

  handler->run_command(input);
  cout << "Successfully Signup!" << endl;

  Response *res = Response::redirect("/showuser");
  res->setSessionId(req->getBodyParam("username"));
  return res;
}

Response *Logout::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST logout ";

  handler->run_command(input);
  cout << "Successfully Logout!" << endl;

  Response *res = Response::redirect("/");
  res->setSessionId("");
  return res;
}

Response *AddFilmHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST films ? ";
  input += "name " + req->getBodyParam("name") + " ";
  input += "year " + req->getBodyParam("year") + " ";
  input += "length " + req->getBodyParam("length") + " ";
  input += "price " + req->getBodyParam("price") + " ";
  input += "summary " + req->getBodyParam("summary") + " ";
  input += "director " + req->getBodyParam("director") + " ";

  handler->run_command(input);
  cout << "Successfully Added Film!" << endl;

  Response *res = Response::redirect("/showuser");
  return res;
}

Response *ShowUser::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "</p>";
  body += req->getSessionId();
  body += "<p>";
  body += "<a href=\"/logout\">Logout!!!</a>";
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
