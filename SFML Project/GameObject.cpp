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

bool GameObject::colide(GameObject obj1, GameObject obj2)
{

}

void GameObject::Move(float dir_x, float dir_y, float fDeltaTime) {
	//normaliser (dir_x, dir_y))

	float n_dir_x = dir_x/(sqrt(dir_x * dir_x + dir_y * dir_y)) ;
	float n_dir_y = dir_y/(sqrt(dir_x * dir_x + dir_y * dir_y)) ;
	
	float x = n_dir_x * m_speed * fDeltaTime;
	float y = n_dir_y * m_speed * fDeltaTime;

	pShape->move(x, y);

	colide();

}



const sf::Shape& GameObject::getShape() {
	return *pShape;
}
