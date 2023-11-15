#pragma once
#include <iostream>

#include<vector>

class GameObject;

namespace Math
{
	float GetAngle(float mouseX, float mouseY, float window_w, float window_h);

	std::vector<GameObject*> Wbigger(GameObject* go1, GameObject* go2);
	std::vector<GameObject*> Hbigger(GameObject* go1, GameObject* go2);

	float Normaliser(float dir_noNorm1, float dir_noNorm2);

};

