#include "GameObject.h"
#include "Math.h"
#include <iostream>

GameObject::GameObject(float x, float y, float w, float h, float speed, sf::Color color) {

	pShape = new sf::RectangleShape(sf::Vector2f(w, h));

	pShape->setFillColor(color);
	
	m_w = w;
	m_h = h;

	m_speed = speed;

	setPosition(x, y);
};


GameObject::GameObject(float x, float y, float r, float speed, sf::Color color) {

	pShape = new sf::CircleShape(r);

	pShape->setFillColor(color);

	m_w = r * 2;
	m_h = r * 2;

	m_speed = speed;

	setPosition(x, y);
};


GameObject::~GameObject() {
	delete pShape;
}





void GameObject::setPosition(float fX, float fY, float fRatioX, float fRatioY) 
{
	SetOrigin(fRatioX, fRatioY);
	pShape->setPosition(fX, fY);
}

bool GameObject::InSegment(int i1, int o1, int o2)
{
	if (i1 >= o1 && i1 <= o2)
	{
		return true;
	}

	return false;
}


CollisionSide GameObject::Collide_Border(int window_w,int window_h)
{
	float X_min = getPositionX(0.f);
	float X_max = getPositionX(1.f);
	float Y_min = getPositionY(0.f);
	float Y_max = getPositionY(1.f);
	

	if (X_min <= 0) {
		return Left;
	}
	
	if (X_max >= window_w) {
		return Right;
	}
	
	if (Y_min <= 0 ) {
		return Top;
	}
	
	if (Y_min >= window_h) {
		return Bottom;
	}

	return None;
}



CollisionSide GameObject::collide(GameObject* other)
{
	std::vector<GameObject*> Width= Math::Wbigger(this, other);
	std::vector<GameObject*> Height = Math::Hbigger(this, other);

	float X1min = Width[0]->getPositionX(0);
	float X1max = Width[0]->getPositionX(1);
	float X2min = Width[1]->getPositionX(0);
	float X2max = Width[1]->getPositionX(1);

	float Y1min = Height[0]->getPositionY(0);
	float Y1max = Height[0]->getPositionY(1);
	float Y2min = Height[1]->getPositionY(0);	
	float Y2max = Height[1]->getPositionY(1);
	


	if ((X1max > X2min && X1min < X2max)) {
		if (Y1max > Y2min && Y1min < Y2max) {
			// Objets qui se chevauchent
			float overlapX = std::min(X1max, X2max) - std::max(X1min, X2min);
			float overlapY = std::min(Y1max, Y2max) - std::max(Y1min, Y2min);

			if (overlapX > overlapY) {
				// Collision verticale
				if (Y1min < Y2min) {
					return Top;
				}
				else {
					return Bottom;
				}
			}
			else {
				// Collision horizontale 
				if (X1min < X2min) {
					return Left;
				}
				else {
					return Right;
				}
			}
		}
	}

	return None;

}



void GameObject::Move(float fDeltaTime) 
{
	float x = m_dir_x * m_speed * fDeltaTime;
	float y = m_dir_y * m_speed * fDeltaTime;

	float fX = getPositionX() + x;
	float fY = getPositionY() + y;

	setPosition(fX, fY);
}



void GameObject::MultDir(float fFactorX, float fFactorY) 
{
	m_dir_x *= fFactorX;
	m_dir_y *= fFactorY;
}


void GameObject::SetDir(float fDirX, float fDirY)
{

	m_dir_x = fDirX ;
	m_dir_y = fDirY ;
}

float GameObject::GetVectDirX(float fX1, float fX2)
{
	return fX2 - fX1;
}

float GameObject::GetVectDirY(float fY1, float fY2)
{
	return fY2 - fY1;
}

float GameObject::GetAngle(float mouseX, float mouseY, float window_w, float window_h) 
{
	float fPx = window_w / 2.f;
	float fPy = window_h;

	float adjacent = mouseX - fPx;
	float opposer = mouseY - fPy;

	float angle = std::atan2(opposer, adjacent) * (180/3.14) + 90;

	return angle;
}

const sf::Shape& GameObject::getShape() {
	return *pShape;
}

float GameObject::getPositionX(float fRatioX) {
	
	sf::Vector2f oOrigin = pShape->getOrigin();
	sf::Vector2f oPosition = pShape->getPosition();

	oPosition.x -= oOrigin.x;
	
	oPosition.x += fRatioX * m_w;
	
	return oPosition.x;
	
}

float GameObject::getPositionY(float fRatioY) {
	sf::Vector2f oOrigin = pShape->getOrigin();
	sf::Vector2f oPosition = pShape->getPosition();

	oPosition.y -= oOrigin.y;

	oPosition.y += fRatioY * m_h;

	return oPosition.y;
}

const float& GameObject::getW() {
	return m_w;
}

const float& GameObject::getH() {
	return m_h;
}


const float& GameObject::getDirX() {
	return m_dir_x;
}

const float& GameObject::getDirY() {
	return m_dir_y;
}

void GameObject::SetOrigin(float fRatioX, float fRatioY)
{
	pShape->setOrigin(fRatioX * m_w, fRatioY * m_h);
}

void GameObject::SetRotation(float a, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);
	pShape->setRotation(a);
}