#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Brick.hpp"

namespace h72{

class Level
{
public:
    explicit Level(std::string a_filename);
    ~Level() = default;

    Level& operator=(Level const& a_level);

    std::vector<std::shared_ptr<Brick>> GetBricks() const;
    sf::Vector2f GetBallSpeed() const;
    sf::Vector2f GetBarSpeed() const;
    unsigned short GetLevel() const;
    unsigned int GetTopScore() const; 

    bool CheckBallCollided(sf::Vector2f a_position, float a_size, int& a_xPos, int& a_yPos);
    void LevelDeleteBricks();
    void Draw(sf::RenderWindow& a_window);
private:
    void CreateBrick(std::string a_infoLine[]);
    bool CheckCollided(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size, int& a_xPos, int& a_yPos);
    bool CheckMidTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckMidDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckMidLeft(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckMidRight(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckRightTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckLeftTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckLeftDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);
    bool CheckRightDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size);

private:

    std::vector<std::shared_ptr<Brick>> m_bricks;
    sf::Vector2f m_ballSpeed;
    sf::Vector2f m_barSpeed;
    unsigned short m_level;
    unsigned int m_topScore;
};

}

#endif 
