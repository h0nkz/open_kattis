#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
	int num;
	string lectures;
	

	cin >> num;

	cin >> lectures;

	vector<bool> stayed_awake(num, false);
	int lectures_awake = 0;

	for (int i = 0; i < num; i++)
	{
		if (lectures[i] == '1')
		{
			stayed_awake.at(i) = true;
			for (int j = 1; j < 3; j++)
			{
				if (i + j < num)
				{
					stayed_awake.at(i+j) = true;
				}
			}
		}
	}

	for (int i = 0; i < num; i++)
	{
		if (stayed_awake.at(i))
		{
			lectures_awake++;
		}
	}


	cout << lectures_awake;


	return 0;
}