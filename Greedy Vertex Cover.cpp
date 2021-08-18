/*
 * Greedy Vertex Cover.cpp
 *
 *  Created on: 23 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int main()
{
	int n = 10;
	int m = 8;

	int e[m][2] = {{0, 1}, {2, 3}, {3, 4}, {3, 5}, {3, 6}, {5, 7}, {7, 8}, {8, 9}};
	int x[n];
	int y[m];

	for (int i = 0; i < n; i++)
	{
		x[i] = 0;
	}

	for (int j = 0; j < m; j++)
	{
		y[j] = 0;
	}

	int u;
	int v;
	for (int a = 0; a < m; a++)
	{
		u = e[a][0];
		v = e[a][1];

		if (x[u] + x[v] >= 1)
		{
			continue;
		}
		else
		{
			x[u] = 1;
			x[v] = 1;
			y[a] = 1;
		}
	}


	for (int r = 0; r < n; r++)
	{
		cout << "The value of x" << r << " is " << x[r] << endl;
	}

	for (int s = 0; s < m; s++)
	{
		cout << "The value of y" << s << " is " << y[s] << endl;
	}

	return 0;
}


