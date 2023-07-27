#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include <random>


#include "Game.hpp"
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

std::string str;

Game::Game()
: m_window(sf::VideoMode(500, 500), "Game!!!")
, m_board(500, 500,sf::Color(152,152,152))
, m_ball(10.f, sf::Color(0,235,234), sf::Vector2f((500/2)-10,455), sf::Vector2f(2,2))
, m_bar(sf::Vector2f(80,15), sf::Color(92,36,0), sf::Vector2f((500/2)-40,475), sf::Vector2f(2,2))
, m_level("../resources/level1.txt")
, m_score()
, m_text("../resources/serpent.ttf",sf::Color(0,0,0), 24, sf::Vector2f(55,10))
{
    m_window.setFramerateLimit(60);
    LoadFromFile();
    LoadGems();
    if (!m_buffer.loadFromFile("../resources/R2D2-yeah.wav")){
        throw std::invalid_argument("Invalid Sound");
    }
    m_sound.setBuffer(m_buffer);
}

void Game::Run()
{
    bool pause = true;
    
    while (m_window.isOpen()){
        
        WindosEvent(pause);
        if(pause && !m_gameOver){    
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                m_flag = true;
            }
            CheckLimitBoard();
            CheckKeyPressed();
            CheckBarCollided();
            CheckBallCollidedBricks();
            m_level.LevelDeleteBricks();
            CheckLevelUp();
            CheckGems();
            CheckGemsDelete();
            if(m_flag){   
                m_ball.Move(1,1);  
            }
        }
    
        WindowsDraw(pause);
    }
}


void Game::WindosEvent(bool& a_pause)
{
    sf::Event event;
    while (m_window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            SaveToFile();
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape){
                a_pause = !a_pause;
                m_text.SetStr("Pause");
            } 
            if(event.key.code == sf::Keyboard::Enter){
                checkTopScore({m_score.GetScore(),str});
                str = "";
                PrintTopScore();
                m_gameOver = false;
                Restart();
            }
        }else if(m_gameOver && event.type == sf::Event::TextEntered) {
            m_text.SetPosition(sf::Vector2f(100, 500/2));
            if (event.text.unicode < 128){
                str += static_cast<char>(event.text.unicode);
                m_text.SetStr("Enter your name: "+str);
            }     
        }    
    }
}

void Game::CheckBallCollidedBricks()
{
    int xPos = 1;
    int yPos = 1; 
    if(m_level.CheckBallCollided(sf::Vector2f(m_ball.GetPosition().x, m_ball.GetPosition().y), m_ball.GetSize(), xPos, yPos)){
        m_ball.SetPositionX(xPos);
        m_ball.SetPositionY(yPos);
        m_score.SetScore(10);
        PlaySound(); 
    }   
}

void Game::CheckLevelUp()
{
    if(m_score.GetScore() >= m_level.GetTopScore()){
        LoadGems();
        LevelUp();
    }
}

void Game::CheckGems()
{
    for(const auto& gem : m_gems){
        if(CheckGemsCollided(gem)){
            if(gem->GetType() == Gems::Type::GOLD){
                m_score.SetScore(5);
            }
        }
    }
}

void Game::CheckGemsDelete()
{
    m_gems.erase(std::remove_if(m_gems.begin(), m_gems.end(), [](auto &gem){
    if(gem->ShouldDelete()){
        return true;
    }
    return false;
    }), m_gems.end());
}

void Game::WindowsDraw(bool& a_pause)
{
    m_window.clear();
    m_window.draw(m_board.GetShape());
    m_window.draw(m_bar.GetShape());
    m_level.Draw(m_window);
        
    if(!m_gameOver && a_pause){
        m_text.SetStr("Score: " + std::to_string(m_score.GetScore()) + "  Level: " + std::to_string(m_levelNumber) + "  Lives: " + std::to_string(m_lives));
    }
        
    for(auto& gem : m_gems){
        m_window.draw(gem->GetShape());
        gem->Move(1,1); 
    }
    m_window.draw(m_text.GetOb());
    m_window.draw(m_ball.GetShape());
    m_window.display();
}

void Game::Restart()
{
    m_ball.Restart();
    m_ball.SetColor(sf::Color(0,235,234));
    m_ball.SetSpeed(sf::Vector2f(2,2));
    m_bar.Restart();
    m_bar.SetSpeed(sf::Vector2f(2,2));
    m_text.SetPosition(sf::Vector2f(55,10));
    m_board.SetColor(sf::Color(152,152,152));
    m_lives = 3;
    m_level = Level("../resources/level1.txt");
    std::cout<<"ASdasdasd"<<std::endl;
    m_score.SetZero();
    m_flag = false;
}

void Game::LevelUp()
{
    m_level = Level("../resources/level" + std::to_string(m_level.GetLevel()+1) + ".txt");
    std::cout<<m_level.GetLevel()<<std::endl;
    if(m_level.GetLevel() == 2){
        m_ball.SetColor(sf::Color(0,0,0));
        m_ball.SetSpeed(sf::Vector2f(3,3));
        m_bar.SetSpeed(sf::Vector2f(3,3));

    }else if(m_level.GetLevel() == 3){
        m_ball.SetColor(sf::Color(100,100,100));
        m_ball.SetSpeed(sf::Vector2f(4,4));
        m_bar.SetSpeed(sf::Vector2f(4,4));
    }
    // else if(m_levelNumber == 4){
    //     m_level = Level("../resources/level4.txt");
    //     Restart();
    //  }
    m_ball.Restart();
    m_bar.Restart();
    m_flag = false;

}

void Game::GameOver()
{
    m_gameOver = true;
    m_board.SetColor(sf::Color(148,0,11));
    m_text.SetStr("Game Over"); 
    m_text.SetPosition(sf::Vector2f(180, 500/2));    
}

