//
// Created by voxca on 07/09/2023.
//

#include "AdditionalFunctions.h"

bool AdditionalFunctions::CheckIfZero(const float& value){
  return value == 0;
}

bool AdditionalFunctions::CheckIfZero(const std::vector<Boid*>& neighborhood){
  return neighborhood.empty();
}

bool AdditionalFunctions::CheckIfZero(const Vector2f& vec){
  if (vec.x == 0 || vec.y == 0) {
    return true;
  }
  else {
    return false;
  }
}