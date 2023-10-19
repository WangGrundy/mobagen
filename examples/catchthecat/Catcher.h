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
private:
  map<int,map<int, bool>> outerTilesAvailible; //visited nodes
  queue<Point2D> outerQueue;
  bool finishedFirstRun = false;
};

#endif  // CATCHER_H
