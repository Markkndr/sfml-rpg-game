#pragma once

#include "Entity.h"

class Entity;

class Player :
    public Entity
{
private:
    //Variables
    bool attacking;
    
    //Initializer
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();

    //Functions
    void loseHp(const int hp);
    void gainHp(const int hp);
    void gainExp(const int exp);
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

