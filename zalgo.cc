#include "zalgo.h"

#include <stdlib.h>
#include <string>
#include <time.h>

Zalgo::Zalgo()
{

}

Zalgo::~Zalgo()
{

}

std::string Zalgo::getDiacritic(int position, int repeatCount)
{
    std::string glyphWithDiacritic = "";
    srand(time(NULL));

    if(position == 0)
    {
        for (int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->ABOVE_DIACRITICS[rand() % 50];
        }
    }
    else if(position == 1)
    {
        for (int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->MIDDLE_DIACRITICS[rand() % 23];
        }
    }
    else if(position == 3)
    {
        for(int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->BELOW_DIACRITICS[rand() % 40];
        }
    }

    return glyphWithDiacritic;
}

std::string Zalgo::generateLine(std::string input, int aboveCount, int middleCount, int belowCount)
{

    std::string zalgoLine = "";

    for (int i = 0; i < input.length(); i++)
    {
        zalgoLine += input[i];
        zalgoLine += getDiacritic(0, aboveCount);
        zalgoLine += getDiacritic(1, middleCount);
        zalgoLine += getDiacritic(3, belowCount);
    }
    return zalgoLine;
}