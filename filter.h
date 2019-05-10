
#ifndef FILTER_H
#define FILTER_H

#include "sources.h"
#include "cp_headers.h"
#include "entity_headers.h"

namespace Filter
{
  int find_exact(std::vector<Entity*> container, Component* cp);
  std::vector<int> filter_min(std::vector<Entity*> container, Component* cp);
}

#endif
