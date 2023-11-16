#include "GameManager.h"
#include "GameObject.h"
#include "Math.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Magazine.h"

GameManager::GameManager(int Brick_size_x, int Brick_size_y)
{
    window_w = 800;
    window_h = 600;

    oWindow = new sf::RenderWindow(sf::VideoMode(window_w, window_h), "SFML");

    fDeltaTime = 0.f;

    gun = new GameObject(window_w / 2 + 5, window_h - 6, 10.f, 30.f, 0.f, sf::Color::Blue);
    gun->setPosition(window_w / 2, window_h, 0.5f, 1.f);

    oMagazine = new Magazine();

    mBrick_size_x = Brick_size_x;
    mBrick_size_y = Brick_size_y;

    CreateBricks(mBrick_size_x, mBrick_size_y);

    

}

void GameManager::CreateBricks(int mBrick_size_x, int mBrick_size_y)
{
    
    float space_x = 5.f;
    float space_y = 5.f;
    
    int nb_ligne = 5;
    int Brick_Space = mBrick_size_x + space_x;
    int window_space_x = (window_w - space_x);
    int rest = window_space_x % Brick_Space;
    int nb_colonne = ((window_space_x - rest)  / Brick_Space)   ;

    

    mBricks_y = nb_ligne;
    mBricks_x = nb_colonne;

    oBricks.resize(mBricks_y);

    for (int y = 0; y < mBricks_y; ++y)
    {
        for (int x = 0; x < mBricks_x; ++x) 
        {
            float fX = space_x + (x * ( mBrick_size_x + space_x ) );
            float fY = space_y + (y * ( mBrick_size_y + space_y ) );

            GameObject* pBrick = new GameObject(-1, -1, mBrick_size_x, mBrick_size_y, 0.f, sf::Color::Red);
            pBrick->setPosition(fX, fY, 0.f, 0.f);
            oBricks[y].push_back(pBrick);
        }
    }


}

GameManager::~GameManager()
{

}

void GameManager::GameLoop()
{
    while (oWindow->isOpen())
    {
        Event();
        Update();
        Draw();
        fDeltaTime = clock.restart().asSeconds();
    }
}

void GameManager::Event()
{
    sf::Event oEvent;
    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == sf::Event::Closed)
            oWindow->close();

        if (oEvent.type == sf::Event::KeyPressed)
        {
            if (oEvent.key.code == sf::Keyboard::Escape)
                oWindow->close();
        }

        if (oEvent.type == sf::Event::MouseButtonPressed)
        {
            if (oEvent.mouseButton.button == sf::Mouse::Button::Left && oMagazine->notEmpty())
            {
                GameObject* oBullet = oMagazine->GetBullet();
                oBullet->setPosition(gun->getPositionX(), gun->getPositionY(1.f), 0.5f, 0.5f);
                oBullets.push_back(oBullet);

                sf::Vector2i mouse = sf::Mouse::getPosition(*oWindow);

                float fDirX = oBullet->GetVectDirX(gun->getPositionX(0.5f), mouse.x);
                float fDirY = oBullet->GetVectDirY(gun->getPositionY(1.f), mouse.y);

                oBullet->SetDir(Math::Normaliser(fDirX, fDirY), Math::Normaliser(fDirY, fDirX));
            }
        }
    }
}

void GameManager::Update()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(*oWindow);

    float fAngle = gun->GetAngle(mouse.x, mouse.y, window_w, window_h);
    gun->SetRotation(fAngle, 0.5f, 1.f);

    for (int i = 0; i < oBullets.size(); i++)
    {
        oBullets[i]->Move(fDeltaTime);

        CollisionSide in = oBullets[i]->Collide_Border(window_w, window_h);
        if (in == Left)
        {
            oBullets[i]->MultDir(-1, 1);
        }

        if (in == Right)
        {
            oBullets[i]->MultDir(-1, 1);
        }

        if (in == Top)
        {
            oBullets[i]->MultDir(1, -1);
        }
        if (in == Bottom)
        {
            delete oBullets[i];
            oBullets[i] = nullptr;
            oBullets.erase(oBullets.begin() + i);
            continue;
        }

        CollisionSide on = CollisionSide::None;

        for (int y = 0; y < mBricks_y; ++y)
        {
            for (int x = 0; x < mBricks_x; ++x)
            {
                if (oBricks[y][x] == nullptr)
                    continue;

                CollisionSide on2 = oBullets[i]->collide(oBricks[y][x]);
                if (on2 == CollisionSide::None)
                    continue;

                if (on2 == on)
					continue;

                on = on2;

                if (on == Left)
                {

                    oBullets[i]->MultDir(-1, 1);
                    delete oBricks[y][x];
                    oBricks[y][x] = nullptr;
                
                    continue;

                }

                if (on == Right)
                {
                    oBullets[i]->MultDir(-1, 1);
                    delete oBricks[y][x];
                    oBricks[y][x] = nullptr;
                    
                    continue;
                }

                if (on == Top)
                {
                    oBullets[i]->MultDir(1, -1);
                    delete oBricks[y][x];
                    oBricks[y][x] = nullptr;
                    
                    continue;
                }

                if (on == Bottom)
                {
                    oBullets[i]->MultDir(1, -1);
                    delete oBricks[y][x];
                    oBricks[y][x] = nullptr;
                    
                    continue;

                }

            }
        }
    }
}

void GameManager::Draw()
{
    oWindow->clear();
    
    oWindow->draw(gun->getShape());
    
    for (int i = 0; i < oBullets.size(); i++)
    {
        oWindow->draw(oBullets[i]->getShape());
    }

    for (int y = 0; y < mBricks_y; ++y)
    {
        for (int x = 0; x < mBricks_x; ++x)
        {
            if (oBricks[y][x] == nullptr)
                continue;
            oWindow->draw(oBricks[y][x]->getShape());
        }
    }

    oWindow->display();

}