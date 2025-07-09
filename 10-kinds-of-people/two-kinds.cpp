#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

/*
    https://open.kattis.com/problems/10kindsofpeople
*/
struct Cell
{
    int section;
    char value;
    Cell(int section, char value) : section(section), value(value) {}

    bool operator==(const Cell& c) const
    {
        return (section == c.section) && (value == c.value);
    }
};
int rows, cols, cases;
char temp;
std::vector<std::vector<char>> matrix{};
std::queue<std::pair<int,int>> queue{};
int count;
std::vector<std::vector<Cell>> sections;

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

void find_section(int x, int y, char kindOfPeople, int section, std::vector<std::vector<bool>>& visited, std::vector<std::vector<Cell>>& sections)
{
    visited[x][y] = true;
    sections[x][y] = Cell(section, kindOfPeople);

    for(int i = 0; i < 4; i++)
    {
        int adjx = x + rowDir[i];
        int adjy = y + colDir[i];

        if(!isValid(visited, adjx, adjy))
        {    
            continue;
        }
        else if(matrix[adjx][adjy] != kindOfPeople)
        {
            queue.push(std::make_pair(adjx, adjy));
        }
        else
        {
            find_section(adjx, adjy, kindOfPeople, section, visited, sections);
        }
    }
}

void flood(int rows, int cols)
{   
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    sections = std::vector(rows, std::vector<Cell>(cols, Cell(-1, 'x')));

    queue.push(std::make_pair(0, 0));
    int section = 0;

    while(!queue.empty())
    {
        auto coord = queue.front();
        int x = coord.first;
        int y= coord.second;

        char kindOfPeople = matrix[x][y];
        if(!visited[x][y])
        {
            find_section(x, y, kindOfPeople, section++, visited, sections);
        }
        queue.pop();
    }
}

int main()
{
    std::cin >> rows >> cols;
    count = rows * cols;

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

    flood(rows, cols);

    std::cin >> cases;

    std::string string_out{};

    for(int i = 0; i < cases; i++)
    {
        int x1, y1, x2, y2;

        std::cin >> x1 >> y1 >> x2 >> y2;

        if(sections[x1-1][y1-1] == sections[x2-1][y2-1])
        {
            string_out.append(peopleMap[sections[x1-1][y1-1].value] + "\n");
        }
        else
        {
            string_out.append("neither\n");
        }
    }

    if(cases > 0)
    {
        std::cout << string_out << std::endl;
    }
}