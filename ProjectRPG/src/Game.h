#pragma once
#include "MainMenuState.h"

class Game
{
private:

	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::ContextSettings settings;
	sf::Clock dtClock;

	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initWindow();
	void initStates();
	void initKeys();

public:

	Game();
	~Game();

	//FUNCTIONS
	
	//Regular
	void endApplication();

	//Update
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();
	//Render
	void Render();
	//Core
	void Run();

};
