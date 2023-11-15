
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include <iostream>
#include "Math.h"

int main(int argc, char** argv)
{
    int window_w = 800;
    int window_h = 600;
    
    sf::RenderWindow oWindow(sf::VideoMode(window_w, window_h), "SFML");

    GameObject oWhiterect(400.f, 300.f, 200.f, 200.f, 10.f, sf::Color::White);
    
    GameObject gun(window_w/2 + 5,window_h - 6, 10.f, 30.f, 0.f, sf::Color::Blue);
    gun.setPosition(window_w / 2, window_h, 0.5f, 1.f);

    GameObject* oBullet = NULL;

    //GAME LOOP

    sf::Clock clock;

    float fDeltaTime = 0.f;

    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();

            if (oEvent.type == sf::Event::KeyPressed)
            {
                if (oEvent.key.code == sf::Keyboard::Escape)
                    oWindow.close();
            }

            if (oEvent.type == sf::Event::MouseButtonPressed) 
            {
                if (oEvent.mouseButton.button == sf::Mouse::Button::Left)
                {
                    oBullet = new GameObject(-1, -1, 5.f, 200.f, sf::Color::Yellow);
                    oBullet->setPosition(gun.getPositionX(), gun.getPositionY(1.f), 0.5f, 0.5f);

                    sf::Vector2i mouse = sf::Mouse::getPosition(oWindow);

                    float fDirX = oBullet->GetVectDirX(gun.getPositionX(0.5f), mouse.x);
                    float fDirY = oBullet->GetVectDirY(gun.getPositionY(1.f), mouse.y);

                    oBullet->SetDir(Math::Normaliser(fDirX, fDirY), Math::Normaliser(fDirY , fDirX));
                }
            }
        }

        //UPDATE

        sf::Vector2i mouse = sf::Mouse::getPosition(oWindow);

        float fAngle = gun.GetAngle(mouse.x, mouse.y, window_w, window_h);
        gun.SetRotation(fAngle, 0.5f, 1.f );

        if (oBullet != nullptr)
        { 
            oBullet->Move(fDeltaTime);
            
            CollisionSide in = oBullet->Collide_Border(window_w, window_h);
            CollisionSide on = oBullet->collide(&oWhiterect);
            
            if (in == Left)
            {
                oBullet->MultDir(-1, 1);
            }

            if (in == Right)
            {
                oBullet->MultDir(-1, 1);
            }

            if (in == Top)
            {
                oBullet->MultDir(1, -1);
            }
            if (in == Bottom)
            {
                oBullet->MultDir(1, -1);
            }

            if (on == Left)
            {

                oBullet->MultDir(-1, 1);
            }

            if (on == Right)
            {
                oBullet->MultDir(-1, 1);
            }

            if (on == Top)
            {
                oBullet->MultDir(1, -1);
            }

            if (on == Bottom)
            {
                oBullet->MultDir(1, -1);
            }
        }




        //DRAW
     
        oWindow.clear();


        
        oWindow.draw(oWhiterect.getShape());
        oWindow.draw(gun.getShape());
        if (oBullet != nullptr)
        {
            oWindow.draw(oBullet->getShape());
        }


        oWindow.display();

        //END LOOP
        fDeltaTime = clock.restart().asSeconds();
    }


    return 0;
}
