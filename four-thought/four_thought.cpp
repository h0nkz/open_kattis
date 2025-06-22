#include <unordered_map>
#include <string>
#include <iostream>

/*
    https://open.kattis.com/problems/4thought
*/

const char operators[] = {'+', '-', '*','/'};
std::unordered_map<int, std::string> numMap{};
const int MAX_COMBINATIONS = 4 * 4 * 4;
int a = 0;
int b = 0;
int c = 0;

int calculate(int i, int value, char combination[])
{
    if(i == 3) return value;
    int toReturn = 0;

    switch (combination[i++])
    {
    case '+':
        toReturn = value + calculate(i, 4, combination);
        break;
    case '-':
        toReturn = value + calculate(i, -4, combination);
        break;
    case '*':
        toReturn = calculate(i, value * 4, combination);
        break;        
    case '/':
        toReturn = calculate(i, value / 4, combination);
        break;
    }
    
    return toReturn;
}

int getValue(char combination[])
{
    return calculate(0, 4, combination);
}

std::string makeString(char combination[], int value)
{
    std::string toReturn{};
    for(int i = 0; i < 3; i++)
    {
        toReturn.push_back('4');
        toReturn.push_back(' ');
        toReturn.push_back(combination[i]);
        toReturn.push_back(' ');
    }

    toReturn.push_back('4');
    toReturn.push_back(' ');
    toReturn.push_back('='); // equal sign
    toReturn.push_back(' ');
    return toReturn;
}

std::string tryCombinations(int value)
{
    char combination[3];

    for(; a < 4; a++)
    {
        for(; b < 4; b++)
        {
            for(; c < 4; c++)
            {
                combination[0] = operators[a]; 
                combination[1] = operators[b];
                combination[2] = operators[c];

                int keyValue = getValue(combination);
                auto comboString = makeString(combination, keyValue);
                numMap.insert_or_assign(keyValue, comboString);
                if(value == keyValue) return comboString;
            }
        }
    }

    return std::string{""};
}

int main()
{
    char combination[3];

    for(int a = 0; a < 4; a++)
    {
        for(int b = 0; b < 4; b++)
        {
            for(int c = 0; c < 4; c++)
            {
                combination[0] = operators[a]; 
                combination[1] = operators[b];
                combination[2] = operators[c];

                int keyValue = getValue(combination);
                numMap.insert_or_assign(keyValue, makeString(combination, keyValue));
            }
        }
    }
    
    int m, in;
    std::cin >> m;

    int value;
    for(int i = 0; i < m; i++)
    {
        std::cin >> value;

        if(auto search = numMap.find(value); search != numMap.end())
        {
            std::cout << search->second << value << std::endl;
        }
        else if(auto combination = tryCombinations(value); !combination.empty())
        {
            std::cout << combination << value << std::endl;
        }
        else{
            std::cout << "no solution" << std::endl;
        }
    }
}