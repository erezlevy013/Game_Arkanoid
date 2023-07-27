#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>

namespace h72{

class Text
{
public:
    explicit Text(std::string a_font, sf::Color a_color, unsigned int a_size, sf::Vector2f a_position);
    ~Text() = default;

    sf::Text GetOb();
    void SetStr(std::string a_str);
    void SetPosition(sf::Vector2f a_position);

    std::string GetStr();
private:
    sf::Font m_font;
    sf::Color m_color;
    unsigned int m_size;
    sf::Vector2f m_position;
    sf::Text m_text;    
};

}

#endif
