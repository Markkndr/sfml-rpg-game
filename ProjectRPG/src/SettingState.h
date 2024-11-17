#pragma once
#include "State.h"
#include "Button.h"

class SettingState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, GUI::Button*>buttons;

    //Initializers
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();
public:
    SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingState();
    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

