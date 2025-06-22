#include <iostream>
#include <vector>
#include <queue>
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

std::unordered_map<std::string, std::string> memo;

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

void savePath(int startX, int startY, int currX, int currY, char kindOfPeople)
{
    std::string key = startX + ' ' + startY + ' ' + currX + ' ' + currY + ""; // kindly tell string that you are a string
    memo.insert(key, peopleMap.at(kindOfPeople));
}

std::string find(const char kindOfPeople, int currX, int currY, int startX, int startY, int goalX, int goalY, std::vector<std::vector<bool>>& visited)
{
    if(!isValid(visited, currX, currY))
        return "";
    
    visited[currX][currY] = true;
    savePath(startX, startY, currX, currY, kindOfPeople);

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

    for(int i = 0; i < cases; i++)
    {
        int x1, y1, x2, y2;

        std::cin >> x1 >> y1 >> x2 >> y2;

        std::cout << find_path(x1 - 1, y1 - 1, x2 - 1 , y2 - 1) << std::endl;
    }
}