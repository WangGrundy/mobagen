#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using std::queue;
using std::map;
using std::vector;
using std::unordered_set;

class Cat : public Agent {
public:
  explicit Cat() : Agent(){};
  Point2D Move(World*) override;
protected:
private:
};

#endif  // CAT_H
