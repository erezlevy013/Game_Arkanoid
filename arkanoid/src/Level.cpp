#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "Level.hpp"
#include "Brick.hpp"
#include "NormalBrick.hpp"
#include "HardBrick.hpp"
#include "UnbreakableBrick.hpp"

namespace h72{

Level::Level(std::string a_filename)
{
    std::ifstream myFile(a_filename);
    if(!myFile){
        throw std::invalid_argument("Invalid File");
    }
    std::string str;
    myFile >> str;
    m_level = std::stoi(str);
    myFile >> str;
    m_topScore = std::stoi(str);
    std::string line[8];
    size_t i = 0;
    while(!myFile.eof()){
        myFile >> line[i++];
        if(i == 8){
            CreateBrick(line);
            i = 0;
        }
    }        
    myFile.close();
}

Level& Level::operator=(Level const& a_level)
{
    m_ballSpeed = a_level.m_ballSpeed;
    m_barSpeed = a_level.m_barSpeed;
    m_level = a_level.m_level;
    m_topScore = a_level.m_topScore;
    m_bricks.reserve(a_level.m_bricks.size());
    for(const auto& brick : m_bricks){
        m_bricks.pop_back();
        brick.get();
    }
    for(const auto& brick : a_level.m_bricks){
        m_bricks.push_back(brick->Clone());
    }
    return *this;

}

std::vector<std::shared_ptr<Brick>> Level::GetBricks() const
{
    return m_bricks;
}

sf::Vector2f Level::GetBallSpeed() const
{
    return m_ballSpeed;
}

sf::Vector2f Level::GetBarSpeed() const
{
    return m_barSpeed;
}

unsigned short Level::GetLevel() const
{
    return m_level;
}

unsigned int Level::GetTopScore() const
{
    return m_topScore;
}

void Level::CreateBrick(std::string a_infoLine[])
{
    float xSize = std::stof(a_infoLine[1]); 
    float ySize = std::stof(a_infoLine[2]);
    int rColor =  std::stoi(a_infoLine[3]);
    int gColor =  std::stoi(a_infoLine[4]);
    int bColor =  std::stoi(a_infoLine[5]);
    float xPos = std::stof(a_infoLine[6]); 
    float yPos = std::stof(a_infoLine[7]);

    if(a_infoLine[0] == "NormalBrick"){
        m_bricks.push_back(std::make_shared<NormalBrick>( sf::Vector2f(xSize,ySize), sf::Color(rColor,gColor,bColor), sf::Vector2f(xPos,yPos)));
    }
    if(a_infoLine[0] == "HardBrick"){
        m_bricks.push_back(std::make_shared<HardBrick>( sf::Vector2f(xSize,ySize), sf::Color(rColor,gColor,bColor), sf::Vector2f(xPos,yPos)));
    }
    if(a_infoLine[0] == "UnbreakableBrick"){
        m_bricks.push_back(std::make_shared<UnbreakableBrick>( sf::Vector2f(xSize,ySize), sf::Color(rColor,gColor,bColor), sf::Vector2f(xPos,yPos)));
    }
}

bool Level::CheckBallCollided(sf::Vector2f a_position, float a_size, int& a_xpos, int& a_yPos)
{
    for(auto& brick : m_bricks){
        if(CheckCollided(brick, a_position, a_size, a_xpos, a_yPos)){
            brick->Hit();
            return true; 
        }
    }
    return false; 
}

void Level::LevelDeleteBricks()
{
    m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(), [](auto &brick){
        if(brick->ShouldDelete()){
            //delete brick;
            //brick = nullptr;
            //std::cout<<brick.use_count()<<std::endl;
            //brick.release();

            return true;
        }
        return false;
    }), m_bricks.end());
}

bool Level::CheckCollided(std::shared_ptr<Brick> a_brick, sf::Vector2f a_position, float a_size, int& a_xPos, int& a_yPos)
{
    if(CheckMidTop(a_brick, a_position, a_size) || CheckMidDown(a_brick, a_position, a_size)){
        a_yPos = -1;
        return true;
    }else if(CheckMidLeft(a_brick, a_position, a_size) || CheckMidRight(a_brick, a_position, a_size)){
        a_xPos = -1;
        return true; 
    }else if(CheckRightTop(a_brick, a_position, a_size) ||CheckLeftTop(a_brick, a_position, a_size) || CheckLeftDown(a_brick, a_position, a_size) || CheckRightDown(a_brick, a_position, a_size) ){
        a_xPos = -1;
        a_yPos = -1;
        return true;
    }
    return false;
}

void Level::Draw(sf::RenderWindow& a_window)
{
    for(auto& brick : m_bricks){
        a_window.draw(brick->GetShape());
    }
}

bool Level::CheckMidTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x + a_size ,a_pos.y))){
        return true;
    }
    return false;
}
bool Level::CheckMidDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x + a_size, a_pos.y + a_size*2))){
        return true;
    }
    return false;
}
bool Level::CheckMidLeft(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x , a_pos.y + a_size))){
        return true;
    }
    return false;   
}
bool Level::CheckMidRight(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x + a_size*2, a_pos.y + a_size))){
        return true;
    }
    return false; 
}
bool Level::CheckRightTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x + a_size*2, a_pos.y))){
        return true;
    }
    return false;
}
bool Level::CheckLeftTop(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x , a_pos.y))){
        return true;
    }
    return false;
}
bool Level::CheckLeftDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x , a_pos.y + a_size*2))){
       return true; 
    }
    return false;
}
bool Level::CheckRightDown(std::shared_ptr<Brick> a_brick, sf::Vector2f a_pos, float a_size)
{
    if(a_brick->IsCollided(sf::Vector2f(a_pos.x + a_size*2, a_pos.y + a_size*2))){
        return true;
    }
    return false;
}

}
