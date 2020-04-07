#include "SphericalObject.h"

SphericalObject::SphericalObject(dt::Vector2D position, double radius, double density, dt::Vector2D velocity){
	this->position = position;
	this->radius = radius;
	this->velocity = velocity;
	this->density = density;
	color = sf::Color(255, 255, 255);
}

long double SphericalObject::getMass(){
	return (density * 4.0 * PhysicalConstants::PI * pow(radius, 3.0)) / 3.0;
}

void SphericalObject::update(long double& deltaTime, std::vector<SphericalObject>& otherSphericalObjects){
	dt::Vector2D totalForce;
	for(SphericalObject otherSphericalObject : otherSphericalObjects){
		long double forceMagnitude = PhysicalConstants::G * getMass() * otherSphericalObject.getMass() / pow(position.distanceTo(otherSphericalObject.position), 2);
		dt::Vector2D forceDueToCurrentObject = position.to(otherSphericalObject.position, forceMagnitude);
		//std::cout << position.distanceTo(otherSphericalObject.position) << std::endl;
		totalForce += forceDueToCurrentObject;
	}
	dt::Vector2D accelaration = totalForce.divide(getMass());
	velocity += accelaration.divide(pow(deltaTime, 2));
	position += velocity.divide(deltaTime);
}

void SphericalObject::draw(sf::RenderWindow& window){
	sf::CircleShape circle(float(radius), 64U);
	circle.setPosition(position.getX() - radius, position.getY() - radius);
	circle.setFillColor(color);
	window.draw(circle);
}