#pragma once
#include "State.h"
#include "GraphicsSettings.h"
#include "Gui.h"

class SettingState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*>buttons;
    std::map<std::string, gui::DropDownList*>dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Initializers
    void initVariables();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initGui();
    void initText();

public:
    SettingState(StateData* state_data);
    virtual ~SettingState();
    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

