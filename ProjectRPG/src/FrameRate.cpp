#include "FrameRate.h"

#include <iostream>

FrameRate::FrameRate() : 
    timer(0)
{

}

FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{

}

void FrameRate::Load()
{
    if (!font.loadFromFile("Assets/Fonts/manaspc.ttf"))
    {
        std::cout << "FAILED TO LOAD FONT" << std::endl;
    }
    else
    {
        std::cout << "Font loaded" << std::endl;
        displayFrameRate.setFont(font);
        displayFrameRate.setPosition(sf::Vector2f(0, 0));
    }
}

void FrameRate::Update(double deltaTime)
{
    timer += deltaTime;

    if (timer >= 100.0f)
    {
        double fps = 1000.0f / deltaTime;

        std::string frameRate =
            std::to_string((int)fps);

        displayFrameRate.setString(frameRate);

        timer = 0;
    }
}

void FrameRate::Draw(sf::RenderWindow& window)
{
    window.draw(displayFrameRate);
}