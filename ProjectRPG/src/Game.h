#pragma once
#include "MainMenuState.h"

class Game
{
private:

	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;

	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	float dt;
	float gridSize;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initGraphicsSettings();
	void initStateData();
	void initVariables();
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
