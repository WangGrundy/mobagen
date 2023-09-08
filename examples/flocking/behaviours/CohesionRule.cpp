#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  bool CheckIfZero(const float& value);
  bool CheckIfZero(const std::vector<Boid*>& neighborhood);

  float xPos = 0;
  float yPos = 0;

  for(auto* i : neighborhood){ //Add all positions
    xPos += i->getPosition().x;
    xPos += i->getPosition().y;
  }

    if(CheckIfZero(neighborhood)){ //don't average cohesion if neighbourhood is 0
      return cohesionForce;
    }

    if(!CheckIfZero(xPos)){ //don't average cohesion if position is zero
      xPos /= neighborhood.size();
    }
    if(!CheckIfZero(yPos)){
      yPos /= neighborhood.size();
    }

  return cohesionForce;
}

bool CheckIfZero(const float& value){
  return value == 0;
}

bool CheckIfZero(const std::vector<Boid*>& neighborhood){
  return neighborhood.empty();
}