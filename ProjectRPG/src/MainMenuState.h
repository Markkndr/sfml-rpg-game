#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::Font font;

    Button* gamestate_btn;

    //Functions
    void initKeybinds();
    void initFonts();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    ~MainMenuState();

    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

