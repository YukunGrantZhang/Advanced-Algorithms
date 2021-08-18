/*
 * Online Set Cover.cpp
 *
 *  Created on: 22 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int main()
{
	srand(5);

	int m = 10;
	int n = 50;
	int c = 2;

	float x[m];

	float set[m];

	for (int i = 0; i < m; i++)
	{
		x[i] = (float) 1 / m;
	}

	for (int u = 0; u < m; u++)
	{
		set[u] = 0;
	}

	int r = c * log(n);

	float alpha[m][r];

	for (int a = 0; a < m; a++)
	{
		for (int b = 0; b < r; b++)
		{
			alpha[a][b] = (float)(rand() % 100) / 100;
		}
	}

	int y = 0;

	for (int c = 0; c < m; c++)
	{
		float change = 0;

		float sum = 0;

		bool exit = false;
		while (exit == false)
		{
			change = x[c];

			x[c] = x[c] + change;

			for (int p = 0; p < r; p++)
			{
				if (x[c] >= alpha[c][p])
				{
					set[y] = x[c];
					y++;
					exit = true;
					break;
				}
			}
		}

		for (int v1 = 0; v1 < m; v1++)
		{
			sum = sum + set[v1];
		}

		if (sum >= 1)
		{
			break;
		}
	}

	for (int j = 0; j < m; j++)
	{
		cout << "Values of x" << j + 1 << " is " << x[j] << endl;
	}

	for (int e = 0; e < m; e++)
	{
		cout << "Values of set value " << e + 1 << " is " << set[e] << endl;
	}

	return 0;
}


