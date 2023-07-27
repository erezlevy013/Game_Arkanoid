#include <SFML/Graphics.hpp>
#include "UnbreakableBrick.hpp"

namespace h72{

UnbreakableBrick::UnbreakableBrick(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_position)
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

bool UnbreakableBrick::ShouldDelete()
{
    return m_flag;
}

bool UnbreakableBrick::IsCollided (sf::Vector2f a_position)
{
    return m_brick.getGlobalBounds().contains(a_position);
}

void UnbreakableBrick::Hit()
{
    m_flag = false; 
}

sf::Vector2f UnbreakableBrick::GetPosition() const
{
    return m_position;
}

sf::RectangleShape UnbreakableBrick::GetShape() const
{
    return m_brick;
}

sf::Vector2f UnbreakableBrick::GetSize() const
{
    return m_size;
}

std::shared_ptr<Brick> UnbreakableBrick::Clone() const
{
    return std::make_shared<UnbreakableBrick>(*this);
}

void UnbreakableBrick::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_brick.setFillColor(m_color);
}

}
