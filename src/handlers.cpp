#include "handlers.hpp"
#include "command_handler.h"
#include <sstream>
using namespace std;

string build_header()
{
 stringstream body;
 body << "<!DOCTYPE html>"
 << "<html><head><link href=\"mui.css\" rel=\"stylesheet\" type=\"text/css\" />"
 << "</head><body>"
 <<   "<div class=\"mui-appbar\"><table width=\"100%\">"
 <<       "<tr style=\"vertical-align:middle;\"><td class=\"mui--appbar-height\">"
 <<   "<a href=\"/\">  <button class=\"mui-btn mui-btn--danger\">Home</button> </a>"
 <<   "<a href=\"/showprofile\">  <button class=\"mui-btn mui-btn--danger\">Profile</button> </a>"
 <<    "</td><td class=\"mui--appbar-height\" align=\"right\">"
 <<      "<a href=\"/logout\">  <button class=\"mui-btn mui-btn--danger\">Logout</button> </a>"
  <<       " </td></tr></table></div> "; 
  return body.str();
}

string find_film_id(string str)
{
  string film_id;
  for(int i=3; i <str.size() ; i++) 
  {
    if(str[i] == '|')
      break;
    film_id += str[i];
  }
  return film_id;
}

string build_table(vector<string> rr)
{
  string body;
  body += "<table class=\"mui-table mui-table--bordered\"  style=\"width:70%;\">";
  body +=  "<thead><tr>";
  int st=0,en;
  for(;st<rr[0].size();st++)
  {
    if(rr[0][st] == ' ' || rr[0][st] == '|')
      continue;
    en=st;
    while( !(rr[0][en] == '|') ) { en++; }
    body += "<th>" + rr[0].substr(st,en-st) + "</th>";
    st=en;
  }
  body += " </tr></thead>";
  body += " <tbody>";

  for(int j=1 ; j<rr.size() ; j++)
  {
    body += "<tr>";
    string s = rr[j];

    string film_id = find_film_id(s);

    body += "<td><a href=\"/showfilm?film_id=" + film_id + "\">";
    body += "";
    for(int i=0;i<s.size();i++)
    {
      if(s[i] == '.')
      {
        body += "</a></td><td>";
        continue;
      }
      if(s[i] == '|')
        body += "</td><td>";
      else
        body += s[i];
    }
    body += "</td>";

    body += "</tr>";
  }
  body += "</tbody>";
  body += "</table>";
  body += "<br><br>";
  return body;
}

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

Response *HomeHandler::callback(Request *req) {
  Response *res;
  cout << req->getSessionId() << endl;
  if(req->getSessionId().size())
    res = Response::redirect("/showuser");
  else
    res = Response::redirect("/home");
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
  string body = build_header();
  body += "<center><br><br><div class=\"mui--text-body2\"";
  body += "<br><br><p class=\"mui--text-display1\">" + string("Film Details!") + "</p><br>";

  vector<string> films;
  for(auto s:rr)
  {
    if(s[0] == '#')
      films.clear();
    if(s != "")
      films.push_back(s);
  }
  for(auto s:rr)
  {    
    if(s[0] == '#')
      break;
    body += s + "<br>";
  }
  films[0][2]='|';
  body += build_table(films);

  body += "<br><br>";

  body += "<a href=\"/buyfilm?film_id=" + req->getQueryParam("film_id") + 
    "\">" + "<button class=\"mui-btn mui-btn--danger\">" +"Buy Film</button></a><br><br>";

  body += "<form action=\"/addcomment\" method=\"post\">";
  body += "<input name=\"comment_text\" type=\"text\" placeholder=\"Write your comment...\"/>";
  body += "<input name=\"film_id\" type=\"hidden\" value=\"" +
    req->getQueryParam("film_id") + "\"/>";
  body += "<button type=\"submit\">Add Comment</button>";
  body += "</form><br>";

  body += "<form action=\"/ratefilm\" method=\"post\">";
  body += "<input name=\"score\" type=\"text\" placeholder=\"Rate this film...\"/>";
  body += "<input name=\"film_id\" type=\"hidden\" value=\"" +
    req->getQueryParam("film_id") + "\"/>";
  body += "<button type=\"submit\">Rate!</button>";
  body += "</form>";

  body += "</div>";
  body += "</p>";
  body += "</center>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowUser::callback(Request *req) {
  bool is_pub = (req->getSessionId().back() == '1');
  CommandHandler* handler = CommandHandler::get_instance();
  string director_name = req->getQueryParam("director_name");

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body = build_header();
  body += "<br><div class=\"mui--text-display3\" style=\"text-align:center;\">NetFlip User Page!</div>";
  body += "<center>";
  body += "<br><br>";

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
  rr[0][2] = '|';
  if(is_pub)
  { 
    rr[0] += " | delete";
    for(int i=1;i<rr.size();i++)
      rr[i] += " | <a href=\"/deletefilm?film_id=" + find_film_id(rr[i]) + "\"> delete </a>";
  }

  body += "<div class=\"mui--text-display1\">" +
    (is_pub==true ? string("Published films!") : string("All films!")) + "</div>";
  body += build_table(rr);

  if(is_pub)
  { 
    body += "<a href=\"/addfilm\" ><button class=\"mui-btn mui-btn--danger\">";
    body += "Add new film</button> </a>";
  }
  body += "</center>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowProfile::callback(Request *req) {
  CommandHandler* handler = CommandHandler::get_instance();

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body = build_header();
  body += "<center>";

  body += "<br><br>";
  body += "<form action=\"/addmoney\" method=\"post\"> ";
  body += "<input name=\"amount\" type=\"text\" placeholder=\"Your money\" />";
  body += "<button type=\"submit\">addMoney</button>";
  body += "</form><br><br>";

  body += "<div class=\"mui--text-display1\"> Purchased films </div>";
  string input = "GET purchased";
  Respond rr = handler->run_command(input);
  rr[0][2]='|';
  body += build_table(rr);

  body += "</p>";
  body += "</center>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
