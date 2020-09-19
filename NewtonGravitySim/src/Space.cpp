#include "Space.h"

Space::Space(){
	lastUpdatedTime = std::chrono::steady_clock::now();
	timeScale = 1.0;
	std::cout << "Time scale: " + std::to_string(timeScale) << std::endl;
}

void Space::addObject(SphericalObject& sphericalObject){
	objects.push_back(sphericalObject);
}

void Space::addObject(dt::Vector2D position, long double radius, long double density, dt::Vector2D velocity){
	objects.push_back(SphericalObject(position, radius, density, velocity));
}

void Space::setTimeScale(long double timeScale){
	this->timeScale = timeScale;
	std::cout << "Time scale: " + std::to_string(timeScale) << std::endl;
}

long double Space::getTimeScale(){
	return timeScale;
}

void Space::speedUp(){
	timeScale *= 2;
	std::cout << "Time scale: " + std::to_string(timeScale) << std::endl;
}

void Space::slowDown(){
	timeScale /= 2;
	std::cout << "Time scale: " + std::to_string(timeScale) << std::endl;
}

void Space::update(){
	auto currentTime = std::chrono::steady_clock::now();
	long double deltaTimeSeconds = ((long double(std::chrono::duration_cast <std::chrono::nanoseconds> (currentTime - lastUpdatedTime).count()))/pow(10, 9))*timeScale;
	lastUpdatedTime = currentTime;
	for(int i = 0; i < objects.size(); i++){
		std::vector<SphericalObject> otherObjects;
		for(int j = 0; j < i; j++){
			otherObjects.push_back(objects[j]);
		}
		for(int j = i + 1; j < objects.size(); j++){
			otherObjects.push_back(objects[j]);
		}
		objects[i].update(deltaTimeSeconds, otherObjects);
	}
}

void Space::draw(sf::RenderWindow& window){
	for(SphericalObject sphericalObject : objects){
		sphericalObject.draw(window);
	}
}