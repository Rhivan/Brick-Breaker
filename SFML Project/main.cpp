
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include <iostream>

int main(int argc, char** argv)
{

    int window_w = 800;
    int window_h = 600;
    
    sf::RenderWindow oWindow(sf::VideoMode(window_w, window_h), "SFML");

    GameObject oBluerect(100.f, 100.f, 50.f, 50.f, 50.f, sf::Color::Blue);

    GameObject oRedrect(300.f, 100.f, 100.f, 100.f, 10.f, sf::Color::Red);

    GameObject oGreencircle(500.f, 100.f, 100.f, 10.f, sf::Color::Green);

    bool isMoving = false;

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
                //if (oEvent.key.code == sf::Keyboard::Up)
                //{
                //    oBluerect.Move(0.f, -10.f, fDeltaTime);
                //}
                //if (oEvent.key.code == sf::Keyboard::Down)
                //{
                //    oBluerect.Move(0.f, 10.f, fDeltaTime);
                //}
                //if (oEvent.key.code == sf::Keyboard::Left)
                //{
                //    oBluerect.Move(-10.f, 0.f, fDeltaTime);
                //}
                //if (oEvent.key.code == sf::Keyboard::Right)
                //{
                //    oBluerect.Move(10.f, 0.f, fDeltaTime);
                //}
                if (oEvent.key.code == sf::Keyboard::Space)
                {
                    isMoving = !isMoving;
                }

            }
        }

        //UPDATE
        if (isMoving)
        {
            oBluerect.Move({1,0}, fDeltaTime);
        }

     /*   if (oBluerect.Move(oBluerect.Collide_Border(window_w, window_h))
        {

        }*/

        if (oBluerect.collide(&oRedrect)) 
        {
            std::cout << "Collision detected with Red Rectangle!" << std::endl;
        }

        if (oBluerect.collide(&oGreencircle)) 
        {
            std::cout << "Collision detected with Green Circle!" << std::endl;    
        }


        //DRAW
     
        oWindow.clear();


        oWindow.draw(oBluerect.getShape());
        oWindow.draw(oRedrect.getShape());
        oWindow.draw(oGreencircle.getShape());



        oWindow.display();

        //END LOOP
        fDeltaTime = clock.restart().asSeconds();
    }


    return 0;
}
