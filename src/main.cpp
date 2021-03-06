
#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");

    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler());
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler());
    server.get("/logout", new Logout());

    server.get("/addfilm", new ShowPage("static/addfilm.html"));
    server.get("/showfilm", new ShowFilm());
    server.post("/addfilm", new AddFilmHandler());
    server.get("/buyfilm", new BuyFilmHandler());
    server.get("/deletefilm", new DeleteFilm());
    server.post("/addmoney", new AddMoney());
    server.post("/addcomment", new AddCommentHandler());
    server.post("/ratefilm", new RateFilmHandler());


    server.get("/showuser", new ShowUser());
    server.get("/showprofile", new ShowProfile());
    server.get("/", new HomeHandler());
    server.get("/home", new ShowPage("static/home.html"));
    server.get("/mui.css", new ShowPage("static/mui.css"));
    
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