void Game::PrintTopScore()
{
    unsigned short i = 0;
    for(auto& data : m_data){
        if(i < 10){
            str += std::to_string(data.first) + data.second;
        }else{
            break;
        }
    }
    str = "";
}

void Game::LoadGems()
{
    std::default_random_engine rand;
    std::uniform_int_distribution<int> rangeOfGems(5, 15);
    size_t sizeOfGems = rangeOfGems(rand);
    for(size_t i = 0; i < sizeOfGems; ++i){
        std::uniform_int_distribution<int> speedOfGem(1, 5);
        std::uniform_int_distribution<int> typeOfGem(0, 3);
        int speed = speedOfGem(rand);
        int type = typeOfGem(rand);
        std::string url;
        Gems::Type gt;
        if(type == 0){
            url = "../resources/gold.png";
            gt = Gems::Type::GOLD;
        }else if(type == 1){
            url = "../resources/red.png";
            gt = Gems::Type::RED;
        }else if(type == 2){
            url = "../resources/black.png";
            gt = Gems::Type::BLACK;
        }else{
            url = "../resources/purple.png";
            gt = Gems::Type::PURPLE;
        }
        //Gems *gem = new Gems(url, gt, sf::Vector2f((i * 100) % 500, 0), sf::Vector2f(speed, speed));
        m_gems.push_back(std::make_shared<Gems>(url, gt, sf::Vector2f((i * 100) % 500, 0), sf::Vector2f(speed, speed)));
    }
}

void Game::PlaySound()
{
    m_sound.play(); 
}

void Game::CheckLimitBoard()
{
    if(m_ball.GetPosition().x < 0 || m_ball.GetPosition().x > m_board.GetHeight() - m_ball.GetSize()*2){
        m_ball.SetPositionX(-1);
    }
    if(m_ball.GetPosition().y < 0){
        m_ball.SetPositionY(-1);
    }
    if(m_ball.GetPosition().y > m_board.GetHeight()){
        m_lives--;
        std::cout<< m_lives<<std::endl;
        if(!m_lives){
            GameOver();
        }
        m_ball.Restart();
        m_bar.Restart();
        m_flag = false;
    }
}

void Game::CheckKeyPressed()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_bar.GetPosition().x >= 0){
        m_bar.Move(-1);
        if(!m_flag){
            m_ball.Move(-1,0); 
        }  
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_bar.GetPosition().x <= m_board.GetHeight()- m_bar.GetSize().x){
        m_bar.Move(1);
        if(!m_flag){
            m_ball.Move(1,0); 
        } 
    }
}

void Game::CheckBarCollided()
{
    if(m_bar.IsCollided(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetSize(), m_ball.GetPosition().y + m_ball.GetSize()*2))){
        m_ball.SetPositionY(-1);
    }else if(m_bar.IsCollided(sf::Vector2f(m_ball.GetPosition().x , m_ball.GetPosition().y + m_ball.GetSize()*2))){
        m_ball.SetPositionX(-1);
        m_ball.SetPositionY(-1);
    }else if(m_bar.IsCollided(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetSize()*2 , m_ball.GetPosition().y + m_ball.GetSize()*2))){
        m_ball.SetPositionX(-1);
        m_ball.SetPositionY(-1);
    }else if(m_bar.IsCollided(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetSize()*2 , m_ball.GetPosition().y + m_ball.GetSize()))){
        m_ball.SetPositionX(-1);
    }else if(m_bar.IsCollided(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetSize() , m_ball.GetPosition().y + m_ball.GetSize()))){
        m_ball.SetPositionX(-1);
    }
}

bool Game::CheckGemsCollided(std::shared_ptr<Gems> a_gem)
{
    if(a_gem->GetPosition().y >= m_bar.GetPosition().y 
    && a_gem->GetPosition().y <= m_bar.GetPosition().y + m_bar.GetSize().y
    && a_gem->GetPosition().x >= m_bar.GetPosition().x
    && a_gem->GetPosition().x <= m_bar.GetPosition().x + m_bar.GetSize().x){
        a_gem->Hit();
        return true;
    }else if(a_gem->GetPosition().y >= m_bar.GetPosition().y 
    && a_gem->GetPosition().y <= m_bar.GetPosition().y + m_bar.GetSize().y
    && a_gem->GetPosition().x + a_gem->GetWidth() >= m_bar.GetPosition().x
    && a_gem->GetPosition().x + a_gem->GetWidth() <= m_bar.GetPosition().x + m_bar.GetSize().x){
        a_gem->Hit();
        return true;
    }
    return false;
}

void Game::LoadFromFile()
{
    std::ifstream myFile("../resources/file.txt");
    if(!myFile){
        throw std::invalid_argument("Invalid File");
    }
    while(!myFile.eof()){
        std::string myStr1;
        std::string myStr2;
        myFile >> myStr1;
        myFile >> myStr2;
        std::pair< int, std::string> p = {atoi( myStr1.c_str()), myStr2};
        m_data.push_back(p);
    }  
}

void Game::checkTopScore(std::pair< int, std::string> a_pair)
{
    m_data.push_back(a_pair);
    sort(m_data.begin(), m_data.end(), std::greater<std::pair<int,std::string>>());
}

void Game::SaveToFile()
{
    std::ofstream myFile("../resources/file.txt");
    if(!myFile){
        throw std::invalid_argument("Invalid File");
    }
    unsigned short i = 0;
    for(auto& data : m_data){
        if(i < 10){
            myFile << data.first << ' ' << data.second << std::endl;
        } else{
            break;
        }
        i++;
    }
}

}
