#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include "AdditionalFunctions.h"
#include <limits>
#include <cmath>

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //  if (!neighborhood.empty()) {
  //      Vector2f position = boid->transform.position;
  //      int countCloseFlockmates = 0;
  //      // todo: find and apply force only on the closest mates
  //  }

  float desiredDistance = desiredMinimalDistance;
  Vector2f ourPosition = Vector2f::zero();
  float lowestDistance= std::numeric_limits<float>::max();
  float currentDistance = -1;
  Vector2f closestFlockMate(0,0);

  //check if neighborhood is zero
  if(AdditionalFunctions::CheckIfZero(neighborhood)){ //don't average velocity if neighbourhood is 0
    separatingForce = Vector2f::normalized(separatingForce);
    return separatingForce;
  }

  ourPosition = boid->transform.position;

  for(auto* i : neighborhood){ //loop through all boids near us to find closest

    //distance = √((x2 – x1)² + (y2 – y1)²).
    //track current distance
    float x = pow((i->getPosition().x - ourPosition.x),2); // (x2 – x1)²
    float y = pow((i->getPosition().y - ourPosition.y), 2); // (y2 – y1)²
    currentDistance = sqrt(x + y); // √((x2 – x1)² + (y2 – y1)²).

    //if distance is lower than our lowest, then update it
    if(currentDistance < lowestDistance){
      lowestDistance = currentDistance; //Get the closest flock mate position data
      closestFlockMate.x = i->getPosition().x - ourPosition.x;
      closestFlockMate.y = i->getPosition().y - ourPosition.y;
    }
  }

  //if distance is less than desiredDistance, move it away inversely proportional to the distance between them
  if(lowestDistance < desiredDistance){
    closestFlockMate.x = 1/closestFlockMate.x;
    closestFlockMate.y = 1/closestFlockMate.y;

    separatingForce = closestFlockMate;
  }

  separatingForce = Vector2f::normalized(separatingForce);
  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
