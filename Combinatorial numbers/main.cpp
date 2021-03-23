#include "CombinatoricNum.h"
#include <string>
#include <vector>

using namespace std;

struct command
{
	string com;
	vector<uint32_t> nums;
};

int ctoi(char c)
{
	switch (c)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			break;
	}
}

uint32_t stoui(string str)
{
	uint32_t rank = 1;
	uint32_t num = 0;
	
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (i > 10 || rank == 1000000000 && (str[i] > 52 || (str[i] == 52 && num > 294967295)))
		{
			throw string("ERROR: not correct arguments");
		}
		num += rank * ctoi(str[i]);
		rank *= 10;
	}

	return num;
}

command spliteStr(string str)
{
	command cmd;
	string chars("UAPCSB"), nums("0123456789");

	if (chars.find(str[0]) == -1 || str[1] != '(' || str[str.size() - 1] != ')')
	{
		throw string("ERROR: not correct command");
	}

	cmd.com = str[0];

	int index = 2, countComma = 0;
	string num;
	while (str[index] != ')')
	{
		if (nums.find(str[index]) == -1)
		{
			if (str[index] == ',' && countComma == 0)
			{
				if (num == "")
				{
					throw string("ERROR: not correct arguments");
				}
				cmd.nums.push_back(stoui(num));
				num = "";
				countComma++;
				index++;
			}
			else
			{
				throw string("ERROR: not correct arguments");
			}
		}
		else
		{
			num += str[index];
			index++;
		}
	}

	if (index != str.size() - 1 || num == "")
	{
		throw string("ERROR: not correct arguments");
	}

	cmd.nums.push_back(stoui(num));

	return cmd;
}

int main()
{	
	command cmd;
	string str;
	cout << "Enter H to bring up help" << endl;
	while (true)
	{
		try
		{
			if (!getline(cin, str))
			{
				break;
			}

			if (!str.compare("Q"))
			{
				break;
			}

			if (!str.compare("H"))
			{
				cout << "All arguments must be entered like this (m,n)" << endl;
				cout << "Q - Exit" << endl;
				cout << "U(m,n) - number of placements" << endl;
				cout << "A(m,n) - number of placements without repetitions" << endl;
				cout << "P(n) - number of permutations" << endl;
				cout << "C(m,n) - number of combinations" << endl;
				cout << "S(m,n) - Stirling number of the second kind" << endl;
				cout << "B(n) - Bell's number" << endl;
				continue;
			}

			cmd = spliteStr(str);

			if (!cmd.com.compare("U"))
			{
				if (cmd.nums.size() == 1)
				{
					cout << "ERROR: too few arguments" << endl;
					continue;
				}
				cout << placement(cmd.nums[0], cmd.nums[1]) << endl;
				continue;
			}

			if (!cmd.com.compare("A"))
			{
				if (cmd.nums.size() == 1)
				{
					cout << "ERROR: too few arguments" << endl;
					continue;
				}
				cout << placementWthoutRep(cmd.nums[0], cmd.nums[1]) << endl;
				continue;
			}


			if (!cmd.com.compare("P"))
			{
				if (cmd.nums.size() == 2)
				{
					cout << "ERROR: too many arguments" << endl;
					continue;
				}
				cout << permutations(cmd.nums[0]) << endl;
				continue;
			}

			if (!cmd.com.compare("C"))
			{
				if (cmd.nums.size() == 1)
				{
					cout << "ERROR: too few arguments" << endl;
					continue;
				}
				cout << combinations(cmd.nums[0], cmd.nums[1]) << endl;
				continue;
			}

			if (!cmd.com.compare("S"))
			{
				if (cmd.nums.size() == 1)
				{
					cout << "ERROR: too few arguments" << endl;
					continue;
				}
				cout << stirling(cmd.nums[0], cmd.nums[1]) << endl;
				continue;
			}

			if (!cmd.com.compare("B"))
			{
				if (cmd.nums.size() == 2)
				{
					cout << "ERROR: too many arguments" << endl;
					continue;
				}
				cout << bell(cmd.nums[0]) << endl;
				continue;
			}
		}
		catch (const string a)
		{
			cout << a << endl;
		}
	}
	return 0;
}