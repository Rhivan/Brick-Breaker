#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:


	GameObject(float x, float y, float w, float h, sf::Color color);
	GameObject(float x, float y, float r, sf::Color color);


	const sf::Shape& getShape();

private:

	sf::Shape* pShape;

	float w;
	float h;
	float x;
	float y;
	float r;
	

	
};