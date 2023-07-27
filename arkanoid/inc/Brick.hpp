#ifndef BRICK_HPP
#define BRICK_HPP

#include <SFML/Graphics.hpp>
#include <memory>
namespace h72{

class Brick
{
public:
    virtual ~Brick() = default;
    virtual bool ShouldDelete() = 0;
    virtual bool IsCollided (sf::Vector2f a_position) = 0;
    virtual void Hit() = 0;

    virtual sf::Vector2f GetPosition() const = 0;
    virtual sf::RectangleShape GetShape() const = 0;
    virtual sf::Vector2f GetSize() const = 0;
    virtual std::shared_ptr<Brick> Clone() const = 0;

};

}

#endif
