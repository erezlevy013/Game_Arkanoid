#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstddef> /* size_t*/
#include <SFML/Graphics.hpp>

namespace h72{

class Board
{
public:
    explicit Board(size_t a_width, size_t a_height, sf::Color a_color);
    ~Board() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    sf::RectangleShape GetShape() const;

    void SetColor(sf::Color a_color);

private:
    size_t m_width;
    size_t m_height;
    sf::Color m_color;
    sf::RectangleShape m_rect;
};

}

#endif
