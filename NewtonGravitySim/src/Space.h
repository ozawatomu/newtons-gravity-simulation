#pragma once

#include <vector>
#include <chrono>
#include "SphericalObject.h"

class Space{
	std::vector<SphericalObject> objects;
	std::chrono::steady_clock::time_point lastUpdatedTime;
	long double timeScale;
public:
	Space();
	void addObject(SphericalObject& sphericalObject);
	void addObject(dt::Vector2D position, long double radius, long double density = 1.0, dt::Vector2D velocity = dt::Vector2D(0.0, 0.0));
	void setTimeScale(long double timeScale);
	long double getTimeScale();
	void speedUp();
	void slowDown();
	void update();
	void draw(sf::RenderWindow&);
};

