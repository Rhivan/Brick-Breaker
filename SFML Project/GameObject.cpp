#include "GameObject.h"

#include <iostream>

GameObject::GameObject(float x, float y, float w, float h, float speed, sf::Color color) {

	pShape = new sf::RectangleShape(sf::Vector2f(w, h));

	pShape->setPosition(x, y);
	pShape->setFillColor(color);
	
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

std::vector<float> GameObject::Collide_Border(int window_w,int window_h)
{
	std::vector<std::vector<float>> matrix_corner(4);
	matrix_corner[0] = { this->m_x, (this->m_y + this->m_h) };
	matrix_corner[1] = { (this->m_x + this->m_w), (this->m_y + this->m_h) };
	matrix_corner[2] = { this->m_x, this->m_y };
	matrix_corner[3] = { (this->m_x + this->m_w), this->m_y };
	if (matrix_corner[0][0] = 0)
	{
		return { 1,this->m_dir_y };
	}
}

bool GameObject::collide(GameObject* other) 
{
	//// Obtenir la boîte englobante globale (rectangle qui encadre étroitement) de cet objet
	//sf::FloatRect thisBounds = pShape->getGlobalBounds();

	//// Obtenir la boîte englobante globale de l'autre objet passé en tant que paramètre
	//sf::FloatRect otherBounds = other.pShape->getGlobalBounds();

	//// Vérifier si les deux boîtes englobantes se chevauchent
	//return thisBounds.intersects(otherBounds);
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
	else return false;
}



void GameObject::Move(std::vector<float> dir, float fDeltaTime) {

	//normaliser (dir_x, dir_y))
	float n_dir_x = dir[0]/(sqrt(dir[0] * dir[0] + dir[1] * dir[1]));
	float n_dir_y = dir[1]/ (sqrt(dir[0] * dir[0] + dir[1] * dir[1]));
	
	float x = n_dir_x * m_speed * fDeltaTime;
	float y = n_dir_y * m_speed * fDeltaTime;

	m_x += x;
	m_y += y;
	m_dir_x = n_dir_x;
	m_dir_x = n_dir_y;

	

}

const sf::Shape& GameObject::getShape() {
	return *pShape;
}

