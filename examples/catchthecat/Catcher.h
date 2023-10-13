#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"
#include "map"
#include "queue"

using std::map;
using std::vector;
using std::queue;

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
protected:
  void CreateMapForOuterTiles(const int& side, queue<Point2D>& outerQueue, bool& finishedFirstRun);
  Point2D GetCatPredictedMove_CatcherVersion(World* world);
private:
  map<int,map<int, bool>> outerTilesAvailible; //visited nodes
  queue<Point2D> outerQueue;
  bool finishedFirstRun = false;

  map<int,map<int, bool>> visited; //visited nodes
  queue<Point2D> frontier; //nodes we about to visit
  map<int, map<int, Point2D>> cameFrom; //left = came from, right point
  bool foundExit = false;


};

#endif  // CATCHER_H
