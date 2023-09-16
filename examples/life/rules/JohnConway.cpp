#include "JohnConway.h"
#include <iostream>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  Point2D currentLocation = {0, 0};
  int numberOfNeighbours = 0;
  bool isAlive = false;

  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      currentLocation = Point2D(j, i);
      numberOfNeighbours = CountNeighbors(world, currentLocation);
      isAlive = world.Get(currentLocation);

      //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      //Any live cell with two or three live neighbours lives on to the next generation.
      //Any live cell with more than three live neighbours dies, as if by overpopulation.
      //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

      if (isAlive) {  // if alive
        // std::cout << "alive" << std::endl;
        // std::cout << "position: X:" << currentLocation.x << "Y:" << currentLocation.y << "/ neighbours:" << numberOfNeighbours << std::endl;
        //Each cell with one or no neighbors dies, as if by solitude.
        if (numberOfNeighbours < 2) {
          world.SetNext(currentLocation, false);
        }
        // Each cell with two or three neighbors survives.
        else if (numberOfNeighbours == 2 || numberOfNeighbours == 3) {
          world.SetNext(currentLocation, true);
        }
        // Each cell with four or more neighbors dies, as if by overpopulation.
        else if (numberOfNeighbours >= 4) {
          world.SetNext(currentLocation, false);
        }

      }
      else if (!isAlive) {  // if dead
        //std::cout << "position: X:" << currentLocation.x << "Y:" << currentLocation.y << "/ neighbours:" << numberOfNeighbours << std::endl;
        // Each cell with three neighbors becomes populated.
        if (numberOfNeighbours == 3) {
          std::cout << "growing" << std::endl;
          world.SetNext(currentLocation, true);
        }
      }
    }
  }
}


int JohnConway::CountNeighbors(World& world, Point2D point) {

  //TOP LEFT IS 0,0

  int neighbourCount = 0;

  //  Point2D top = point.Up();
  //  Point2D middle = point;
  //  Point2D bottom = point.Down();
  //
  //  top = top.Left();
  //  middle = middle.Left();
  //  bottom = bottom.Left();
  //
  //  for(int i = 0; i <= 1; i++){
  //    top.x + i;
  //    middle.x + i;
  //    bottom.x + i;
  //
  //    if(world.Get(top)){
  //      neighbourCount++;
  //    }
  //    if(world.Get(middle)){
  //      neighbourCount++;
  //    }
  //    if(world.Get(bottom)){
  //      neighbourCount++;
  //    }
  //  }


  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      if(world.Get(Point2D(point.x + j, point.y + i))){
        neighbourCount++;
      }
    }
  }

  //Y X

  //  -1  -1
  //  -1  0
  //  -1  1

  //  0  -1
  //  0  0
  //  0  1

  //  1  -1
  //  1  0
  //  1  1


  neighbourCount--; // don't count itself

  return neighbourCount;
}
