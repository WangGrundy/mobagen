#include "Catcher.h"
#include "World.h"


//Calculate the cats most optimal path (shortest distance), place a block on the edge block.
//First place blocks on the most outer side
//Place those blocks in the cat's most optimal position

//Once all these neighbours are taken, Then start putting these blocks randomly in the cat's neighbours

Point2D OriginalCode(World* world, int side);

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  Point2D catPredictedMove;
  auto catPosition = world->getCat();

  return OriginalCode(world, side);

  CreateMapForOuterTiles(side, outerQueue, finishedFirstRun);

  catPredictedMove = GetCatPredictedMove_CatcherVersion(world);

  for(;;){
    //Point2D point = outerQueue.front();

    //if we are able to place a tile on here
    if (world->catcherCanMoveToPosition(catPredictedMove)) {
      return {catPredictedMove.x, catPredictedMove.y};
    }

    //otherwise keep popping
    //place a tile next to it
    //How do we make it so, it places a tile right next the predicted one???
    outerQueue.pop();

  }
}

void Catcher::CreateMapForOuterTiles(const int& side, queue<Point2D>& outerQueue, bool& finishedFirstRun){
  //Create map of all outer tiles
  if(!finishedFirstRun){
    for(int i = -side; i < side; i++){
      //make all RIGHT side tiles visitable
      outerTilesAvailible[side][i] = true;
      outerQueue.push(Point2D(side,i));

      //make all LEFT side tiles visitable
      outerTilesAvailible[-side][i] = true;
      outerQueue.push(Point2D(-side,i));

      //make all TOP side tiles visitable
      outerTilesAvailible[-side + i][-side] = true;
      outerQueue.push(Point2D(-side + i,-side));

      //make all Bottom side tiles visitable
      outerTilesAvailible[-side + i][side] = true;
      outerQueue.push(Point2D(-side + i,side));
    }
    finishedFirstRun = true;
  }
}

Point2D Catcher::GetCatPredictedMove_CatcherVersion(World* world){
  foundExit = false;
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

    //if cat wins on this tile:
    if(world->catWinsOnSpace(currentPosition)){
      foundExit = true;
      break;
    }

    //get all neighbours
    vector<Point2D> neighboursVisitable = world->neighbors(currentPosition);

    //is cat blocked off? cycles through all neighbours visitable,
    for(int i = 0; i <  neighboursVisitable.size() - 1; i++){
      //only add to frontier if cat is able to move onto tile
      if(world->catCanMoveToPosition(neighboursVisitable[i]) &&
          !visited[currentPosition.x][currentPosition.y])
      { //&& !visited[neighboursVisitable[i].x][neighboursVisitable[i].y]
        //adds all neighbours to frontier
        frontier.push(neighboursVisitable[i]);
      }
    }

    visited[next.x][next.y] = true;

    //for every element, check neighbourhood and store came_from
    cameFrom[next.x][next.y] = currentPosition;

    currentPosition = next;
  }

//  //if not found a successful tile, move randomly
//  if(!foundExit){
//    int randomNumber = Random::Range(0, frontier.size());
//
//    //return random neighbour
//    for(int i = 0; i < randomNumber; i++){
//      frontier.pop();
//      currentPosition = frontier.front();
//    }
//    return {currentPosition.x,currentPosition.y};
//  }

//  while(currentPosition != catPosition){
//
//    //run through entire map, to find head
//    if(cameFrom[currentPosition.x][currentPosition.y] == catPosition){
//      break;
//    }
//    currentPosition = cameFrom[currentPosition.x][currentPosition.y];
//  }

  return {currentPosition.x,currentPosition.y};
}

Point2D OriginalCode(World* world, int side){
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();

    //if cat is not
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) {

      //

      return p;
    }

  }
}