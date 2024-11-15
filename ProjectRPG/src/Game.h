#pragma once
#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;    
	sf::ContextSettings windowSettings;

	float dt;
	bool fullscreen;

	std::stack<State*> states;
	std::vector<sf::VideoMode> videoModes;

	std::map<std::string, int> supportedKeys;

	//Initialization
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
