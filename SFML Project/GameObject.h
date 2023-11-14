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


	void SetDir(float fDirX, float fDirY);
	void Move(float fDeltaTime);
	CollisionSide Collide_Border(int window_w, int window_h);
	CollisionSide collide(GameObject* other);
	std::vector<GameObject*> Wbigger(GameObject* other);
	std::vector<GameObject*>Hbigger(GameObject* other);
	bool InSegment(int i1, int o1, int o2);
	float GetAngle(float mouseX, float mouseY, float window_w, float window_h);
	void MultDir(float fDirX, float fDirY);
	void SetOrigin(float x, float y);
	void SetRotation(float a);

	const sf::Shape& getShape();
	const float& getPositionX();
	const float& getPositionY();
	const float& getDirX();
	const float& getDirY();

	

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
	float angle;
	float M_PI = 3.14159265358979323846;
	

	
};