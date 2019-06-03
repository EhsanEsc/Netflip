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
  if(req->getBodyParam("is_publisher") == "is_pub")
    input += "publisher true ";

  handler->run_command(input);
  cout << "Successfully Signup!" << endl;

  Response *res = Response::redirect("/showuser");
  string sess = req->getBodyParam("username");
  if(req->getBodyParam("is_publisher") == "is_pub")
    sess += "1";
  else
    sess += "0";
  res->setSessionId(sess);
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

Response *AddMoney::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST money ? ";
  input += "amount " + req->getBodyParam("amount") + " ";

  handler->run_command(input);
  cout << "Successfully Added Money!" << endl;

  Response *res = Response::redirect("/showprofile");
  return res;
}

Response *DeleteFilm::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST delete_films ? ";
  input += "film_id " + req->getQueryParam("film_id") + " ";

  handler->run_command(input);
  cout << "Successfully Delete Film!" << endl;

  Response *res = Response::redirect("/showuser");
  return res;
}

Response *ShowFilm::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "GET films ? film_id " + req->getQueryParam("film_id");
  Respond rr = handler->run_command(input);

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>NetFlip Film Page!</h1>";
  body += "<p>";
  body += "</p>";
  body += "<p>";
  body += "<a href=\"/logout\">Logout!!!</a><br>";

  for(auto s:rr)
    body += s + "<br>";

  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowUser::callback(Request *req) {
  if(req->getSessionId().back() == '1')
  {
    Response *res = Response::redirect("/showpub");
    return res;
  }

  CommandHandler* handler = CommandHandler::get_instance();

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>NetFlip User Page!</h1>";
  body += "<p>";
  body += "</p>";
  body += "<p>";
  body += "<a href=\"/logout\">Logout!!!</a><br>";
  body += "<a href=\"/showprofile\">Profile!!!</a><br>";

  string input = "GET films";
  Respond rr = handler->run_command(input);
  for(auto s: rr)
  {
    if(s[0] == '#')
    {
      body += s + "<br>";
      continue;
    }

    string film_id;
    for(int i=3; i <s.size() ; i++)
    {
      if(s[i] == '|')
        break;
      film_id += s[i];
    }

    body += "<a href=\"/showfilm?film_id=" + film_id + "\">";
    body += s ;
    body += "</a>";
  }

  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowProfile::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>NetFlip Profile Page!</h1>";
  body += "<p>";
  body += "</p>";
  body += "<p>";
  body += "<a href=\"/logout\">Logout!!!</a><br>";

  body += "<form action=\"/addmoney\" method=\"post\"> ";
  body += "<input name=\"amount\" type=\"text\" placeholder=\"Your money\" /><br>";
  body += "<button type=\"submit\">addMoney</button>";
  body += "</form><br><br>";

  string input = "GET purchased";
  Respond rr = handler->run_command(input);
  for(auto s: rr)
  {
    if(s[0] == '#')
    {
      body += s + "<br>";
      continue;
    }

    string film_id;
    for(int i=3; i <s.size() ; i++)
    {
      if(s[i] == '|')
        break;
      film_id += s[i];
    }

    body += "<a href=\"/showfilm?film_id=" + film_id + "\">";
    body += s ;
    body += "</a>";
  }

  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowPub::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>NetFlip Publisher Page!</h1>";
  body += "<p>";
  body += "</p>";
  body += "<p>";
  body += "<a href=\"/logout\">Logout!!!</a><br>";
  body += "<a href=\"/showprofile\">Profile!!!</a><br>";
  body += "<a href=\"/addfilm\">ADDFILM!!!</a><br><br><br>";

  string input = "GET published";
  Respond rr = handler->run_command(input);
  for(auto s: rr)
  {
    if(s[0] == '#')
    {
      body += s + "<br>";
      continue;
    }

    string film_id;
    for(int i=3; i <s.size() ; i++)
    {
      if(s[i] == '|')
        break;
      film_id += s[i];
    }

    body += "<a href=\"/showfilm?film_id=" + film_id + "\">";
    body += s ;
    body += "</a>";

    cout << "!@# " << film_id << endl;
    
    body += "  <a href=\"/deletefilm?film_id=" + film_id + "\"> @delete@ </a>";
    body += "<br>";
  }

  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
