//
// Created by voxca on 07/09/2023.
//

#ifndef MOBAGEN_ADDITIONALFUNCTIONS_H
#define MOBAGEN_ADDITIONALFUNCTIONS_H
#include "../gameobjects/Boid.h"

class AdditionalFunctions {
public:
   static bool CheckIfZero(const float& value);
   static bool CheckIfZero(const std::vector<Boid*>& neighborhood);
   static bool CheckIfZero(const Vector2f& v2);
};

#endif  // MOBAGEN_ADDITIONALFUNCTIONS_H