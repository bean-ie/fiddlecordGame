#include "headers/vector.h"
#include <math.h>

Vector2 subtractVectors(Vector2 first, Vector2 second) {
    return (Vector2){first.x-second.x, first.y-second.y};
}

Vector2 addVectors(Vector2 first, Vector2 second) {
    return (Vector2){first.x+second.x, first.y+second.y};
}

double magnitude(Vector2 v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

double sqrMagnitude(Vector2 v) {
    return (v.x * v.x) + (v.y * v.y);
}

Vector2 normalizeVector(Vector2 v) {
    double length = magnitude(v);
    if (length == 0) return (Vector2){0, 0};
    return divideVector(v, length);
}

Vector2 multiplyVector(Vector2 v, float scalar) {
    return (Vector2){v.x*scalar, v.y*scalar};
}

Vector2 divideVector(Vector2 v, float scalar) {
    return (Vector2){v.x/scalar, v.y/scalar};
}