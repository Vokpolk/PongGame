#include "bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
	//create video mode object
	VideoMode vm(1920, 1080);

	//create and open a window
	RenderWindow window(vm, "Pong", Style::Default);

	int score = 0;
	int lives = 3;

	//create a bat at the bottom center of the screen
	Bat bat(1920.f / 2, 1080 - 20);

	//HUD
	Text hud;

	//font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.TTF");

	//set the font to our retro-style
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	//clock for timing
	Clock clock;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		//handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		//handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bat.moveLeft();
		} else {
			bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bat.moveRight();
		} else {
			bat.stopRight();
		}

		//update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		//update the hud
		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.display();
	}

	return 0;
}
