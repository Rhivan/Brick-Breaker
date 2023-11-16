#pragma once

#include "GameObject.h"
#include "Magazine.h"
#include <vector>

class GameManager
{
public:
	GameManager(int Brick_size_x, int Brick_size_y);
	~GameManager();
	void GameLoop();
	void CreateBricks(int mBrick_size_x, int mBrick_size_y);
	void Event();
	void Update();
	void Draw();

private:
	int window_w;
	int window_h;
	sf::Clock clock;
	float fDeltaTime;
	sf::RenderWindow* oWindow;
	GameObject* gun;
	Magazine* oMagazine;
	std::vector<GameObject*> oBullets;
	std::vector< std::vector<GameObject*> > oBricks;
	int mBrick_size_x;
	int mBrick_size_y;
	float margin_x;
	float margin_y;
	int mBricks_y;
	int mBricks_x;
};