#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <vector>

class Cat : public Agent {
public:
  explicit Cat() : Agent(){};
  Point2D Move(World*) override;

  std::vector<Point2D> GetVisitableNeighbours(World* world, const Point2D& catPos);
};

#endif  // CAT_H
