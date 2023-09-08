#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  bool CheckIfZero(const float& value);
  bool CheckIfZero(const std::vector<Boid*>& neighborhood);

  float x = 0;
  float y = 0;

  for (auto* i : neighborhood){
    x += i->getVelocity().x;
    y += i->getVelocity().y;
  }

  if(CheckIfZero(neighborhood)){ //don't average velocity if neighbourhood is 0
    return averageVelocity;
  }

  if(!CheckIfZero(x)){ //don't average velocity if velocity is zero
    x /= neighborhood.size();
  }
  if(!CheckIfZero(y)){
    y /= neighborhood.size();
  }

  //set velocity
  averageVelocity.x = x;
  averageVelocity.y = y;

  return Vector2f::normalized(averageVelocity);
}

bool CheckIfZero(const float& value){
  return value == 0;
}

bool CheckIfZero(const std::vector<Boid*>& neighborhood){
  return neighborhood.empty();
}