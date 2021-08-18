/*
 * Schoning's Algorithm.cpp
 *
 *  Created on: 4 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>

using namespace std;

int m = 10;
int n = 3;

int check_satisfiability(int matrix[][3])
{
	bool satisfy = true;
	int clause;

	for (int x = 0; x < m; x++)
	{
		bool s = false;
		for (int y = 0; y < n; y++)
		{
			if (matrix[x][y] == 2)
			{
				s = true;
			}

			if (matrix[x][y] == -1)
			{
				s = true;
			}
		}

		if (s == false)
		{
			clause = x;
			satisfy = false;
		}
	}

	if (satisfy == true)
	{
		cout << "Assignment is satisfied" << endl;
		return 100;
	}
	else
	{
		cout << "Assignment is not satisfied" << endl;
		return clause;
	}
}

void schoningalgorithm(int matrix[][3])
{
	int clause = check_satisfiability(matrix);

	while (clause != 100)
	{
		int i = rand() % 3;

		//cout << clause << endl;
		//cout << i << endl;

		if (matrix[clause][i] == -2)
		{
			matrix[clause][i] = -1;
		}

		if (matrix[clause][i] == 2)
		{
			matrix[clause][i] = 1;
		}

		if (matrix[clause][i] == -1)
		{
			matrix[clause][i] = -2;
		}

		if (matrix[clause][i] == 1)
		{
			matrix[clause][i] = 2;
		}

		clause = check_satisfiability(matrix);
	}
}

int main()
{
	srand(1);

	int a[m][3];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int sign = rand() % 2;

			if (sign == 0)
			{
				a[i][j] = -(rand() % 2 + 1);
			}
			else
			{
				a[i][j] = rand() % 2 + 1;
			}
		}
	}

	for (int i1 = 0; i1 < m; i1++)
	{
		for (int j1 = 0; j1 < n; j1++)
		{
			cout << a[i1][j1];
		}
		cout << endl;
	}

	schoningalgorithm(a);

	for (int i2 = 0; i2 < m; i2++)
	{
		for (int j2 = 0; j2 < n; j2++)
		{
			cout << a[i2][j2];
		}
		cout << endl;
	}

	//cout << e << endl;

	return 0;
}


