//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
#include <iostream>
void HexagonGameOfLife::Step(World& world) {
<<<<<<< HEAD
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
        // Only the cells with two neighbors survives.
        else if (numberOfNeighbours == 2) {
          world.SetNext(currentLocation, true);
        }
        // Each cell with three or more neighbors dies from overpopulation.
        else if (numberOfNeighbours >= 3) {
          world.SetNext(currentLocation, false);
        }

      }
      else if (!isAlive) {  // if dead
        // Each cell with two neighbors revives.
        if (numberOfNeighbours == 2) {
          world.SetNext(currentLocation, true);
        }
      }
    }
  }
=======
  for (int y = 0; y < world.SideSize(); ++y) {
    for (int x = 0; x < world.SideSize(); ++x)
    {
      int neighbors = CountNeighbors(world,Point2D(x,y));
      if (neighbors==2)//(neighbors==2&&world.Get(Point2D(x,y)))||
      {
        world.SetNext(Point2D(x,y), true);
      }
      else
      {
        world.SetNext(Point2D(x,y), false);
      }
    }
  }

  world.SwapBuffers();
>>>>>>> 5ab9f641f4135fb85f22f4eee32ead9a03f0f51a
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
<<<<<<< HEAD

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

    //    Top Row = B.Top+Left, B.Top
    //    Middle Row = B.Left, B.right
    //    Bottom row = B.Bottom.Left, B.Bottom

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
  else{// ODD ROW
    //    Top row = B.Top , B.Top+Right
       //     Middle row = B.Left, B.Right
       //      Bottom row: B.Bottom, B.Bottom+Right

       if(world.Get(point.Up())){ //middle = right hand side
         neighbourCount++;
       }
       if(world.Get(point.Up().Right())){
         neighbourCount++;
       }

       if(world.Get(point.Down())){
         neighbourCount++;
       }
       if(world.Get(point.Down().Right())){
         neighbourCount++;
       }
  }

  return neighbourCount;
}
=======
  int count;
//assume 1,1
  bool shift =point.y%2!=0;
  if (shift){//assume 1,1
    count= world.Get(point.Up())+//1,0
           world.Get(point.Right().Up())+//2,0
           world.Get(point.Right())+//2,1
           world.Get(point.Right().Down())+//2,2
           world.Get(point.Down())+//1,2
           world.Get(point.Left());//0,1


  }
  else{//assume 2,2
    count = world.Get(point.Up().Left())+//1,1
           world.Get(point.Up())+//2,1
           world.Get(point.Right())+//3,2
           world.Get(point.Down())+//2,3
           world.Get(point.Down().Left())+//1,3
           world.Get(point.Left());//1,2
  }

  return count;


}
>>>>>>> 5ab9f641f4135fb85f22f4eee32ead9a03f0f51a
