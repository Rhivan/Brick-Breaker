#pragma once

#include "GameObject.h"

#include <vector>

class Magazine
{
public:
	Magazine();
	~Magazine();
	bool notEmpty();
	GameObject* GetBullet();
	

private:
	std::vector<GameObject*> oBullets;
};
