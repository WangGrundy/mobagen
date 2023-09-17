//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
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
        //Each cell with one or no neighbors dies, as if by solitude.
        if (numberOfNeighbours <= 1) {
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
        // Each cell with three neighbors becomes populated.
        if (numberOfNeighbours == 3) {
          world.SetNext(currentLocation, true);
        }
      }
    }
  }
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {

  int neighbourCount = 0;

  //Check Left and right of initial point regardless of even or odd row.
  //Middle Row = B.Left, B.right
  if(world.Get(point.Left())){
    neighbourCount++;
  }
  if(world.Get(point.Right())){
    neighbourCount++;
  }

//B = initial block
  if((point.y % 2) == 0){ // EVEN ROW
    //IF ON ODD ROW, IT WILL ALWAYS BE RIGHT
//    Top Row = B.Top+Left, B.Top (MIDDLE = RIGHT)
//    Bottom row = B.Bottom.Left, B.Bottom

    if(world.Get(point.Up().Right())){
      neighbourCount++;
    }
    if(world.Get(point.Up())){ //middle = right hand side
      neighbourCount++;
    }

    if(world.Get(point.Down())){
      neighbourCount++;
    }
    if(world.Get(point.Down().Right())){
      neighbourCount++;
    }

  }
  else{// ODD ROW

    //IF ON ODD ROW, IT WILL ALWAYS BE RIGHT
    //    Top row = B.Top , B.Top+Right (MIDDLE = LEFT)
    //    Bottom row: B.Bottom, B.Bottom+Right
    

    if(world.Get(point.Up().Left())){
      neighbourCount++;
    }
    if(world.Get(point.Up())){ //middle = right hand side
      neighbourCount++;
    }

    if(world.Get(point.Down().Left())){
      neighbourCount++;
    }
    if(world.Get(point.Down())){
      neighbourCount++;
    }
  }

  return neighbourCount;
}
