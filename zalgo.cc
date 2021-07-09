#include "zalgo.h"

#include <stdlib.h>
#include <string>
#include <time.h>
#include <regex>
#include <bits/stdc++.h>

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

    if (position == 0)
    {
        for (int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->ABOVE_DIACRITICS[rand() % 50];
        }
    }
    else if (position == 1)
    {
        for (int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->MIDDLE_DIACRITICS[rand() % 23];
        }
    }
    else if (position == 3)
    {
        for (int i = 0; i < repeatCount; i++)
        {
            glyphWithDiacritic += this->BELOW_DIACRITICS[rand() % 40];
        }
    }

    return glyphWithDiacritic;
}

std::string Zalgo::generateLine(std::string input, int aboveCount, int middleCount, int belowCount)
{

    std::string zalgoLine = "";

    for (int i = 0; (unsigned)i < input.length(); i++)
    {
        zalgoLine += input[i];
        zalgoLine += getDiacritic(0, aboveCount);
        zalgoLine += getDiacritic(1, middleCount);
        zalgoLine += getDiacritic(3, belowCount);
    }
    return zalgoLine;
}

std::vector<int> argumentParser(std::string input)
{
    std::vector<int> argumentVector;
    std::string tempString = "";

    if (input == "--random" || input == "-r")
    {
        argumentVector.push_back(-1);
        return argumentVector;
    }

    for (int i = 0; (unsigned)i < input.length(); i++)
    {
        if (input[i] == '-')
        {
            if (tempString == "random")
            {
                argumentVector.push_back(-1);
            }
            else
            {
                argumentVector.push_back(stoi(tempString));
            }
            tempString = "";
            continue;
        }
        tempString += input[i];
    }
    if (tempString == "random")
    {
        argumentVector.push_back(-1);
    }
    else
    {
        argumentVector.push_back(stoi(tempString));
    }
    return argumentVector;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    if (argc < 2 || argc > 2)
    {
        std::cout << "Wrong usage" << std::endl;
        return 1;
    }

    int aboveCount = 0;
    int middleCount = 0;
    int belowCount = 0;

    if (std::regex_match(argv[1], std::regex("(^(\\d{1,}|(random))-(\\d{1,}|(random))-(\\d{1,}|(random)))|(^--random)|(^-r)")))
    {
        if (std::regex_match(argv[1], std::regex("^(\\d{1,}|(random))-(\\d{1,}|(random))-(\\d{1,}|(random))")))
        {
            std::vector<int> arguments = argumentParser(argv[1]);
            aboveCount = arguments[0];
            middleCount = arguments[1];
            belowCount = arguments[2];

        }
        else if (std::regex_match(argv[1], std::regex("^-r")))
        {
            aboveCount = middleCount = belowCount = -10;
        }
        else
        {
            aboveCount = middleCount = belowCount = -100;
        }

    }
    else
    {
        std::cout << "Wrong usage" << std::endl;
        return -1;
    }

    std::string inputLine;
    Zalgo zalgo;

    while(getline(std::cin, inputLine))
    {
        std::cout << zalgo.generateLine(inputLine, aboveCount, middleCount, belowCount) << std::endl;
    }

    return 0;
}
