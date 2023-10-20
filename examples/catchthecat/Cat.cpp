#include "Cat.h"
#include "World.h"

Point2D Cat::Move(World* world) {
  vector<Point2D> path = generatePath(world);

  if(path.empty()){
    Point2D randomTile = getRandomTileNextToCat(world);
    return randomTile;
  }

  return {path[path.size()-1]};
}