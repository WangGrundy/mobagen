#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include "AdditionalFunctions.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
  float x = 0;
  float y = 0;

  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
//  if (!neighborhood.empty()) {
//      Vector2f position = boid->transform.position;
//      int countCloseFlockmates = 0;
//      // todo: find and apply force only on the closest mates
//  }

  for(auto* i : neighborhood){ //Add all positions
    x += i->getPosition().x;
    y += i->getPosition().y;
  }

  if(AdditionalFunctions::CheckIfZero(neighborhood)){ //don't average velocity if neighbourhood is 0
    return separatingForce;
  }

  if(!AdditionalFunctions::CheckIfZero(x)){ //don't average velocity if velocity is zero
    x /= neighborhood.size();
  }
  if(!AdditionalFunctions::CheckIfZero(y)){
    y /= neighborhood.size();
  }

  //set SF
  separatingForce.x = -x;
  separatingForce.y = -y;

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
