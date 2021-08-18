/*
 * Semidefinite Programming Maxcut.cpp
 *
 *  Created on: 24 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>

using namespace std;

int n = 5;


int main()
{
	srand(9);

	float x[5][5] = {{1, 1, 1, 1, 1},
			         {1, 1, 1, 0, 0},
			         {1, 1, 1, 0, 0},
			         {1, 0, 0, 1, 0},
			         {1, 0, 0, 0, 1}};

	float r[5];

	int v[5];

	for (int a = 0; a < 5; a++)
	{
		r[a] = float(rand() % 10) / 10;

		bool sign = rand() % 2;

		if (sign == false)
		{
			r[a] = -r[a];
		}
	}

	for (int b = 0; b < 5; b++)
	{
		cout << r[b] << endl;
	}

	for (int i = 0; i < n; i++)
	{
		float sum = 0;

		for (int j = 0; j < n; j++)
		{
			sum = sum + x[i][j] * r[j];
		}

		if (sum >= 0)
		{
			v[i] = 1;
		}
		else
		{
			v[i] = -1;
		}
	}

	for (int a = 0; a < n; a++)
	{
		cout << v[a] << endl;
	}

	return 0;
}


