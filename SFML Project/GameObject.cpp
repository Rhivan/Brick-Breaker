#include "GameObject.h"

GameObject::GameObject(float x, float y, float w, float h, float speed, sf::Color color) {

	pShape = new sf::RectangleShape(sf::Vector2f(w, h));

	pShape->setPosition(x, y);
	pShape->setFillColor(color);
	
	m_speed = speed;


};

GameObject::GameObject(float x, float y, float r, float speed, sf::Color color) {


	pShape = new sf::CircleShape(r);

	pShape->setPosition(x, y);
	pShape->setFillColor(color);

	m_speed = speed;

	
};

std::vector<GameObject*> GameObject::Wbigger(GameObject* other)
{
	std::vector<GameObject*> out(2);

	if (w > other->w)
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

	if (h > other->h)
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

	if (InSegment(Width[0]->x,Width[1]->x, (Width[1]->x + Width[1]->w)) || InSegment((Width[0]->x + Width[0]->w), Width[1]->x, (Width[1]->x + Width[1]->w))    && InSegment(Width[0]->y, Width[1]->y, (Width[1]->y + Width[1]->h)) || InSegment((Width[0]->y + Width[0]->h), Width[1]->y, (Width[1]->y + Width[1]->h)))
	{
		return true;
	}
	else return false;
}

void GameObject::Move(float dir_x, float dir_y, float fDeltaTime) {

	//normaliser (dir_x, dir_y))
	float n_dir_x = dir_x/(sqrt(dir_x * dir_x + dir_y * dir_y)) ;
	float n_dir_y = dir_y/(sqrt(dir_x * dir_x + dir_y * dir_y)) ;
	
	float x = n_dir_x * m_speed * fDeltaTime;
	float y = n_dir_y * m_speed * fDeltaTime;

	pShape->move(x, y);

}



const sf::Shape& GameObject::getShape() {
	return *pShape;
}
