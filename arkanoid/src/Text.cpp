#include <SFML/Graphics.hpp>
#include <iostream>

#include "Text.hpp"

namespace h72{

Text::Text(std::string a_font, sf::Color a_color, unsigned int a_size, sf::Vector2f a_position )
: m_color(a_color)
, m_size(a_size)
, m_position(a_position) 
{
    if(!m_font.loadFromFile(a_font)){
        throw std::runtime_error("Failed font!");
    }
    m_text.setFont(m_font);
    m_text.setCharacterSize(m_size);
    m_text.setFillColor(m_color);
    m_text.setPosition(m_position);
}

sf::Text Text::GetOb()
{
    return m_text;
}

void Text::SetStr(std::string a_str)
{
    m_text.setString(a_str);
}

std::string Text::GetStr()
{
    std::string str;
    std::cin >> str;  
    return str;  
}

void Text::SetPosition(sf::Vector2f a_position)
{
    m_text.setPosition(a_position);
}


}
