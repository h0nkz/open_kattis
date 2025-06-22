#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>

/*
    https://open.kattis.com/problems/classy
*/

struct Person
{
    std::string name;
    long value;
};

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

    for(int i = 1; i <= classStack.size(); i++)
    {

    }




}

int main()
{
    int cases, persons;

    std::cin >> cases;

    for(int i = 0; i < cases; i++)
    {
        std::cin >> persons;
        std::vector<Person> personVector{};
        for(int j = 0; j < persons; j++)
        {
            Person person{};
            std::string classString{};
            std::cin >> person.name;
            std::cin >> classString;
            person.value = parse_class_value(classString);


        }

    }
}