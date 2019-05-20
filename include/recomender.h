
#ifndef RECOMENDER_H
#define RECOMENDER_H

#include<map>
#include<vector>

constexpr int MAX_CNT_NODES = 1e3+22;

class Recomender
{
public:
  Recomender();
  static Recomender* get_instance();
  void add_node(int new_uid);
  void delete_node(int uid);
  void add_weight(int node_uid, std::vector<int> related_nodes_uid);
  std::vector<int> get_recomend_ids(int uid, std::vector<int> restricted_noeds_uid);
private:
  static Recomender* instance;
  int G[MAX_CNT_NODES][MAX_CNT_NODES];
  std::vector<int> available_ids;

  std::map<int,int> id_cache;
  int to_id(int user_id);
  int get_new_id();
  int last_id = 0;
};

#endif
