#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <set>
#include <ctime>
#include <string>

class Score
{
    char name[16];
    int score;
    std::time_t date;
public:
    Score(const char* n = "no name", int sc = 0, std::time_t t = 0U);
    bool operator<(const Score& obj) const;
    std::string getDateAsString() const;
    friend std::ostream& operator<<(std::ostream& out, const Score& obj);
    Score& operator+=(int amount) { score += amount; return *this; }
    operator int() const { return score; }
};

class HighScores
{
public:
    HighScores();
    void WriteHighScoresFile();
    void updateHighScores(const Score&);
protected:

private:
    std::multiset<Score> highScores;
    bool highScoresFileExists;
    static std::string HighScoresFilename;
    friend std::ostream& operator<<(std::ostream& out, const HighScores& scores);

};


#endif // HIGH_SCORES_H
