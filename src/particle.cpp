#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include "particle.hpp"

Particle::Particle(Vector2 p, Vector2 v, Color c)
{
    position = p;
    velocity = v;
    color = c;
}

Particle::Particle(int width, int height)
{
    position.x = GetRandomValue(0, width-1);
    position.y = GetRandomValue(0, height-1);
    velocity.x = GetRandomValue(-100, 100) / 100.f;
    velocity.y = GetRandomValue(-100, 100) / 100.f;
    color = (Color){(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),255};
    // color = (Color){0,0,0,100};
}

float Particle::getDistance(Vector2 otherPosition) {
    const float dx = position.x - otherPosition.x;
    const float dy = position.y - otherPosition.y;
    // Pythagorean theorem
    return sqrt((dx*dx) + (dy*dy));
}

Vector2 Particle::getDistanceFromOtherPoint(Vector2 otherPosition) {
    float distance = getDistance(otherPosition);
    if (distance == 0.0f) distance = 1;
    const float dx = position.x - otherPosition.x;
    const float dy = position.y - otherPosition.y;
    Vector2 normal = (Vector2){dx*(1/distance), dy*(1/distance)};
    return normal;
}

void Particle::moveParticle(int width, int height) {
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x < 0) {
        position.x += width;
    }
    else if (position.x >= width) {
        position.x -= width;
    }
        
    if (position.y < 0) {
        position.y += height;
    }
    else if (position.y >= height) {
        position.y -= height;
    }
}

void Particle::drawParticle() {
    DrawPixelV(position, color);
}

void Particle::attractParticle(Vector2 positionToAttract, float attractionRate)
{
    float distance = fmax(getDistance(positionToAttract),0.5);
    Vector2 normal = getDistanceFromOtherPoint(positionToAttract);

    velocity.x -= normal.x/distance;
    velocity.y -= normal.y/distance;
}

void Particle::friction(float frictionRate) {
    velocity.x *= frictionRate;
    velocity.y *= frictionRate;
}