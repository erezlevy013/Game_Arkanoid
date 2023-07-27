#include <SFML/Graphics.hpp>
#include "HardBrick.hpp"

namespace h72{

HardBrick::HardBrick(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_position)
: m_size(a_size)
, m_color(a_color)
, m_position(a_position)
{
    sf::RectangleShape brick;
    brick.setFillColor(m_color);
    brick.setSize(m_size);
    brick.setPosition(m_position);
    m_brick = brick;
}

bool HardBrick::ShouldDelete()
{
    return m_flag;
}

bool HardBrick::IsCollided (sf::Vector2f a_position)
{
    return m_brick.getGlobalBounds().contains(a_position);
}

void HardBrick::Hit()
{
    if(m_maxHits == 1){
        m_maxHits--;
        m_flag = true; 
    }
    m_maxHits--;
}

sf::Vector2f HardBrick::GetPosition() const
{
    return m_position;
}

sf::RectangleShape HardBrick::GetShape() const
{
    return m_brick;
}

sf::Vector2f HardBrick::GetSize() const 
{
   return m_size;
}

std::shared_ptr<Brick> HardBrick::Clone() const
{
    return std::make_shared<HardBrick>(*this);
}

void HardBrick::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_brick.setFillColor(m_color);
}

}