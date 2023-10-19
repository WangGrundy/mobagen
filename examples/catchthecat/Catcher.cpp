#include "Catcher.h"
#include "World.h"

Point2D OriginalCode(World* world, int side);

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  auto catPosition = world->getCat();

  vector<Point2D> catPath = generatePath(world);

  //if theres no path
  if(catPath.empty()){

    //get random tile next to cat
    Point2D randomTileNextToCat = getRandomTileNextToCat(world);
    if(randomTileNextToCat != catPosition){
      return randomTileNextToCat;
    }
    //If no tiles next to cat, place random tiles, place random tiles instead
    return randomTileInWorld(world, side);
  }

  //if there is path, return wanted tile
  return catPath[0];
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