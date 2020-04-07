#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2D.h"
#include "PhysicalConstants.h"

class SphericalObject{
	dt::Vector2D position, velocity;
	long double radius, density;
	sf::Color color;
public:
	SphericalObject(dt::Vector2D position, long double radius, long double density = 1.0, dt::Vector2D velocity = dt::Vector2D(0.0, 0.0));
	long double getMass();
	dt::Vector2D getPosition();
	void update(long double& deltaTime, std::vector<SphericalObject>& otherSphericalObjects);
	void draw(sf::RenderWindow& window);
};

