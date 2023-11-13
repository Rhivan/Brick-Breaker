#include "GameObject.h"

#include <iostream>

GameObject::GameObject(float x, float y, float w, float h, float speed, sf::Color color) {

	pShape = new sf::RectangleShape(sf::Vector2f(w, h));

	pShape->setPosition(x, y);
	pShape->setFillColor(color);
	pShape->setRotation(0.f);
	
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	

	m_speed = speed;


};

GameObject::GameObject(float x, float y, float r, float speed, sf::Color color) {


	pShape = new sf::CircleShape(r);

	pShape->setPosition(x, y);
	pShape->setFillColor(color);

	m_x = x;
	m_y = y;
	m_w = r * 2;
	m_h = r * 2;

	m_speed = speed;

	
};

GameObject::~GameObject() {
	delete pShape;
}

std::vector<GameObject*> GameObject::Wbigger(GameObject* other)
{
	std::vector<GameObject*> out(2);

	if (m_w > other->m_w)
	{
		out[1] = this;
		out[0] = other;
	}
	else
	{
		out[1] = other;
		out[0] = this;
	}

	return out;
}

std::vector<GameObject*> GameObject::Hbigger(GameObject* other)
{
	std::vector<GameObject*> out(2);

	if (m_h > other->m_h)
	{
		out[1] = this;
		out[0] = other;
	}
	else
	{
		out[1] = other;
		out[0] = this;
	}

	return out;
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
	float X_min = this->m_x;
	float X_max = this->m_x + this->m_w;
	float Y_min = this->m_y;
	float Y_max = this->m_y + this->m_h;
	

	if (X_min <= 0) {
		return Left;
	}
	
	if (X_max >= window_w) {
		return Right;
	}
	
	if (Y_min <= 0 ) {
		return Top;
	}
	
	if (Y_max >= window_h) {
		return Bottom;
	}

	return None;
}



CollisionSide GameObject::collide(GameObject* other)
{
	std::vector<GameObject*> Width= this->Wbigger(other);
	std::vector<GameObject*> Height = this->Hbigger(other);

	float X1min = Width[0]->m_x;
	float X1max = Width[0]->m_x + Width[0]->m_w;
	float X2min = Width[1]->m_x;
	float X2max = Width[1]->m_x + Width[1]->m_w;

	float Y1min = Height[0]->m_y;
	float Y1max = Height[0]->m_y + Height[0]->m_h;
	float Y2min = Height[1]->m_y;	
	float Y2max = Height[1]->m_y + Height[1]->m_h;
	


	if (InSegment(X1min, X2min, X2max) && InSegment(Y1min, Y2min, Y2max) || InSegment(X1min, X2min, X2max) && InSegment(Y1max, Y2min, Y2max))
		return Right;

	if (InSegment(X1max, X2min, X2max) && InSegment(Y1min, Y2min, Y2max) || InSegment(X1max, X2min, X2max) && InSegment(Y1max, Y2min, Y2max))
		return Left;

	if (InSegment(Y1min, Y2min, Y2max) && InSegment(X1min, X2min, X2max) || InSegment(Y1min, Y2min, Y2max) && InSegment(X1max, X2min, X2max))
		return Bottom;

	if (InSegment(Y1max, Y2min, Y2max) && InSegment(X1min, X2min, X2max) || InSegment(Y1max, Y2min, Y2max) && InSegment(X1max, X2min, X2max))
		return Top;


	else
	{
		return None;
	}
}



void GameObject::Move(float fDeltaTime) {

	//normaliser (dir_x, dir_y))
	float n_dir_x = m_dir_x /(sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y));
	float n_dir_y = m_dir_y/ (sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y));
	
	float x = n_dir_x * m_speed * fDeltaTime;
	float y = n_dir_y * m_speed * fDeltaTime;

	m_x += x;
	m_y += y;

	pShape->setPosition(m_x, m_y);

	

}

void GameObject::SetDir(float fDirX, float fDirY) {

	m_dir_x = fDirX;
	m_dir_y = fDirY;
	
}

void GameObject::MultDir(float fFactorX, float fFactorY) {

	m_dir_x *= fFactorX;
	m_dir_y *= fFactorY;

}


const sf::Shape& GameObject::getShape() {
	return *pShape;
}

const float& GameObject::getPositionX() {
	return m_x;
	
}

const float& GameObject::getPositionY() {
	return m_y;
}

const float& GameObject::getDirX() {
	return m_dir_x;
}

const float& GameObject::getDirY() {
	return m_dir_y;
}