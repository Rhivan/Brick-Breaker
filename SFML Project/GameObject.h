#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:


	GameObject(float x, float y, float w, float h, float speed, sf::Color color);
	GameObject(float x, float y, float r, float speed, sf::Color color);


	void Move(float x, float y, float fDeltaTime);
	bool colide(GameObject obj1, GameObject obj2);


	const sf::Shape& getShape();

private:

	sf::Shape* pShape;

	float w;
	float h;
	float x;
	float y;
	float r;
	float fDeltaTime;
	float m_speed;
	

	
};