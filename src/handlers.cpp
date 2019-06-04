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

Response *BuyFilmHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST buy ? film_id " + req->getQueryParam("film_id");

  handler->run_command(input);
  cout << "Successfully Film Bought!" << endl;

  Response *res = Response::redirect("/showuser");
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

Response *AddCommentHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST comments ? ";
  input += "film_id " + req->getBodyParam("film_id") + " ";
  input += "content " + req->getBodyParam("comment_text") + " ";

  cout << "$$$ " << input << endl;

  handler->run_command(input);
  cout << "Successfully Added comment!" << endl;

  Response *res = Response::redirect("/showfilm?film_id="
  + req->getBodyParam("film_id"));
  return res;
}

Response *RateFilmHandler::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  string input = "POST rate ? ";
  input += "film_id " + req->getBodyParam("film_id") + " ";
  input += "score " + req->getBodyParam("score") + " ";

  cout << "### " << input << endl;

  handler->run_command(input);
  cout << "Successfully Rated!" << endl;

  Response *res = Response::redirect("/showfilm?film_id="
  + req->getBodyParam("film_id"));
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
  body += "<br><br>";

  body += "<a href=\"/buyfilm?film_id=" + req->getQueryParam("film_id") + "\">Buy Film!!!</a><br><br>";
  
  body += "<form action=\"/addcomment\" method=\"post\">";
  body += "<p>Add Comment</p><br>";
  body += "<input name=\"comment_text\" type=\"text\" placeholder=\"Write your comment...\"/>";
  body += "<input name=\"film_id\" type=\"hidden\" value=\"" +
    req->getQueryParam("film_id") + "\"/>";
  body += "<button type=\"submit\">Add Comment</button>";
  body += "</form><br>";

  body += "<form action=\"/ratefilm\" method=\"post\">";
  body += "<p>Rate film </p>";
  body += "<input name=\"score\" type=\"text\" placeholder=\"Rate this film...\"/>";
  body += "<input name=\"film_id\" type=\"hidden\" value=\"" +
    req->getQueryParam("film_id") + "\"/>";
  body += "<button type=\"submit\">Rate!</button>";
  body += "</form>";

  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowUser::callback(Request *req) {
  bool is_pub = (req->getSessionId().back() == '1');
  CommandHandler* handler = CommandHandler::get_instance();
  string director_name = req->getQueryParam("director_name");

  cout << "**** " << director_name << endl;

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
  if(is_pub)
    body += "<a href=\"/addfilm\">ADDFILM!!!</a><br><br><br>";

  body += "<br><form action=\"/showuser\" method=\"get\">";
  body += "<p>Filter films by Director Name</p>";
  body += "<input name=\"director_name\" type=\"text\" placeholder=\"Write Director Name...\"/>";
  body += "<button type=\"submit\">Filter!</button>";
  body += "</form><br><br><br>";

  string input;
  if(is_pub)
    input = "GET published"; 
  else
    input = "GET films";

  if(director_name != "")
    input += " ? director " + director_name;

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
    if(is_pub)
      body += "<a href=\"/deletefilm?film_id=" + film_id + "\"> @delete@ </a>";

    body += "<br>";
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