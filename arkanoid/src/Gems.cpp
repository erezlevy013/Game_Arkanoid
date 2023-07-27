#include <SFML/Graphics.hpp>
#include "MoveShape.hpp"
#include "Gems.hpp"

namespace h72{

Gems::Gems(std::string a_url, Type a_type, sf::Vector2f a_startPosition, sf::Vector2f a_speed)
: m_type(a_type)
, m_startPosition(a_startPosition)
, m_speed(a_speed)
, m_position(a_startPosition)
{
    if(!m_texture.loadFromFile(a_url)){
        throw std::invalid_argument("Invalid png");
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_startPosition);
    m_sprite.setScale(sf::Vector2f(0.15f, 0.15f));
}
void Gems::Move(float a_x, float a_y) 
{
    m_position.y += m_speed.y * a_y;  
    m_sprite.setPosition(m_position);
}
void Gems::Restart()
{
    m_sprite.setPosition(m_startPosition);
    m_position = m_startPosition;
}

bool Gems::IsCollided(sf::Vector2f a_position)
{
    return m_sprite.getGlobalBounds().contains(a_position);;
}

sf::Sprite Gems::GetShape() const
{
    return m_sprite; 
}

sf::Vector2f Gems::GetPosition() const
{ 
    return m_position;
}

float Gems::GetWidth() const
{
    return m_sprite.getScale().x * 100;
}

float Gems::GetHeight() const
{
    return m_sprite.getScale().y * 100;
} 

Gems::Type Gems::GetType() const
{
    return m_type;
}

void Gems::SetSpeed(sf::Vector2f a_speed)
{
    m_speed = a_speed;
}

void Gems::Hit()
{
    m_shoDelFlag = true;
}

bool Gems::ShouldDelete()
{
    return m_shoDelFlag;
}

}
