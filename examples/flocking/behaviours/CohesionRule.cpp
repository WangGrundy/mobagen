#include "CohesionRule.h"
#include "../gameobjects/Boid.h"
#include "AdditionalFunctions.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  //Vector2f cohesionForce;
  Vector2f positionCenter;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  //add all positions together
  for(auto* i : neighborhood){ //Add all positions
    positionCenter += i->getPosition(); //keep adding neighbourhood positions
  }

  //check if there is no neighbourhood
  if(AdditionalFunctions::CheckIfZero(neighborhood)){ //don't average cohesion if neighbourhood is 0
    return boid->getPosition(); //return itself if its zero
  }
  else{
    //divide and find the average neighbourhood position
    positionCenter /= neighborhood.size();
  }

  //find the vector from this boid position to the centre and return it
  positionCenter = positionCenter - boid->getPosition();

  return positionCenter;
}