#include "Game.h"

void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
}

//Initializers
void Game::initWindow()
{
    std::ifstream ifs("config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool vertical_sync_enabled = true;
    bool fullscreen = false;
    int antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();
    
    this->fullscreen = fullscreen;
    windowSettings.antialiasingLevel = antialiasing_level; 
    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    }

    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Const&Dest
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this - states.empty())
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

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
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
        this->states.top()->render(this->window);

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
