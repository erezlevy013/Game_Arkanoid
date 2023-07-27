#ifndef SCORE_HPP
#define SCORE_HPP

namespace h72{

class Score
{
public:
    explicit Score() = default;
    ~Score() = default;

    unsigned int GetScore() const;
    void SetScore(unsigned int a_plus);
    void SetZero();

private:
    unsigned int m_score = 0; 
};

}

#endif
