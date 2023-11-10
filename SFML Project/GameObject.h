#pragma once
#include <SFML/Graphics.hpp>


enum CollisionSide {
	None,
	Left,
	Right,
	Top,
	Bottom
};

class GameObject
{
public:


	GameObject(float x, float y, float w, float h, float speed, sf::Color color);
	GameObject(float x, float y, float r, float speed, sf::Color color);

	~GameObject();


	void Move_dir(float fDirX, float fDirY, float fDeltaTime);
	void Move(float fDeltaTime);
	CollisionSide Collide_Border(int window_w, int window_h);
	bool collide(GameObject* other, int window_w, int window_h);
	std::vector<GameObject*> Wbigger(GameObject* other);
	std::vector<GameObject*>Hbigger(GameObject* other);
	bool InSegment(int i1, int o1, int o2);

	const sf::Shape& getShape();
	const float& getPositionX();
	const float& getPositionY();

private:

	sf::Shape* pShape;

	float m_w;
	float m_h;
	float m_x;
	float m_y;
	float fDeltaTime;
	float m_speed;
	float m_dir_x;
	float m_dir_y;
	

	
};