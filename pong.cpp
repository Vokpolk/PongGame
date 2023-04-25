#include "bat.h"
#include "ball.h"
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

	//create a ball
	Ball ball(1920.f / 2, 0);

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
		
		//update the bat, the ball and hud


		//update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		//update the hud
		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		//handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y) {
			//reverse
			ball.reboundBottom();
			//remove life
			--lives;
			//check zero lives
			if (lives < 1) {
				//reset the score
				score = 0;
				//reset the lives
				lives = 3;
			}
		}
		
		//handle ball hitting top
		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			//add a point to score
			++score;
		}

		//handle ball hitting sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
			ball.reboundSides();
		}

		//has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
		}

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}
