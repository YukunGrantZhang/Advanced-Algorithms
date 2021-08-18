/*
 * Greedy Set Cover.cpp
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

	int m = 5;
	int n = 50;
	int c = 2;

	float cs[m] = {5.0, 1.0, 3.0, 1.0, 3.0};

	float y[n];

	float ns[m] = {20.0, 10.0, 5.0, 30.0, 20.0};

	float x[m];

	for (int i = 0; i < m; i++)
	{
		x[m] = 0;
	}

	for (int j = 0; j < m; j++)
	{
		y[j] = 0;
	}

	int y_count = 0;

	bool summation = false;

	float lowest_cost = 1.0;

	while (summation == false)
	{
		lowest_cost = 1.0;
		int chosen_x = 0;
		for (int a = 0; a < m; a++)
		{
			if (x[a] == 1)
			{
				continue;
			}

			if ((cs[a] / ns[a]) < lowest_cost)
			{
				lowest_cost = cs[a] / ns[a];
				chosen_x = a;
			}
		}

		x[chosen_x] = 1;

		for (int b = 0; b < ns[chosen_x]; b++)
		{
			y[y_count] = cs[chosen_x] / ns[chosen_x];
			y_count++;

			if (y_count == n)
			{
				summation = true;
				break;
			}
		}
	}

	for (int r = 0; r < m; r++)
	{
		cout << "The value of x" << r + 1 << " is " << int(x[r]) << endl;
	}

	for (int s = 0; s < n; s++)
	{
		cout << "The value of y" << s + 1 << " is " << y[s] << endl;
	}

	return 0;
}



