#include "gravity.h"
#include <cmath>

// Vector
Vector::Vector(double x, double y) : x(x), y(y) {}
Vector::~Vector() {}

Vector Vector::operator+(const Vector& other) const { return {x + other.x, y + other.y}; }
Vector Vector::operator-(const Vector& other) const { return {x - other.x, y - other.y}; }
Vector Vector::operator*(const Vector& other) const { return {x * other.x, y * other.y}; }
Vector Vector::operator/(const Vector& other) const { return {other.x == 0 || other.y == 0 ? 0 : x / other.x, y / other.y}; }
Vector Vector::operator*(double scalar) const { return {x * scalar, y * scalar}; }
Vector Vector::operator/(double scalar) const { return {scalar == 0 ? 0 : x / scalar, y / scalar}; }
Vector operator*(double scalar, const Vector& v) { return {v.x * scalar, v.y * scalar}; }

// Body
Body::Body() = default;
Body::~Body() = default;
Body::Body(double mass, const Vector& position, const Vector& velocity) : mass(mass), position(position), velocity(velocity) {}

void Body::updateVelocity(const Vector& totalForce, double timeStep) {
    acceleration = totalForce / mass;
    velocity = velocity + acceleration * timeStep;
}

void Body::updatePosition(double timeStep) {
    position = position + velocity * timeStep;
}

Vector Body::calculateGravitationalForce(const Body& other) const {
    const Vector diff = other.position - position;
    double distanceSquared = diff.x * diff.x + diff.y * diff.y;
    if (distanceSquared == 0) return {0, 0};
    double distance = sqrt(distanceSquared);
    double forceMagnitude = 1 * (mass * other.mass) / distanceSquared;
    Vector direction = diff / distance;
    return direction * forceMagnitude;
}

// Rocket
Rocket::Rocket() = default;
Rocket::~Rocket() = default;
Rocket::Rocket(double mass, const Vector& position, const Vector& velocity, const Vector& exhaustVelocity, double exhaustRate)
        : exhaustVelocity(exhaustVelocity), exhaustRate(exhaustRate) {
    this->mass = mass;
    this->velocity = velocity;
    this->position = position;
}

void Rocket::updateVelocity(const Vector& totalForce, double timeStep) {
    Vector thrustForce = exhaustVelocity * exhaustRate;
    Vector totalForce2 = totalForce + thrustForce;
    Vector acceleration = totalForce2 / mass;
    velocity = velocity + acceleration * timeStep;
}

void Rocket::updatePosition(double timeStep) {
    position = position + velocity * timeStep;
    mass -= exhaustRate * timeStep;
    if (mass < 0.1) mass = 0.1;
}

// Gezegen
Gezegen::Gezegen(double mass, Vector position, Vector velocity, double orbitalSpeed)
        : Body(mass, position, velocity), orbitalSpeed(orbitalSpeed) {}

void Gezegen::updatePosition(double timeStep) {
    velocity.x += orbitalSpeed * timeStep;
    Body::updatePosition(timeStep);
}

// Asteroid
Asteroid::Asteroid(double mass, Vector position, Vector velocity) : Body(mass, position, velocity) {}

void Asteroid::updatePosition(double timeStep) { Body::updatePosition(timeStep); }

// Universe
Universe::Universe(double timeStep) : timeStep(timeStep) {}
Universe::~Universe() {
    for (auto body : bodies) delete body;
}

void Universe::addBody(Body* body) { bodies.push_back(body); }
void Universe::calculateForces() const {
    for (size_t i = 0; i < bodies.size(); ++i) {
        Vector totalForce(0, 0);
        for (size_t j = 0; j < bodies.size(); ++j) {
            if (i != j) totalForce = totalForce + bodies[i]->calculateGravitationalForce(*bodies[j]);
        }
        bodies[i]->updateVelocity(totalForce, timeStep);
    }
}

void Universe::updatePositions() {
    for (auto body : bodies) body->updatePosition(timeStep);
}

void Universe::step() {
    calculateForces();
    updatePositions();
}
