#pragma once

#include "Entity.h"

class Player :
    public Entity
{
private:
    //Variables
    
    //Initializer
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Functions
};

