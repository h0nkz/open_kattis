#include <iostream>

struct position
{
	char x;
	char y;

	int getSum()
	{
		return x + y;
	}

	 bool operator==(position& rhs)
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	 bool operator!=(position& rhs)
	 {
		 return !(*this == rhs);
	 }
};

bool sameColor(position from, position to)
{
	return((from.getSum() % 2) == (to.getSum() % 2));
}

bool validate(position pos)
{
	return((pos.x >= 'A') && (pos.x <= 'H') && (pos.y >= '1') && (pos.y <= '8'));
}

bool sameDiagonal(position from, position to)
{
	return (from.getSum() == to.getSum()) || ((from.x + to.y) == (to.x + from.y));
}


position findNextMove(position from, position to)
{
	position pos;
	for (int i = -8; i <= 8; i++)
	{
		for (int j = -8; j <= 8; j++)
		{
			pos.x = from.x + i;
			pos.y = from.y + j;
			if (validate(pos) && sameDiagonal(pos, to) && sameDiagonal(from, pos))
			{
				return pos;
			}
		}
	}
}


int main()
{
	int cases;

	std::cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		position from, to;
		std::cin >> from.x;
		std::cin >> from.y;
		std::cin >> to.x;
		std::cin >> to.y;

		if (!sameColor(from, to))
		{
			std::cout << "Impossible" << std::endl;
		}
		else if (from == to)
		{
			std::cout << "0 " << from.x << " " << from.y << std::endl;
		}
		else if (sameDiagonal(from, to))
		{
			std::cout << "1 " << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
		}
		else 
		{
			std::cout << "2 ";
			std::cout << from.x << " " << from.y << " ";
			position nextMove = findNextMove(from, to);
			std::cout << nextMove.x << " " << nextMove.y << " ";
			std::cout << to.x << " " << to.y << std::endl;
		}

	}
}