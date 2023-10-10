#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <queue>
#include <map>
#include <vector>

using std::queue;
using std::map;
using std::vector;

map<int,map<int, bool>> visited; //visited nodes
queue<Point2D> frontier; //nodes we about to visit
map<int, Point2D> cameFrom; //left = came from, right point

Point2D convertFromLinear(int linearPosition, World world);

Point2D Cat::Move(World* world) {

//  1. add all the neighbors to the frontier, then start the loop
//  2. Then take from the frontier, add it to the visited, add all its available neighbors to the frontier

  visited.clear();
  frontier = queue<Point2D>();
  cameFrom.clear();

  //get current position of cat
  Point2D catPosition = world->getCat();
  //cat position
  frontier.push(catPosition);

  //current position
  Point2D currentPosition = catPosition;

  //keep repeating this until frontier is empty
  while(!frontier.empty()){

    //choose next point:
    Point2D next = frontier.front();

    //frontier pop the current position/ consume current position
    frontier.pop(); //current position

    //get all neighbours
    vector<Point2D> neighboursVisitable = world->neighbors(currentPosition);

    //if cat wins on this tile:
    if(world->catWinsOnSpace(currentPosition)){
      break;
    }

    //is cat blocked off?
    for(int i = 0; i <  neighboursVisitable.size() - 1; i++){

      //only add to frontier if cat is able to move onto tile
      if(world->catCanMoveToPosition(neighboursVisitable[i]) && !visited[currentPosition.x][currentPosition.y]){
        //adds all neighbours to frontier
        frontier.push(neighboursVisitable[i]);
      }
    }

    //visit the next element in queue.
    visited[next.x][next.y] = true;

    //for every element, check neighbourhood and store came_from
    cameFrom.insert({world->getWorldSideSize() * currentPosition.y + currentPosition.x, next});

    currentPosition = next;
  }

  //convert from tail to head... but which tail do I use?

  //convert between linear to Point2D = x,y
  //int x =

  //convertFromLinear(currentPosition, world);

  //for(int i = 0; i < )

  return convertFromLinear(world->getWorldSideSize() * currentPosition.y + currentPosition.x, *world);
}

//The rules of my algorithm for the cat will be:
//Cat will find path to nearest square to move to the closest exit
//if cat finds multiple exits worth the same, then choose 1 randomly
//cat will continue to do this until it has 0 possible squares to go to

//BFS
//Pick and remove a location from the frontier.Expand it by looking at its neighbors.
// Skip walls. Any unreached neighbors we add to both the frontier and the reached set

////this function should add all countable neighbours into the vector and return that
//vector<Point2D> Cat::GetVisitableNeighbours(World* world, const Point2D& catPos){
//
//  //Check all sides of the cat tile:
//
//  if(world->neighbors())
//
//  world->getContent(Point2D(0,0)); //checks for blocked tiles
//
//
//
//}


//switch (rand) {
//  case 0:
//    return World::NE(pos);
//  case 1:
//    return World::NW(pos);
//  case 2:
//    return World::E(pos);
//  case 3:
//    return World::W(pos);
//  case 4:
//    return World::SW(pos);
//  case 5:
//    return World::SE(pos);
//  default:
//    throw "random out of range";
//}

Point2D convertFromLinear(int linearPosition, World world){

  int x = linearPosition % world.getWorldSideSize();
  int y = linearPosition / world.getWorldSideSize();

  Point2D temp(x,y);
  return temp;
}