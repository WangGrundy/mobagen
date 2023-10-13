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
  std::vector<Point2D> GetVisitableNeighbours(World* world, const Point2D& catPos);

protected:
  Point2D ReturnIfNoPathToWin(Point2D currentPosition, queue<Point2D>& frontier);
  Point2D FindHead(Point2D catPosition, Point2D& currentTile, map<int, map<int, Point2D>>& cameFrom);
  void GetAllVisitableNeighboursAndPushOnFrontier(Point2D catPosition, Point2D currentTile, World* world);

private:
  map<int,map<int, bool>> visited; //visited nodes
  queue<Point2D> frontier; //nodes we about to visit
  map<int, map<int, Point2D>> cameFrom; // curr point, From
  unordered_set<Point2D> frontierSet; //new
  bool foundExit = false;
};

#endif  // CAT_H
