#include <cassert>

namespace ime {

float& Vector2::
operator[](unsigned i) {
    assert(i < 2);
    return (i == 0) ? x : y;
}

Vector2 Vector2::
operator-(Vector2 v){
    return Vector2(x-v.x ,y-v.y);
}

Vector2 Vector2::
operator/(float f){
    return Vector2(x/f,y/f);
}

}