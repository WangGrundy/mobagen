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

  Vector2f diffVec;
  Vector2f ourVec;
  float distance;
  int countFlockmates = 0;
  Vector2f accumulation;

  ourVec = boid->getPosition();

  //check if neighborhood is zero
  if(AdditionalFunctions::CheckIfZero(neighborhood)){ //if
    separatingForce = Vector2f::normalized(separatingForce);
    return separatingForce;
  }

  for(auto* i : neighborhood) {  // loop through all boids near us to find closest
    diffVec = ourVec - i->getPosition();
    distance = diffVec.getMagnitude();

    if(distance < desiredMinimalDistance && distance > 0){
      countFlockmates++;
      Vector2f hat = diffVec.normalized();
      separatingForce = hat/distance;
      accumulation += separatingForce;
    }
  }

  if(countFlockmates > 0){
    accumulation /= countFlockmates;
  }

  separatingForce = accumulation;

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
