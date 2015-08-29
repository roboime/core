#pragma once

#include <cassert>

namespace ime {

struct Vector2 {
  float x,
        y,
        z;

  Vector3()
    : x {0.0f}, y {0.0f}, z {0.0f}
  {}

  Vector3(float nx, float ny, float nz)
    : x {nx}, y {ny}, z {nz}
  {}

  float& operator[](unsigned i) {
    assert(i < 3);
    return (i == 0 ? x : (i==1 ? y : z));
  }
};

}

// vim: set ts=2 sw=2 tw=80
