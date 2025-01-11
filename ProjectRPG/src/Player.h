#pragma once

#include "Entity.h"

class Entity;

class Player :
    public Entity
{
private:
    //Variables
    bool attacking;
    sf::CircleShape spellHitbox;
    
    //Initializer
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    bool getAttacking();

    //Functions
    void loseHp(const int hp);
    void gainHp(const int hp);
    void gainExp(const int exp);
    void updateAttack(const float& dt, sf::Vector2f& mousePosView);
    void updateAnimation(const float& dt);
    virtual void update(const float& dt, sf::Vector2f& mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

