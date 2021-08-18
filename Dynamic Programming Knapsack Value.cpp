/*
 * Dynamic Programming Knapsack Value.cpp
 *
 *  Created on: 24 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int n = 10;

int count = 0;

int W = 15;

int x[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

float sum = 0;

int max_value = 21;

int packing(int v[], int w[], int i, int p)
{
	if (i == 0)
	{
		if (v[i] == p)
		{
			return w[0];
		}
		else
		{
			return 100;
		}
	}

	int value1 = 0;
	int value2 = 0;

	value1 = packing(v, w, i - 1, p);

	if (p - v[i] >= 0)
	{
		value2 = w[i] + packing(v, w, i - 1, p - v[i]);
	}
	else
	{
		return value1;
	}

	if (value1 >= value2)
	{
		return value2;
	}
	else
	{
		return value1;
	}
}

int main()
{
	srand(5);

	int v[n] = {1, 5, 3, 1, 2, 8, 9, 8, 3, 1};
	int w[n] = {1, 9, 1, 5, 2, 6, 3, 6, 1, 2};

	int b = 0;

	for (int y = 0; y < n; y++)
	{
		b = b + w[y];
	}

	int min_weight = packing(v, w, 9, 21);

	cout << "Min Weight achievable is: " << min_weight << endl;

	return 0;
}


