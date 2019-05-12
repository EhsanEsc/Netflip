
#include "cp_headers.h"
#include "entity_headers.h"
#include "filter.h"

using namespace std;

Component* build_component(TYPE_NAME tn, string content)
{
  if(tn == TYPE_NAME::USER_NAME)
  {
    Name* cp = new Name(content, tn);
    return cp;
  } else if(tn == TYPE_NAME::AGE) {
    Number* cp = new Number(stoi(content),tn,1,99);
    return cp;
  }
}

vector<Component*> get_component(vector<string> vs)
{
  // farz mikonim valide
  vector<Component*> res;
  for(int i=0;i<vs.size();i+=2)
  {
    res.push_back(build_component(type_name_cache[vs[i]], vs[i+1]));
  }
  return res;
}

int main()
{
  freopen("in.txt","r",stdin);

  vector<User*>users;
  while(true)
  {
    try {
      string str;
      cin >> str;
      vector<Entity*> et;
      for(auto& u:users)
      {
        et.push_back(dynamic_cast<Entity*>(u));
      }
      if(str == "end") break;
      if(str == "add")
      {
        string str1,str2,str3,str4;
        cin >> str1 >> str2 >> str3 >> str4;
        vector<string> vs = {str1,str2,str3,str4};
        vector<Component*> comps = get_component(vs);
        User* new_user = new User(comps);
        users.push_back(new_user);
      } else if(str == "show") {
        string str1,str2;
        cin >> str1 >> str2;
        Component* cp = build_component(type_name_cache[str1],str2);
        User* guser = Filter_interface::find_exact(users,cp);
        // User* guser = users[0];
        if(guser==NULL)
          cout << "User Not Found" << endl;
        else
          guser->show();
        delete cp;
      } else if(str == "showmin") {
        string str1,str2;
        cin >> str1 >> str2;
        Component* cp = build_component(type_name_cache[str1],str2);
        vector<User*> glist = Filter_interface::filter_min(users,cp);
        cout << "##" << endl;
        for(auto& g:glist)
          g->show();
        cout << "##" << endl;
        delete cp;
      }
    } catch(Error& err) {
      cerr << "ERROR: " << err.what() << endl;
    }
  }
  return 0;
}
