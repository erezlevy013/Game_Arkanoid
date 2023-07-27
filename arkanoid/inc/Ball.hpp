#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "MoveShape.hpp"

namespace h72{

class Ball : public MoveShape
{
public:
    explicit Ball(float a_size, sf::Color a_color, sf::Vector2f a_startPosition, sf::Vector2f a_circleSpeed);
    ~Ball() = default;

    void Move(float a_x, float a_y) override;
    void Restart();
    bool IsCollided(sf::Vector2f a_position);

    sf::CircleShape GetShape() const;
    sf::Vector2f GetPosition() const;
    float GetSize() const;

    void SetColor(sf::Color a_color);
    void SetPositionX(float a_x);
    void SetPositionY(float a_x);
    void SetSpeed(sf::Vector2f a_speed);


private:
    float m_size;
    sf::Color m_color;
    sf::Vector2f m_startPosition;
    sf::Vector2f m_circleSpeed;
    sf::Vector2f m_circlePosition;
    sf::CircleShape m_circle;
};

}

#endif
