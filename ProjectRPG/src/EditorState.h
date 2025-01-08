#pragma once

#include "Gui.h"
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    //Variables
    PauseMenu* pmenu;
    sf::Font font;
    sf::Text cursorText;
    sf::View view;

    std::map<std::string, gui::Button*>buttons;

    TileMap* tileMap;
    
    sf::RectangleShape sidebar;

    sf::RectangleShape selectorRect;
    sf::IntRect textureRect;

    gui::TextureSelector* textureSelector;

    sf::RectangleShape collisionBox;

    bool collision;
    short type;
    float cameraSpeed;

    //Functions
    void initVariables();
    void initView();
    void initBackground();
    void initKeybinds();
    void initPauseMenu();
    void initFonts();
    void initText();
    void initButtons();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorImput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};
