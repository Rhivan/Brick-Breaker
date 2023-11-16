
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include <iostream>
#include "Math.h"
#include "GameManager.h"

int main(int argc, char** argv)
{
    GameManager oGameManager(20, 20);
    
    oGameManager.GameLoop();

    return 0;
}