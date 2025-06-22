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

std::string find(const int kindOfPeople, int x, int y, const std::pair<int, int>& goal, std::vector<std::vector<bool>>& visited)
{
    if(!isValid(visited, x, y))
        return "";
    
    visited[x][y] = true;

    std::string toReturn = ""; 
    for(int i = 0; i < 4; i++)
    {
        int adjx = x + rowDir[i];
        int adjy = y + colDir[i];

        if(!isValid(visited, adjx, adjy))
        {    
            continue;
        }
        if((adjx == goal.first) && (adjy == goal.second))
        {
            return peopleMap.at(matrix[adjx][adjy]);
        }
        if(matrix[adjx][adjy] != kindOfPeople)
        {
            visited[adjx][adjy] = true;
        }
        else
        {
            std::string result = find(kindOfPeople, adjx, adjy, goal, visited);
            if(!result.empty())
            {
                return result;
            }
        }
    }

    return toReturn;
}

std::string find_path(std::pair<int, int> start, std::pair<int, int> goal)
{
    if(matrix[start.first][start.second] != matrix[goal.first][goal.second])
        return "neither";

    if((start.first == goal.first) && (start.second == goal.second))
        return peopleMap.at(matrix[start.first][start.second]);
    
    int kindOfPeople = matrix[start.first][start.second]; 
    
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    std::string result = find(kindOfPeople, start.first, start.second, goal, visited);

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

        std::cout << find_path(std::make_pair(x1 - 1, y1 - 1), std::make_pair(x2 - 1 , y2 - 1)) << std::endl;
    }
}