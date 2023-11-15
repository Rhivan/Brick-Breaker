#include "Math.h"
#include "GameObject.h"
#include <iostream>



float Math::GetAngle(float mouseX, float mouseY, float window_w, float window_h)
{
	float fPx = window_w / 2.f;
	float fPy = window_h;

	float adjacant = mouseX - fPx;
	float opposer = mouseY - fPy;

	float angle = std::atan2(opposer, adjacant) * (180 / 3.14) + 90;

	std::cout << angle << std::endl;

	return angle;
}

std::vector<GameObject*> Math::Wbigger(GameObject* go1, GameObject* go2)
{
	std::vector<GameObject*> out(2);

	if (go1->getW() > go2->getW())
	{
		out[1] = go1;
		out[0] = go2;
	}
	else
	{
		out[1] = go2;
		out[0] = go1;
	}

	return out;
}


std::vector<GameObject*> Math::Hbigger(GameObject* go1, GameObject* go2)
{
	std::vector<GameObject*> out(2);

	if (go1->getH() > go2->getH())
	{
		out[1] = go1;
		out[0] = go2;
	}
	else
	{
		out[1] = go2;
		out[0] = go1;
	}

	return out;
}

float Math::Normaliser(float dir_noNorm1, float dir_noNorm2)
{
	float norm = sqrt(dir_noNorm1 * dir_noNorm1 + dir_noNorm2 * dir_noNorm2);

	float dir_Norm = dir_noNorm1 / norm;

	return dir_Norm;
}