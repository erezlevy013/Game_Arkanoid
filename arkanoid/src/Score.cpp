#include "Score.hpp"

namespace h72{

unsigned int Score::GetScore() const
{
    return m_score;
}

void Score::SetScore(unsigned int a_plus)
{
    m_score += a_plus;
}

void Score::SetZero()
{
    m_score = 0;
}

}
