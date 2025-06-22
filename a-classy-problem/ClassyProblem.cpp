#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>
/*
    https://open.kattis.com/problems/classy
*/

std::unordered_map<std::string, long> classValueMap{};

struct Person
{
    std::string name;
    long value;

    /*
        Since the map sorts ascending, we make the operator
        oposite so that it gets sorted descending for the value,
        but keep less than for the lexicographical comparison
    */
    bool operator<(const Person& other) const
    {
        if(value == other.value)
        {
            return name < other.name;
        }

        return value > other.value;
    }
};

int get_char_value(char c)
{
    switch (c)
    {
    case 'u':
        return 3;
    case 'm':
        return 2;
    case 'l':
        return 1;
    }

    return -1;
}

long parse_class_value(std::string classString)
{
    std::stack<char> classStack{};

    classStack.push(classString[0]);

    for(int i = 0; i < classString.length(); i++)
    {
        /*
            If it's a dash, push the first letter to the stack
            and skip five letters (lowest word length)
        */
        if(classString[i] == '-')
        {
            classStack.push(classString[i + 1]);
            i += 5;
        }   
    }

    long baseValue = 2222222222; // All middle, as middle is default
    int exp = 10 - classStack.size(); // Get the exponent for modulus by subracting size
    baseValue = baseValue % (long)pow(10, exp); // Remainder is the values that should be default

    int stackSize = classStack.size();
    for(int i = 1; i <= stackSize; i++)
    {
        baseValue += get_char_value(classStack.top()) * pow(10, 10 - i);
        classStack.pop();
    }

    classValueMap.insert_or_assign(classString, baseValue);

    return baseValue;
}

std::vector<std::string> split(const char *str, char c = ' ')
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}

int main()
{
    int cases, persons;
    std::string casesString, personsString;
    std::string breakLine(30, '=');
    std::getline(std::cin, casesString);
    cases = stoi(casesString);
    std::vector<std::map<Person, std::string>> mapVector{};

    for(int i = 0; i < cases; i++)
    {
        std::getline(std::cin, personsString);
        persons = stoi(personsString);
        std::map<Person, std::string> personMap;
        std::string temp{};
        for(int j = 0; j < persons; j++)
        {
            std::getline(std::cin, temp);
            std::stringstream ss(temp);
            std::vector<std::string> tokens;
            std::string token;

            while (std::getline(ss, token, ' ')) { // using space as delimiter
                tokens.push_back(token);
            }
            
            Person person{};
            std::string classString{};
            person.name = tokens[0].erase(tokens[0].size() - 1);
            classString = tokens[1];

            if(auto search = classValueMap.find(classString); search != classValueMap.end())
            {
                person.value = search->second;
            }
            else
            {
                person.value = parse_class_value(classString);
            }

            personMap.emplace(std::make_pair(person, person.name));
        }
        mapVector.push_back(personMap);
    }

    for(auto ptr = mapVector.begin(); ptr != mapVector.end(); ptr++)
    {
        for(const auto& [key,value] : *ptr)
        {
            std::cout << value << std::endl;
        }
        
        std::cout << breakLine << std::endl;
    }
}