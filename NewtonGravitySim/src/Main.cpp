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
	//space.addObject(dt::Vector2D(400, 400), 150, 1);
	//space.addObject(dt::Vector2D(700, 700), 30, 1, dt::Vector2D(-0.15, 0.0));
	//space.addObject(dt::Vector2D(700, 900), 10, 1, dt::Vector2D(0.1, 0.0));

	space.addObject(dt::Vector2D(0, 0), 6371000, 5510);
	space.addObject(dt::Vector2D(384400000, 0), 1737100, 3340, dt::Vector2D(0.0, 1023.056));
	//space.addObject(dt::Vector2D(284400000, 0), 1737100, 3340*2, dt::Vector2D(0.0, -1023.056));

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					std::cout << "Pressed" << std::endl;
					break;
				case sf::Event::MouseWheelScrolled:
					if(event.mouseWheelScroll.delta > 0){
						view.setSize(view.getSize().x / 1.1, view.getSize().y / 1.1);
					} else{
						view.setSize(view.getSize().x * 1.1, view.getSize().y * 1.1);
					}
					std::cout << WINDOW_WIDTH/view.getSize().x << std::endl;
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