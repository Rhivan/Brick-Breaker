#include "GameManager.h"
#include "GameObject.h"
#include "Math.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Magazine.h"

Magazine::Magazine()
{
	oBullets.resize(3);
	for (int i = 0; i < oBullets.size(); ++i)
	{
		oBullets[i] = new GameObject(-1, -1, 5.f, 200.f, sf::Color::Yellow);
	
	}
}

Magazine::~Magazine()
{
	
}

bool Magazine::notEmpty()
{
	if (oBullets.size() > 0)
	{
		return true;
	}

	return false;
}

GameObject* Magazine::GetBullet()
{
	GameObject* oBullet = oBullets[oBullets.size() - 1];
	oBullets.pop_back();
	return oBullet;
}