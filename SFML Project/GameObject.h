#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:


	GameObject(float x, float y, float w, float h, float speed, sf::Color color);
	GameObject(float x, float y, float r, float speed, sf::Color color);


	void Move(float x, float y, float fDeltaTime);
	bool collide(GameObject* other);
	std::vector<GameObject*> Wbigger(GameObject* other);
	std::vector<GameObject*>Hbigger(GameObject* other);
	bool InSegment(int i1, int o1, int o2);


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