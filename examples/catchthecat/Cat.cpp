#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  foundExit = false;
  visited.clear();
  frontier = queue<Point2D>();
  cameFrom.clear();
  frontierSet.clear();

  //get current position of cat //push Cat position onto queue
  Point2D catPosition = world->getCat();
  frontier.push(catPosition);
  frontierSet.insert(catPosition);
  Point2D currentTile;
 // frontierSet.insert(catPosition); //frontier set

  while(!frontier.empty()){ //keep repeating this until frontier is empty

    // get the current from frontier
    currentTile = frontier.front();

    //frontier pop from frontier
    frontier.pop(); //current position
    frontierSet.erase(currentTile);

    //if cat wins on this tile:
    if(world->catWinsOnSpace(currentTile)){
      foundExit = true;
      std::cout << "---------FOUND WINNING TILE: ------\n";
      std::cout << currentTile.x << " " << currentTile.y << std::endl;
      break;
    }

    //mark current as visited
    visited[currentTile.x][currentTile.y] = true;

    //add visitable neighbours to frontier
    GetAllVisitableNeighboursAndPushOnFrontier(catPosition, currentTile, world);

    //take next node from frontier
    Point2D nextTile = frontier.front();

    //store came from
    cameFrom[nextTile.x][nextTile.y] = currentTile;
  }

  //if not found a successful tile, move randomly
  if(!foundExit){
    return ReturnIfNoPathToWin(currentTile, frontier);
  }

  //Find Head of came from which isn't the cat position, to find next tile
  //TODO: check if its nextTile or currentTile that should be inputted
  Point2D nextTile = FindHead(catPosition, currentTile, cameFrom);

  return {nextTile.x,nextTile.y};
}

Point2D Cat::ReturnIfNoPathToWin(Point2D currentPosition, queue<Point2D>& frontier){
  int randomNumber = Random::Range(0, frontier.size());

  //return random neighbour
  for(int i = 0; i < randomNumber; i++){
    frontier.pop();
    currentPosition = frontier.front();
  }

  std::cout << "---------NO NEIGHBOUR, RANDOM TILE: ------\n";
  std::cout << currentPosition.x << " " << currentPosition.y << std::endl;
  return {currentPosition.x,currentPosition.y};
}

Point2D Cat::FindHead(Point2D catPosition, Point2D& nextTile, map<int, map<int, Point2D>>& cameFrom ){

  //loop until head of map
  while(nextTile != catPosition){
    //run through entire map, to find head
    if(cameFrom[nextTile.x][nextTile.y] == catPosition){
      break;
    }
    //find tile that was before this one
    nextTile = cameFrom[nextTile.x][nextTile.y];
  }

  //TODO: create a path vector to make it simpler
  std::cout << "---------NEXT TILE: ------\n";
  std::cout << nextTile.x << " " << nextTile.y << std::endl;
}

void Cat::GetAllVisitableNeighboursAndPushOnFrontier(Point2D catPosition, Point2D currentTile, World* world){

  //get all neighbours of currentTile
  vector<Point2D> neighboursVisitable = world->neighbors(currentTile);

  //std::cout << "neighbour list: \n";
  //Cycles through all neighbours that are visitable on next tile
  for(int i = 0; i <  neighboursVisitable.size(); i++){
    //not visited
    if(!visited[neighboursVisitable[i].x][neighboursVisitable[i].y]){
      //not cat
      if(catPosition != neighboursVisitable[i]) {
        //not blocked
        if(!world->getContent(neighboursVisitable[i])){
          if(!frontierSet.contains(neighboursVisitable[i])){
            //TODO: Make sure frontier doesn't contain duplicates
            //push to frontier  //push to frontier set
            frontier.push(neighboursVisitable[i]);
            frontierSet.insert(neighboursVisitable[i]);
            //std::cout << "x: " << neighboursVisitable[i].x << " y:" << neighboursVisitable[i].y << std::endl;
            //store came from, do I need to do it here??
            //cameFrom[neighboursVisitable[i].x][neighboursVisitable[i].y] = currentTile;
          }
        }
      }
    }
  }
  //std::cout << "-----------------------------" << std::endl;
}