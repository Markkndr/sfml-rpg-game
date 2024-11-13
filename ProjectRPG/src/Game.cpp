#include "Game.h"

//Initializers
void Game::initWindow()
{
    std::ifstream ifs("config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(0, 0);
    bool vertical_sync_enabled = true;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    settings.antialiasingLevel = 8;
    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Default, settings);
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys));
}

//Const&Dest
Game::Game()
{
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
