#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {

  int temp;
  Point2D visitThis = randomStartPoint(w);

  //if stack is empty, push random point onto stack.
  if(stack.empty() && visitThis == Point2D(INT_MAX, INT_MAX)) {
    return false; // stop here
  }

  if(stack.empty()){ //add to stack
    stack.push_back(visitThis);
  }

  //get last item in stack
  std::vector<Point2D> visitables = getVisitables(w , stack[stack.size() - 1]);

  visitThis = stack.back();
  visited[visitThis.x][visitThis.y] = true;

  //if visitables is empty, pop the end of stack.
  if(visitables.empty()){
    w->SetNodeColor(visitThis,Color::Black);
    stack.pop_back();
    return true;
  }

  //if we do have something in visitables:
  if(visitables.size() == 1){ //if its just 1 item...
    BreakWalls(visitThis, visitables[0], w);
    w->SetNodeColor(visitThis,Color::Red);
    visitThis = visitables[0]; //get first item out
    w->SetNodeColor(visitThis,Color::Yellow);

  }
  else{//if we have more than 1 item in vistables
    w->SetNodeColor(visitThis,Color::Red);
    temp = rand() % visitables.size(); //create a random number to visit
    BreakWalls(visitThis, visitables[temp], w);
    visitThis = visitables[temp];
    w->SetNodeColor(visitThis,Color::Yellow);
  }

  visited[visitThis.x][visitThis.y] = true;
  stack.push_back(visitThis);

  return true; //return true if we want to keep recursing
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;

  std::vector<Point2D> visitables;

  //check walls
  //if no walls, add to visitables

  if(p.y != -sideOver2 && !visited[p.x][p.y - 1]){
    visitables.push_back(p.Up());
  }
  if(p.x != sideOver2 && !visited[p.x + 1][p.y]){
    visitables.push_back(p.Right());
  }
  if(p.y != sideOver2 && !visited[p.x][p.y + 1]){
    visitables.push_back(p.Down());
  }
  if(p.x != -sideOver2 && !visited[p.x - 1][p.y]){
    visitables.push_back(p.Left());
  }

  return visitables;
}

void RecursiveBacktrackerExample::BreakWalls(Point2D oldPoint , Point2D newPoint, World* w){

  auto delta = newPoint - oldPoint;

  if(delta.x == -1){
    w->SetWest(oldPoint, false);
  }

  if(delta.x == 1){
    w->SetEast(oldPoint, false);
  }
  if(delta.y == -1){
    w->SetNorth(oldPoint, false);
  }
  if(delta.y == 1){
    w->SetSouth(oldPoint, false);
  }
}