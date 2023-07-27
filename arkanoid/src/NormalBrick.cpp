#include <SFML/Graphics.hpp>
#include "NormalBrick.hpp"

namespace h72{

NormalBrick::NormalBrick(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_position)
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

bool NormalBrick::ShouldDelete()
{
    return m_maxHits == 0;
}

bool NormalBrick::IsCollided (sf::Vector2f a_position)
{
    return m_brick.getGlobalBounds().contains(a_position);
}

void NormalBrick::Hit()
{
    m_maxHits--;
}

sf::Vector2f NormalBrick::GetPosition() const
{
    return m_position;
}

sf::RectangleShape NormalBrick::GetShape() const
{
    return m_brick;
}

sf::Vector2f NormalBrick::GetSize() const
{
    return m_size;
}

std::shared_ptr<Brick> NormalBrick::Clone() const
{
    return std::make_shared<NormalBrick>(*this);
}

void NormalBrick::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_brick.setFillColor(m_color);
}

}
