#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat {
private:
	Vector2f m_Position;
	RectangleShape m_Shape;
	float m_Speed = 1000.f;
	bool m_MovingRight = false;
	bool m_MovingLeft = false;

public:
	Bat(float startX, float startY);

	FloatRect getPosition();
	RectangleShape getShape();
	void moveRight();
	void moveLeft();
	void stopRight();
	void stopLeft();
	void update(Time dt);
};
