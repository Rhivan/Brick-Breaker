#include "GameObject.h"

GameObject::GameObject(float x, float y, float w, float h, sf::Color color) {

	pShape = new sf::RectangleShape();

	pShape->setPosition(x, y);
	oRectangle.setSize(sf::Vector2f(w, h));
	oRectangle.setFillColor(color);

};

GameObject::GameObject(float x, float y, float r, sf::Color color) {


	pShape = new sf::CircleShape();

	oCircle.setPosition(x, y);
	oCircle.setRadius(r);
	oCircle.setFillColor(color);
	
};

const sf::Shape& GameObject::getShape() {
	return *pShape;
}
