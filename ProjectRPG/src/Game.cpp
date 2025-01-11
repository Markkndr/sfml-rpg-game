#include "stdafx.h"
#include "Game.h"

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("config/graphics.ini");

}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initVariables()
{
    this->window = NULL;
    this->dt = 0.f;
    this->gridSize = 160.f;
}

//Initializers
void Game::initWindow()
{

    if (this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen, 
            this->gfxSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title, 
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);
    }

    this->window->setVerticalSyncEnabled(this->gfxSettings.vSync);
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
}

void Game::initKeys()
{
    std::ifstream ifs("config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}

//Const&Dest
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//Functions
void Game::endApplication()
{
    std::cout << "Ending application" << std::endl;
}

void Game::UpdateDt()
{
    //updates dt variable with time to render one frame
    this->dt = this->dtClock.restart().asSeconds();

}

void Game::UpdateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::Update()
{
    this->UpdateSFMLEvents();

    if (!this->states.empty() /* && this->window->hasFocus()*/)
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    //App end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::Render()
{
    this->window->clear();

    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::Run()
{
    while (this->window->isOpen())
    {
        this->UpdateDt();
        this->Update();
        this->Render();
    }
}
