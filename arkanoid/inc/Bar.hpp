#ifndef BAR_HPP
#define BAR_HPP

#include <SFML/Graphics.hpp>
#include "MoveShape.hpp"

namespace h72{

class Bar :public MoveShape
{
public:
    explicit Bar(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_startPosition, sf::Vector2f a_barSpeed);
    ~Bar() = default;

    void Move(float a_x, float a_y = 0);
    void Restart();
    bool IsCollided(sf::Vector2f a_position);
    
    sf::RectangleShape GetShape() const;
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize() const;

    void SetColor(sf::Color a_color);
    void SetSpeed(sf::Vector2f a_speed);

private:
    sf::Vector2f m_size;
    sf::Color m_color;
    sf::Vector2f m_startPosition;
    sf::Vector2f m_barSpeed;
    sf::Vector2f m_barPosition;
    sf::RectangleShape m_bar;
};

}



#endif
