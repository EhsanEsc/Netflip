
#include "recomender.h"
#include<algorithm>
using namespace std;

<<<<<<< HEAD
constexpr int MAX_RECOMENDATION_SIZE = 4;
=======
constexpr MAX_RECOMENDATION_SIZE = 4;
>>>>>>> 97cb0f4f16c46e0a149b9f1163365a302604c766

Recomender::Recomender()
{
  last_id = 0;
  for(int i=0;i<MAX_CNT_NODES;i++)
    for(int j=0;j<MAX_CNT_NODES;j++)
      G[i][j]=0;
}

Recomender* Recomender::instance = NULL;
Recomender* Recomender::get_instance()
{
  if(instance == NULL)
    instance = new Recomender();
  return instance;
}

void Recomender::add_node(int new_uid)
{
  if(to_id(new_uid) != -1) return;
  id_cache[new_uid] = get_new_id();
  available_ids.push_back(id_cache[new_uid]);
}

void Recomender::delete_node(int uid)
{
  if(to_id(uid) == -1) return;
  int id = to_id(uid);
  for(int i=0 ; i<int(available_ids.size()) ; i++)
  {
    if(available_ids[i] == id)
    {
      available_ids.erase(available_ids.begin() + i);
      return;
    }
  }
}

void Recomender::add_weight(int node_uid, std::vector<int> related_nodes_uid)
{
  int id = to_id(node_uid);
  if(id == -1) return;
  vector<int> vid;
  for(auto& u:related_nodes_uid)
  {
    if(to_id(u) == -1) return;
    vid.push_back(to_id(u));
  }

  for(auto& u:vid)
    G[u][id]++,G[id][u]++;
}

std::vector<int> Recomender::get_recomend_ids(int uid, std::vector<int> restricted_noeds_uid)
{
  int id = to_id(uid);
  if(id == -1) return vector<int>();
  vector<int> bad_ids;
  for(auto& u: restricted_noeds_uid)
  {
    if(to_id(u) == -1) return vector<int>();
    bad_ids.push_back(to_id(u));
  }
  bad_ids.push_back(id);

  vector<pair<int,int>> vec;
  for(auto& u: available_ids)
    vec.push_back({G[id][u],-u});
  sort(vec.begin(),vec.end());
  reverse(vec.begin(),vec.end());

  vector<int> res;
  for(auto& u:vec)
    if(find(bad_ids.begin(),bad_ids.end(),-u.second) == bad_ids.end())
      res.push_back(-u.second);

  if(res.size()>MAX_RECOMENDATION_SIZE)
    res.resize(MAX_RECOMENDATION_SIZE);
  return res;
}

int Recomender::to_id(int user_id)
{
  if(id_cache.find(user_id) == id_cache.end())
    return -1;
  return id_cache[user_id];
}

int Recomender::get_new_id()
{
  last_id++;
  return last_id;
}
