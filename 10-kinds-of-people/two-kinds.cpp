#include <iostream>
#include <vector>
#include <unordered_map>

/*
    https://open.kattis.com/problems/10kindsofpeople
*/

int rows, cols, cases;
char temp;
std::vector<std::vector<char>> matrix{};

std::unordered_map<char, std::string> peopleMap 
{
    {'0', "binary"},
    {'1', "decimal"}
};

std::unordered_map<std::string, char> memo;

int rowDir[] = { -1, 0, 1, 0 };
int colDir[] = { 0, 1, 0, -1 };

bool isValid(std::vector<std::vector<bool>>& visited, int row, int col)
{
    if(row < 0 || row >= rows || col < 0 || col >= cols)
        return false;
    
    if(visited[row][col])
        return false;
    
    return true;
}

std::string makeString(int startX, int startY, int currX, int currY)
{
    return std::to_string(startX) + "," + std::to_string(startY) + "," +
           std::to_string(currX) + "," + std::to_string(currY);
}

void save_path(int startX, int startY, int currX, int currY, char kindOfPeople)
{
    memo.insert_or_assign(makeString(startX, startY, currX, currY), kindOfPeople);
}

std::string find(const char kindOfPeople, int currX, int currY, int startX, int startY, int goalX, int goalY, std::vector<std::vector<bool>>& visited)
{
    if(!isValid(visited, currX, currY))
        return "";

    auto s = makeString(currX, currY, goalX, goalY);
    
    if(auto search = memo.find(s); search != memo.end())
    {
        return peopleMap[search->second];
    } 
    
    visited[currX][currY] = true;
    save_path(currX, currY, goalX, goalY, kindOfPeople);

    std::string toReturn = ""; 
    for(int i = 0; i < 4; i++)
    {
        int adjx = currX + rowDir[i];
        int adjy = currY + colDir[i];

        if(!isValid(visited, adjx, adjy))
        {    
            continue;
        }
        if((adjx == goalX) && (adjy == goalY))
        {
            return peopleMap.at(matrix[adjx][adjy]);
        }
        
        if(matrix[adjx][adjy] != kindOfPeople)
        {
            visited[adjx][adjy] = true;
        }
        else
        {
            std::string result = find(kindOfPeople, adjx, adjy, startX, startY, goalX, goalY, visited);
            if(!result.empty())
            {
                return result;
            }
        }
    }

    return toReturn;
}

std::string find_path(int startX, int startY, int goalX, int goalY)
{
    if(matrix[startX][startY] != matrix[goalX][goalY])
        return "neither";

    if((startX == goalX) && (startY == goalY))
        return peopleMap.at(matrix[startX][startY]);
    
    char kindOfPeople = matrix[startX][startY]; 
    
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    auto s = makeString(startX, startY, goalX, goalY);
    
    if(auto search = memo.find(s); search != memo.end())
    {
        if(search->second == kindOfPeople)
        return peopleMap[search->second];
    } 

    std::string result = find(kindOfPeople, startX, startY, startX, startY, goalX, goalY, visited);

    return result.empty() ? "neither" : result;
}

int main()
{
    std::cin >> rows >> cols;

    for(int i = 0; i < rows; i++)
    {
        std::vector<char> vec{};
        for (int j = 0; j < cols; j++)
        {
            std::cin >> temp;
            vec.push_back(temp);
        } 
        matrix.push_back(vec);
    }     

    std::cin >> cases;

    std::string string_out{};

    for(int i = 0; i < cases; i++)
    {
        int x1, y1, x2, y2;

        std::cin >> x1 >> y1 >> x2 >> y2;

        string_out.append(find_path(x1 - 1, y1 - 1, x2 - 1 , y2 - 1) + "\n");
    }

    if(cases > 0)
    {
        std::cout << string_out << std::endl;
    }
}