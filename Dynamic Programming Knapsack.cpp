/*
 * Dynamic Programming Knapsack.cpp
 *
 *  Created on: 23 Jan 2021
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

int packing(int v[], int w[], int i, int b)
{
	if (i == 0)
	{
		return 0;
	}

	int value1 = 0;
	int value2 = 0;

	value1 = packing(v, w, i - 1, b);

	if (b - w[i] >= 0)
	{
		value2 = v[i] + packing(v, w, i - 1, b - w[i]);
	}

	if (value1 >= value2)
	{
		//cout << "HERE" << value2 << endl;
		return value1;
	}
	else
	{
		//cout << value2 << endl;
		//x[i] = 1;
		//cout << v[i] << endl;
		return value2;
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

	int max_value = packing(v, w, 9, W);

	cout << "Max value achievable is: " << max_value << endl;

	return 0;
}


