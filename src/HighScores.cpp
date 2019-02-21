// #define _CRT_SECURE_NO_WARNINGS

#include "HighScores.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>


Score::Score(const char* n, int sc, time_t t)
    : score(sc), date(t)
{
#ifdef _MSC_VER                         // for MSVS 2017
	strcpy_s(name, sizeof name, n);
#else
    std::strcpy(name,n);
#endif
}


bool Score::operator<(const Score& obj) const
{
    return score > obj.score;  // display in reverse order
}

std::string Score::getDateAsString() const
{
#ifdef _MSC_VER                         // for MSVS 2017
	tm tm_buffer;
	localtime_s(&tm_buffer, &date);
	std::string datestring = std::to_string(tm_buffer.tm_mon + 1);
	datestring += '/';
	datestring += std::to_string(tm_buffer.tm_mday);
	datestring += '/';
	datestring += std::to_string((tm_buffer.tm_year + 1900) % 100);
#else
	tm* ptr2tm = localtime(&date);
	std::string datestring = std::to_string(ptr2tm->tm_mon + 1);
	datestring += '/';
	datestring += std::to_string(ptr2tm->tm_mday);
	datestring += '/';
	datestring += std::to_string((ptr2tm->tm_year + 1900) % 100);
#endif
	return datestring;
}

std::ostream& operator<<(std::ostream& out, const Score& obj)
{
    out << std::left << std::setw(16) << obj.name
        << std::right << std::setw(4) << obj.score
        << std::setw(12) << obj.getDateAsString() << std::endl;
    return out;
}

////////////////  HighScores functions ////////////////////

std::string HighScores::HighScoresFilename = "../highscores.bin";

HighScores::HighScores()
: highScores(), highScoresFileExists(true)
{
    std::ifstream fin(HighScoresFilename,std::ios_base::binary);
    if (!fin)
    {
        std::cout << "Can't find high scores file, " << HighScoresFilename << ".  I'll create a new one." << std::endl;
        highScoresFileExists = false;
    }
    else
    {
        Score temp;
        while (fin.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
        {
            highScores.insert(temp);
        }
        fin.close();
    }
}

void HighScores::updateHighScores(const Score& obj)
{
    highScores.insert(obj);
    if (highScores.size() > 10)
    {
        highScores.erase(--highScores.end());
    }
}


void HighScores::WriteHighScoresFile()
{
    std::ofstream fout(HighScoresFilename,std::ios_base::binary);

    auto count = 0;
    for (auto it = highScores.cbegin(); it != highScores.cend(); ++it, ++count )
    {
        if (count == 10)
            break;
        fout.write(reinterpret_cast<const char*>(&*it),sizeof(*it));
    }
    fout.close();
    std::cout << "High scores file written" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const HighScores& scores)
{
    if (scores.highScores.size() < 1)
        out << "No high scores recorded" << std::endl;
    else
    {
        out << "  *********** High Scores ***********" << std::endl << std::endl;
        out << "     Name           Score    Date" << std::endl;
        auto count = 1;
        for (auto it = scores.highScores.cbegin(); it != scores.highScores.cend(); ++it, ++count )
        {
            if (count == 11)
                break;
            out << std::setw(3) << count << "  " << *it;
        }
    }
    return out;
}
