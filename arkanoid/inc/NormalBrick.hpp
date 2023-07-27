#ifndef NORMAL_BRICK_HPP
#define NORMAL_BRICK_HPP

#include <SFML/Graphics.hpp>
#include "Brick.hpp"

namespace h72{

class NormalBrick : public Brick
{
public:
    explicit NormalBrick(sf::Vector2f a_size, sf::Color a_color, sf::Vector2f a_Position);
    ~NormalBrick() = default;

    bool ShouldDelete() override;
    bool IsCollided (sf::Vector2f a_position) override;
    void Hit()override;

    sf::Vector2f GetPosition() const override;
    sf::RectangleShape GetShape() const override;
    sf::Vector2f GetSize() const override;
    std::shared_ptr<Brick> Clone() const override;

    void SetColor(sf::Color a_color);
    
private:
    sf::Vector2f m_size;
    sf::Color m_color;
    sf::Vector2f m_position;
    sf::RectangleShape m_brick;
    unsigned int m_maxHits = 1;
    bool m_flag = false;
};

}

#endif
