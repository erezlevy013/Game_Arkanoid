#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "MoveShape.hpp"

namespace h72{


Ball::Ball(float a_size, sf::Color a_color, sf::Vector2f a_startPosition, sf::Vector2f a_circleSpeed)
: m_size(a_size)
, m_color(a_color)
, m_startPosition(a_startPosition)
, m_circleSpeed(a_circleSpeed)
, m_circlePosition(a_startPosition)
{
    sf::CircleShape circle(m_size);
    circle.setFillColor(m_color);
    circle.setPosition(m_startPosition);
    m_circle = circle;
}

void Ball::Move(float a_x, float a_y)
{
    m_circlePosition.x += m_circleSpeed.x * a_x;
    m_circlePosition.y += m_circleSpeed.y * a_y;  
    m_circle.setPosition(m_circlePosition);
}

void Ball::Restart()
{
    if(m_circleSpeed.x < 0){
        SetPositionX(-1);
    }
    if(m_circleSpeed.y < 0){
        SetPositionY(-1);
    }
    m_circle.setPosition(m_startPosition);
    m_circlePosition = m_startPosition; 
}

bool Ball::IsCollided(sf::Vector2f a_position)
{
    return m_circle.getGlobalBounds().contains(a_position);
}

sf::CircleShape Ball::GetShape() const
{
    return m_circle;
}

sf::Vector2f Ball::GetPosition() const
{
    return m_circlePosition;
}

float Ball::GetSize() const
{
    return m_size;
}

void Ball::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_circle.setFillColor(m_color);
}

void Ball::SetPositionX(float a_x)
{
    m_circleSpeed.x *= a_x;
    m_circlePosition.x += m_circleSpeed.x;
    m_circle.setPosition(m_circlePosition);
}

void Ball::SetPositionY(float a_y)
{
    m_circleSpeed.y *= a_y;
    m_circlePosition.y += m_circleSpeed.y;
    m_circle.setPosition(m_circlePosition);
}

void Ball::SetSpeed(sf::Vector2f a_speed)
{
    m_circleSpeed = a_speed;
}

}
