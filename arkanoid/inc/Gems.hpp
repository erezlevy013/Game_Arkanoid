#ifndef GEMS_HPP
#define GEMS_HPP

#include <SFML/Graphics.hpp>
#include "MoveShape.hpp"

namespace h72{

class Gems : public MoveShape
{
public:
    enum Type{GOLD, RED, BLACK, PURPLE};

    Gems(std::string a_url, Type m_type, sf::Vector2f a_startPosition, sf::Vector2f a_speed);
    ~Gems() = default;

    void Move(float a_x, float a_y) override;
    void Restart();
    bool IsCollided(sf::Vector2f a_position);

    sf::Sprite GetShape() const;
    sf::Vector2f GetPosition() const;
    float GetWidth() const;
    float GetHeight() const;
    Type GetType() const;

    void SetSpeed(sf::Vector2f a_speed);
    bool ShouldDelete();
    void Hit();

private:
    Type m_type;    
    sf::Vector2f m_startPosition;
    sf::Vector2f m_speed;
    sf::Vector2f m_position;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    bool m_shoDelFlag = false;
};

}

#endif 
