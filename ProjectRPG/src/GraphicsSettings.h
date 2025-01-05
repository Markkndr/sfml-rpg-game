#pragma once


class GraphicsSettings
{
public:
	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	GraphicsSettings();
	~GraphicsSettings();

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

