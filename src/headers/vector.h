#ifndef VECTOR_H
#define VECTOR_H

struct Vector2 {
    float x;
    float y;
};

typedef struct Vector2 Vector2;

Vector2 subtractVectors(Vector2 first, Vector2 second);
Vector2 addVectors(Vector2 first, Vector2 second);
double magnitude(Vector2 v);
double sqrMagnitude(Vector2 v);
Vector2 normalizeVector(Vector2 v);
Vector2 multiplyVector(Vector2 v, float scalar);
Vector2 divideVector(Vector2 v, float scalar);
Vector2 rotateVector(Vector2 v, float angle);

#endif