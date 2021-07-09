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

std::string Zalgo::getDiacritic(int position)
{
    std::string glyphWithDiacritic = "";

    if (position == 0)
    {
        glyphWithDiacritic = this->ABOVE_DIACRITICS[rand() % ABOVE_DIACRITICS_SIZE];
    }
    else if (position == 1)
    {
        glyphWithDiacritic = this->MIDDLE_DIACRITICS[rand() % MIDDLE_DIACRITICS_SIZE];
    }
    else if (position == 3)
    {
        glyphWithDiacritic = this->BELOW_DIACRITICS[rand() % BELOW_DIACRITICS_SIZE];
    }

    return glyphWithDiacritic;
}

std::string Zalgo::generateLine(std::string input, int &aboveCount, int &middleCount, int &belowCount, int &flag)
{
    if (flag < 0)
    {
        aboveCount = Zalgo::randomCountGenerator(aboveCount);
        middleCount = Zalgo::randomCountGenerator(middleCount);
        belowCount = Zalgo::randomCountGenerator(belowCount);
    }
    else
    {
        if (aboveCount == -1)
            aboveCount = Zalgo::randomCountGenerator(aboveCount);
        if (middleCount == -1)
            middleCount = Zalgo::randomCountGenerator(middleCount);
        if (belowCount == -1)
            belowCount = Zalgo::randomCountGenerator(belowCount);
    }

    std::string zalgoLine = "";

    for (int i = 0; (unsigned)i < input.length(); i++)
    {
        zalgoLine += input[i];

        for (int i = 0; i < aboveCount; i++)
            zalgoLine += getDiacritic(0);

        for (int i = 0; i < middleCount; i++)
            zalgoLine += getDiacritic(1);

        for (int i = 0; i < belowCount; i++)
            zalgoLine += getDiacritic(3);
    }
    return zalgoLine;
}

std::vector<int> Zalgo::argumentParser(std::string input)
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

int Zalgo::randomCountGenerator(int &input)
{

    if (input == -1)
        return (rand() % 100 + 1);

    if (input == -10)
        return (rand() % 10 + 1);

    if (input == -100)
        return (rand() % 1000 + 1);

    return 0;
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    srand(time(NULL));

    if (argc < 2 || argc > 2)
    {

        std::cout << "Wrong usage" << std::endl;
        return 1;
    }

    int aboveCount = 0;
    int middleCount = 0;
    int belowCount = 0;
    int flag = -1;

    Zalgo zalgo;

    if (std::regex_match(argv[1], std::regex("(^(\\d{1,}|(random))-(\\d{1,}|(random))-(\\d{1,}|(random)))|(^--random)|(^-r)")))
    {
        if (std::regex_match(argv[1], std::regex("^(\\d{1,}|(random))-(\\d{1,}|(random))-(\\d{1,}|(random))")))
        {
            std::vector<int> arguments = zalgo.argumentParser(argv[1]);
            aboveCount = arguments[0];
            middleCount = arguments[1];
            belowCount = arguments[2];
            flag = 0;
        }
        else if (std::regex_match(argv[1], std::regex("^-r")))
        {
            aboveCount = middleCount = belowCount = flag = -10;
        }
        else
        {
            aboveCount = middleCount = belowCount = flag = -100;
        }
    }
    else
    {
        std::cout << "Wrong usage" << std::endl;
        return -1;
    }

    std::string inputLine;

    while (getline(std::cin, inputLine))
    {
        std::cout << zalgo.generateLine(inputLine, aboveCount, middleCount, belowCount, flag) << std::endl;
    }

    return 0;
}
