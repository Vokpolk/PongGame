#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f m_Position;
	RectangleShape m_Shape;

	float m_Speed = 1500.f;
	float m_DirectionX = 0.2f;
	float m_DirectionY = 0.2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();
	RectangleShape getShape();

	float getXVelocity();

	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();

	void update(Time dt);
};
