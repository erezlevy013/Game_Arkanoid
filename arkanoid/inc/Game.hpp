#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Board.hpp"
#include "Ball.hpp"
#include "Bar.hpp"
#include "Brick.hpp"
#include "NormalBrick.hpp"
#include "Level.hpp"
#include "Score.hpp"
#include "Text.hpp"
#include "Gems.hpp"

namespace h72{

class Game
{
public:
    explicit Game();
    ~Game() = default;

    void Run();

private:
    void WindosEvent(bool& a_pause);
    void CheckBallCollidedBricks();
    void CheckLevelUp();
    void CheckGems();
    void CheckGemsDelete();
    void WindowsDraw(bool& a_pause);
    void Restart();
    void LevelUp();
    void GameOver();
    void PlaySound();
    void CheckLimitBoard();
    void CheckKeyPressed();
    void CheckBarCollided();
    void LoadFromFile();
    void SaveToFile();
    void checkTopScore(std::pair< int, std::string> a_pair);
    void PrintTopScore();
    void LoadGems();
    bool CheckGemsCollided(std::shared_ptr<Gems> a_gem);
    
private:
    sf::RenderWindow m_window;
    Board m_board;  
    Ball m_ball;  
    Bar m_bar;  
    Level m_level;
    Score m_score;
    Text m_text;
    std::vector<std::shared_ptr<Gems>> m_gems;
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;
    std::vector<std::pair<int, std::string>> m_data;
    bool m_flag = false;
    bool m_gameOver = false;
    unsigned short m_levelNumber = 1;
    unsigned short m_lives = 3;
};

}

#endif