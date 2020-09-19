#include <iostream>
#include <SFML/Graphics.hpp>
#include "Space.h"

int main(){
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's Gravity Simulation", sf::Style::Close, contextSettings);
	sf::View view(sf::Vector2f(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	bool isWheelDrag = false;
	sf::Vector2f oldPos;

	Space space;

	// CHAOS
	
	view.setSize(view.getSize().x * 750000, view.getSize().y * 750000);
	SphericalObject a{dt::Vector2D(0, 0), 6371000, 5510};
	SphericalObject b{dt::Vector2D(384400000, 0), 1737100, 3340, dt::Vector2D(0.0, 1023.056)};
	SphericalObject c{dt::Vector2D(284400000, 0), 4737100, 3340, dt::Vector2D(0.0, -1023.056)};
	SphericalObject d{dt::Vector2D(-284400000, 0), 3737100, 3340, dt::Vector2D(0.0, 1023.056)};
	SphericalObject e{dt::Vector2D(-184400000, 0), 2737100, 3340, dt::Vector2D(0.0, -1023.056)};
	SphericalObject f{dt::Vector2D(-384400000, 0), 5737100, 3340, dt::Vector2D(0.0, -1023.056)};
	a.setColor(223, 71, 60);
	b.setColor(174, 60, 96);
	c.setColor(243, 195, 60);
	d.setColor(37, 94, 121);
	e.setColor(38, 119, 120);
	f.setColor(130, 180, 187);
	space.addObject(a);
	space.addObject(b);
	space.addObject(c);
	space.addObject(d);
	space.addObject(e);
	space.addObject(f);
	
	

	// STABLE 3 BODY SOLUTION
	/*
	view.setCenter(0, 0);
	view.setSize(view.getSize().x / 200, view.getSize().y / 200);
	double radius{0.2};
	double mass{15000000000};
	SphericalObject x1{dt::Vector2D(0.97000436, -0.24308753), radius, 1, dt::Vector2D(-0.93240737 / -2, -0.86473146 / -2)};
	SphericalObject x2{dt::Vector2D(-0.97000436, 0.24308753), radius, 1, dt::Vector2D(-0.93240737 / -2, -0.86473146 / -2)};
	SphericalObject x3{dt::Vector2D(0, 0), radius, 1, dt::Vector2D(-0.93240737, -0.86473146)};
	x1.setMass(mass);
	x2.setMass(mass);
	x3.setMass(mass);
	x1.setColor(237, 62, 21);
	x2.setColor(252, 161, 6);
	x3.setColor(26, 142, 156);
	space.addObject(x1);
	space.addObject(x2);
	space.addObject(x3);
	*/


	// EARTH AND MOON
	/*
	view.setCenter(0, 0);
	view.setSize(view.getSize().x*750000, view.getSize().y*750000);
	space.setTimeScale(65472);
	SphericalObject earth{dt::Vector2D(0, 0), 6371 * 1000, 0, dt::Vector2D(0, 0)};
	earth.setMass(5.972 * pow(10, 24));
	earth.setColor(95, 188, 255);
	SphericalObject moon{dt::Vector2D(384400 * 1000, 0), 1737.1 * 1000, 0, dt::Vector2D(0, 1022)};
	moon.setMass(7.34767309 * pow(10, 22));
	moon.setColor(194, 227, 244);
	space.addObject(earth);
	space.addObject(moon);
	*/

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
						space.speedUp();
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
						space.slowDown();
					}
					break;
				case sf::Event::MouseWheelScrolled:
					if(event.mouseWheelScroll.delta > 0){
						view.setSize(view.getSize().x / 1.1, view.getSize().y / 1.1);
					} else{
						view.setSize(view.getSize().x * 1.1, view.getSize().y * 1.1);
					}
					//std::cout << WINDOW_WIDTH/view.getSize().x << std::endl;
					break;
				case sf::Event::MouseButtonPressed:
					isWheelDrag = true;
					oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					break;
				case sf::Event::MouseButtonReleased:
					isWheelDrag = false;
					break;
				case sf::Event::MouseMoved:
					if(isWheelDrag){
						const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
						const sf::Vector2f deltaPos = oldPos - newPos;
						view.setCenter(view.getCenter() + deltaPos);
						window.setView(view);
						oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					}
					break;

			}
		}
		window.clear();
		window.setView(view);



		space.update();
		space.draw(window);



		window.display();
	}
}