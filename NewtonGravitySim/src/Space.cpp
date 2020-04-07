#include "Space.h"

Space::Space(){
	lastUpdatedTime = std::chrono::steady_clock::now();
}

void Space::addObject(SphericalObject& sphericalObject){
	objects.push_back(sphericalObject);
}

void Space::addObject(dt::Vector2D position, double radius, double density, dt::Vector2D velocity){
	objects.push_back(SphericalObject(position, radius, density, velocity));
}

void Space::update(){
	auto currentTime = std::chrono::steady_clock::now();
	long double deltaTimeSeconds = long double(std::chrono::duration_cast <std::chrono::nanoseconds> (currentTime - lastUpdatedTime).count());
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