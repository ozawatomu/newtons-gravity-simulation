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

	Space space;
	space.addObject(dt::Vector2D(400, 400), 150, 1);
	space.addObject(dt::Vector2D(700, 700), 30, 1, dt::Vector2D(-0.15, 0.0));
	space.addObject(dt::Vector2D(700, 900), 10, 1, dt::Vector2D(0.1, 0.0));

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					std::cout << "Pressed" << std::endl;
					space.update();
					break;
			}
		}
		window.clear();
		space.draw(window);
		window.display();
	}
}