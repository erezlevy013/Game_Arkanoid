#include "Board.hpp"

namespace h72{

Board::Board(size_t a_width, size_t a_height, sf::Color a_color)
: m_width(a_width)
, m_height(a_height)
, m_color(a_color)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(m_width,m_height));
    rectangle.setFillColor(m_color);
    m_rect = rectangle;
}

size_t Board::GetWidth() const
{
    return m_width;
}

size_t Board::GetHeight() const
{
    return m_height;
}

sf::RectangleShape Board::GetShape() const
{
    return m_rect;
}

void Board::SetColor(sf::Color a_color)
{
    m_color = a_color;
    m_rect.setFillColor(m_color);
}

}
