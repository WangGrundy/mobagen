#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::vector, std::unordered_set, std::unordered_map;

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  vector<Point2D> generatePath(World* w);
  vector<Point2D> getVisitableNeightbors(World* world, Point2D current, Point2D catPosition, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierSet);
  Point2D getRandomTileNextToCat(World* world);
  Point2D randomTileInWorld(World* world, int side);
};

#endif  // AGENT_H
