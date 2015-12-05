#pragma once

// #include <cassert>

namespace ime {

struct Vector2 {
  float x,
        y;

  Vector2()
    : x {0.0f}, y {0.0f}
  {}

  Vector2(float nx, float ny)
    : x {nx}, y {ny}
  {}

  // float& operator[](unsigned i) {
  //   assert(i < 2);
  //   return (i == 0) ? x : y;
  // }
};

}

// vim: set ts=2 sw=2 tw=80
