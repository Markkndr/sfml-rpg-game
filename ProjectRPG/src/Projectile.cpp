#include "Projectile.h"
#include "Math.h"

Projectile::Projectile() :
    m_speed(0)
{
}

Projectile::~Projectile()
{
}

void Projectile::Initialize(const sf::Vector2f& position,const sf::Vector2f& target, float speed)
{
    m_speed = speed;
    rectangleShape.setSize(sf::Vector2f(20, 10));
    rectangleShape.setPosition(position);
    direction = Math::NormalizeVector(target - position);
}

void Projectile::Update(float deltaTime)
{
    rectangleShape.setPosition(rectangleShape.getPosition() + direction * m_speed * deltaTime);
}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(rectangleShape);
}