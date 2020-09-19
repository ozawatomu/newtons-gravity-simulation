#include "SphericalObject.h"

SphericalObject::SphericalObject(dt::Vector2D position, long double radius, long double density, dt::Vector2D velocity){
	this->position = position;
	this->radius = radius;
	this->velocity = velocity;
	this->density = density;
	color = sf::Color(255, 255, 255);
}

long double SphericalObject::getMass(){
	return (density * 4.0 * PhysicalConstants::PI * pow(radius, 3.0)) / 3.0;
}

void SphericalObject::setMass(long double mass){
	density = mass / ((4.0 * PhysicalConstants::PI * pow(radius, 3.0)) / 3.0);
}

void SphericalObject::setColor(int r, int g, int b){
	color = sf::Color(r, g, b);
}

void SphericalObject::update(long double& deltaTime, std::vector<SphericalObject>& otherSphericalObjects){
	dt::Vector2D totalForce;
	for(SphericalObject otherSphericalObject : otherSphericalObjects){
		long double forceMagnitude = PhysicalConstants::G * getMass() * otherSphericalObject.getMass() / pow(position.distanceTo(otherSphericalObject.position), 2);
		dt::Vector2D forceDueToCurrentObject = position.to(otherSphericalObject.position, forceMagnitude);
		totalForce += forceDueToCurrentObject;
	}
	//std::cout << totalForce;
	dt::Vector2D accelaration = totalForce.divide(getMass());
	velocity += accelaration.multiply(deltaTime); // convert accelaration to m/s/deltaTime
	position += velocity.multiply(deltaTime); // convert accelaration to m/deltaTime
}

void SphericalObject::draw(sf::RenderWindow& window){
	sf::CircleShape circle(float(radius), 128U);
	circle.setPosition(float(position.getX() - radius), float(position.getY() - radius));
	circle.setFillColor(color);
	window.draw(circle);
}