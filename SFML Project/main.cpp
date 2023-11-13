
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include <iostream>

int main(int argc, char** argv)
{

    int window_w = 800;
    int window_h = 600;
    
    sf::RenderWindow oWindow(sf::VideoMode(window_w, window_h), "SFML");

    GameObject oBluerect(110.f, 400.f, 50.f, 50.f, 200.f, sf::Color::Blue);

    GameObject oRedrect(100.f, 100.f, 200.f, 200.f, 10.f, sf::Color::Red);

    //GameObject oGreencircle(500.f, 100.f, 100.f, 10.f, sf::Color::Green);

    oBluerect.SetDir(0, -1);
    std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
    std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
    

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
                
                if (oEvent.key.code == sf::Keyboard::Space)
                {
                    oBluerect.SetDir(-1, 0);
                    std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
                    std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
                }

            }
        }

        //UPDATE
       
        oBluerect.Move(fDeltaTime);
        
       
        CollisionSide in = oBluerect.Collide_Border(window_w, window_h);
        CollisionSide on = oBluerect.collide(&oRedrect);

        if (in == Left)
        {
			oBluerect.SetDir(1, oBluerect.getDirY());

			std::cout << "Collision detected with Border!" << std::endl;
            std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
            std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
		}
       
        if (in == Right)
        {
            oBluerect.SetDir( -1, oBluerect.getDirY());

            std::cout << "Collision detected with Border!" << std::endl;
            std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
            std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
        }

		if (in == Top)
		{
			oBluerect.SetDir( oBluerect.getDirX(), 1);

            std::cout << "Collision detected with Border!" << std::endl;
		}
        if (in == Bottom)
        {
            oBluerect.SetDir(oBluerect.getDirX(), -1);

            std::cout << "Collision detected with Border!" << std::endl;
		}

        if (on == Left)
        {

			oBluerect.MultDir(-1,1);

			std::cout << "Collision detected with Left of Red Rectangle!" << std::endl;
			std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
			std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
		}

        if (on == Right)
        {
            oBluerect.MultDir(-1, 1);

			std::cout << "Collision detected with Right of Red Rectangle!" << std::endl;
			std::cout << "dir_x: " << oBluerect.getDirX() << std::endl;
			std::cout << "dir_y: " << oBluerect.getDirY() << std::endl;
		}

        if (on == Top)
        {
            oBluerect.MultDir(1,-1);
            std::cout << "Collision detected with Top of Red Rectangle!" << std::endl;
        }

        if (on == Bottom)
        {
            oBluerect.MultDir(1,-1);
            std::cout << "Collision detected with  Bottom of Red Rectangle!" << std::endl;
		}




        //if (oBluerect.collide(&oGreencircle)) 
        {
         /*   std::cout << "Collision detected with Green Circle!" << std::endl;    */
        }


        //DRAW
     
        oWindow.clear();


        oWindow.draw(oBluerect.getShape());
        oWindow.draw(oRedrect.getShape());
        //oWindow.draw(oGreencircle.getShape());



        oWindow.display();

        //END LOOP
        fDeltaTime = clock.restart().asSeconds();
    }


    return 0;
}
