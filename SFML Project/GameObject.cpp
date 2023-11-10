#include "GameObject.h"

#include <iostream>

GameObject::GameObject(float x, float y, float w, float h, float speed, sf::Color color) {

	pShape = new sf::RectangleShape(sf::Vector2f(w, h));

	pShape->setPosition(x, y);
	pShape->setFillColor(color);
	pShape->setRotation(70.f);
	
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
	if (i1 > o1 && i1 < o2)
	{
		return true;
	}

	return false;
}


CollisionSide GameObject::Collide_Border(int window_w,int window_h)
{
	std::vector<std::vector<float>> matrix_corner(4);
	matrix_corner[0] = { this->m_x, (this->m_y + this->m_h) };
	matrix_corner[1] = { (this->m_x + this->m_w), (this->m_y + this->m_h) };
	matrix_corner[2] = { this->m_x, this->m_y };
	matrix_corner[3] = { (this->m_x + this->m_w), this->m_y };
	

	if (matrix_corner[0][0] <= 0 || matrix_corner[2][0] <= 0) {
		return Left;
	}
	else if (matrix_corner[1][0] >= window_w || matrix_corner[3][0] <= window_w) {
		return Right;
	}
	else if (matrix_corner[0][1] <= 0  || matrix_corner[1][1] <= 0) {
		return Top;
	}
	else if (matrix_corner[2][1] >= window_h || matrix_corner[3][1] >= window_h) {
		return Bottom;
	}

	return None;
}



bool GameObject::collide(GameObject* other , int window_w, int window_h)
{
	std::vector<GameObject*> Width= this->Wbigger(other);
	std::vector<GameObject*> Height = this->Hbigger(other);


	bool bIsXMinInside = InSegment(Width[0]->m_x, Width[1]->m_x, (Width[1]->m_x + Width[1]->m_w));

	bool bIsXMaxInside = InSegment((Width[0]->m_x + Width[0]->m_w), Width[1]->m_x, (Width[1]->m_x + Width[1]->m_w));

	bool bIsYMinInside = InSegment(Height[0]->m_y, Height[1]->m_y, (Height[1]->m_y + Height[1]->m_h));

	bool bIsYMaxInside = InSegment((Height[0]->m_y + Height[0]->m_h), Height[1]->m_y, (Height[1]->m_y + Height[1]->m_h));

	std::cout << Width[0]->m_x << " " << Width[0]->m_y << " "<< std::endl;

	if ((bIsXMinInside || bIsXMaxInside) && (bIsYMinInside || bIsYMaxInside))
	{
		return true;
	}
	
	return false;
}



void GameObject::Move_dir(float fDirX, float fDirY, float fDeltaTime) {

	//normaliser (dir_x, dir_y))
	float n_dir_x = fDirX/(sqrt(fDirX * fDirX + fDirY * fDirY));
	float n_dir_y = fDirY/ (sqrt(fDirX * fDirX + fDirY * fDirY));
	
	float x = n_dir_x * m_speed * fDeltaTime;
	float y = n_dir_y * m_speed * fDeltaTime;

	m_x += x;
	m_y += y;

	pShape->setPosition(m_x, m_y);

	

}


void GameObject::Move(float fDeltaTime) {

	Move_dir(this->m_dir_x, this->m_dir_y, fDeltaTime);
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
