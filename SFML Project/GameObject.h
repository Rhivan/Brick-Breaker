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
	bool InSegment(int i1, int o1, int o2);
	float GetAngle(float mouseX, float mouseY, float window_w, float window_h);
	void MultDir(float fDirX, float fDirY);
	void SetRotation(float a, float fRatioX, float fRatioY);
	float GetVectDirX(float mouseX, float window_w);
	float GetVectDirY(float mouseY, float window_h);

	void setPosition(float fX, float fY, float fRatioX = 0.5f, float fRatioY = 0.5f);

	const sf::Shape& getShape();
	float getPositionX(float fRatioX = 0.5f);
	float getPositionY(float fRatioY = 0.5f);
	const float& getW();
	const float& getH();
	const float& getDirX();
	const float& getDirY();

	

private:

	sf::Shape* pShape;

	float m_w;
	float m_h;
	float fDeltaTime;
	float m_speed;
	float m_dir_x;
	float m_dir_y;
	float angle;
	float M_PI = 3.14159265358979323846;

	void SetOrigin(float fRatioX, float fRatioY);

	
};