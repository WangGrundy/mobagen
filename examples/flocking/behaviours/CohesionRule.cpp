#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  bool CheckIfZeroS(const float& value);
  bool CheckIfZeroS(const std::vector<Boid*>& neighborhood);

  float xPos = 0;
  float yPos = 0;

  for(auto* i : neighborhood){ //Add all positions
    xPos += i->getPosition().x;
    yPos += i->getPosition().y;
  }

  if(CheckIfZeroS(neighborhood)){ //don't average cohesion if neighbourhood is 0
    return cohesionForce;
  }

  if(!CheckIfZeroS(xPos)){ //don't average cohesion if position is zero
    xPos /= neighborhood.size();
  }
  if(!CheckIfZeroS(yPos)){
    yPos /= neighborhood.size();
  }

  //set Cohesion force
  cohesionForce.x = xPos;
  cohesionForce.y = yPos;

  return cohesionForce;
}

bool CheckIfZeroS(const float& value){
  return value == 0;
}

bool CheckIfZeroS(const std::vector<Boid*>& neighborhood){
  return neighborhood.empty();
}