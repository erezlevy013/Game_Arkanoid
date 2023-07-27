#include <SFML/Graphics.hpp>
#include "Bar.hpp"
#include "MoveShape.hpp"

namespace h72{


Bar::Bar(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_startPosition, sf::Vector2f a_barSpeed)
: m_size(a_size)
, m_color(a_color)
, m_startPosition(a_startPosition)
, m_barSpeed(a_barSpeed)
, m_barPosition(a_startPosition)
{
    sf::RectangleShape bar;
    bar.setFillColor(m_color);
    bar.setSize(m_size);
    bar.setPosition(m_startPosition);
    m_bar = bar;
}

void Bar::Move(float a_x, float a_y)
{
    m_barPosition.x += m_barSpeed.x * a_x; 
    m_bar.setPosition(m_barPosition);
}

void Bar::Restart()
{
    m_bar.setPosition(m_startPosition);
    m_barPosition = m_startPosition;
}

bool Bar::IsCollided(sf::Vector2f a_position)
{
    return m_bar.getGlobalBounds().contains(a_position);
}

sf::RectangleShape Bar::GetShape() const
{
    return m_bar;
}

sf::Vector2f Bar::GetPosition() const
{
    return m_barPosition;
}

sf::Vector2f Bar::GetSize() const
{
    return m_size;
}

void Bar::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_bar.setFillColor(m_color);
}

void Bar::SetSpeed(sf::Vector2f a_speed)
{
    m_barSpeed = a_speed;
}

}