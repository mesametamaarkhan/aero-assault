#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include <fstream>
#include "game.h"
using namespace std;
using namespace sf;
class Menu {
public:
    Sprite background;
    Texture bg_texture;
    Texture HTP_BG;
    Sprite HTP;
    Texture playerSelectTex;
    Sprite playerSelectBG;
    bool help = false;
    bool playerSelect = false;

    Menu()
    {
        bg_texture.loadFromFile("img/menu.png");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
    }

    void display_menu(RenderWindow& window)
    {
        window.draw(background);
        window.display();
        Event E;
        while (window.isOpen())
        {
            while (window.pollEvent(E))
            {
                if (E.type == Event::Closed)
                    window.close();
            }


            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                playerSelect = playerSelection();
            }
            if (Keyboard::isKeyPressed(Keyboard::H))
            {
                help = howToPlay();
            }
            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }

            if (playerSelect) {
                if (Keyboard::isKeyPressed(Keyboard::Num1))
                {
                    Game g("img/player.png", 0.25, 0.25);
                    g.run(window);
                }
                if (Keyboard::isKeyPressed(Keyboard::Num2))
                {
                    Game g("img/player-2.png", 0.5, 0.5);
                    g.run(window);
                }
            }

            if (!help)
                window.clear(Color::White);
            
            window.draw(background);
            if (help)
            {
                window.draw(HTP);
            }

            if (playerSelect) {
                window.draw(playerSelectBG);
            }

            window.display();
        }
    }

    bool howToPlay()
    {
        HTP_BG.loadFromFile("img/howtoplay.png");
        HTP.setTexture(HTP_BG);
        HTP.setScale(1, 1);
        help = true;
        return help;
    }

    bool playerSelection() {
        playerSelectTex.loadFromFile("img/player-select.png");
        playerSelectBG.setTexture(playerSelectTex);
        playerSelectBG.setScale(1, 1);
        playerSelect = true;
        return playerSelect;
    }


};


#endif 
