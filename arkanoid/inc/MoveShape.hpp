#ifndef MOVE_SHAPE_HPP
#define MOVE_SHAPE_HPP

namespace h72{

class MoveShape
{
public:
    virtual ~MoveShape() = default;
    virtual void Move(float a_x, float a_y) = 0;
    virtual bool IsCollided(sf::Vector2f a_position) = 0;
};

}

#endif