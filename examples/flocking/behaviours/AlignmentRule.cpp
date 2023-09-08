#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"
#include "AdditionalFunctions.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  //iterate over the neighbourhood and add each velicity
  for (auto* i : neighborhood){
    averageVelocity += i->getVelocity();
  }

  //check if neighbour hood is zero
  if(AdditionalFunctions::CheckIfZero(neighborhood)){ //don't average velocity if neighbourhood is 0
    return averageVelocity;
  }

  //check if neighbour hood velocity is zero and then divide to get average velocity
  if(!AdditionalFunctions::CheckIfZero(averageVelocity)){ //don't average velocity if velocity is zero
    averageVelocity /= neighborhood.size();
  }

  return Vector2f::normalized(averageVelocity);
}