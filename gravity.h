#ifndef GRAVITY_H
#define GRAVITY_H

#include <vector>

// Vector sınıfı
class Vector {
public:
    double x, y;
    Vector(double x = 0, double y = 0);
    ~Vector();

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    friend Vector operator*(double scalar, const Vector& v);
};

// Body sınıfı
class Body {
public:
    double mass;
    Vector velocity, position, acceleration;

    Body();
    virtual ~Body();
    Body(double mass, const Vector& position, const Vector& velocity);

    virtual void updateVelocity(const Vector& totalForce, double timeStep);
    virtual void updatePosition(double timeStep);

    Vector calculateGravitationalForce(const Body& other) const;
};

// Rocket, Gezegen, Asteroid sınıfları
class Rocket : public Body {
public:
    Rocket();
    ~Rocket();
    Rocket(double mass, const Vector& position, const Vector& velocity, const Vector& exhaustVelocity, double exhaustRate);

    void updateVelocity(const Vector& totalForce, double timeStep) override;
    void updatePosition(double timeStep) override;

private:
    Vector exhaustVelocity;
    double exhaustRate;
};

class Gezegen : public Body {
public:
    double orbitalSpeed;
    Gezegen(double mass, Vector position, Vector velocity, double orbitalSpeed);

    void updatePosition(double timeStep) override;
};

class Asteroid : public Body {
public:
    Asteroid(double mass, Vector position, Vector velocity);
    void updatePosition(double timeStep) override;
};

// Universe sınıfı
class Universe {
public:
    double timeStep;
    std::vector<Body*> bodies;

    explicit Universe(double timeStep);
    ~Universe();

    void addBody(Body* body);
    void calculateForces() const;
    void updatePositions();
    void step();
};

#endif
