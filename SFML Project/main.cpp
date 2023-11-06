
#include <SFML/Graphics.hpp>
#include "gameObject.h"

int main(int argc, char** argv)
{
    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(800, 600), "SFML");

    GameObject oBluerect(100.f, 100.f, 50.f, 50.f, sf::Color::Blue);

    GameObject oRedcircle(300.f, 100.f, 100.f, sf::Color::Red);


    int i = 5;

    sf::RectangleShape rs;

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();

            if (oEvent.key.code == sf::Keyboard::Escape)
                oWindow.close();
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        
        oWindow.draw(oBluerect.getShape());
        oWindow.draw(oRedcircle.getShape());
       


        oWindow.display();
    }

    return 0;
}
