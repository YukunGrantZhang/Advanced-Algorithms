/*
 * FPTAS Knapsack.cpp
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

float packing(float v[], float w[], int i, float p)
{
	if (i == 0)
	{
		if (abs(v[i] - p) <= 0.1)
		{
			return w[0];
		}
		else
		{
			return 100;
		}
	}

	float value1 = 0;
	float value2 = 0;

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

	float v[n] = {1, 5, 3, 1, 2, 8, 9, 8, 3, 1};
	float w[n] = {1, 9, 1, 5, 2, 6, 3, 6, 1, 2};

	float epsilon = 0.1;
	float v_max = 9;

	int b = 0;

	for (int y = 0; y < n; y++)
	{
		v[y] = (n / epsilon) * (v[y] / v_max);
	}

	for (int a = 0; a < n; a++)
	{
		cout << v[a] << endl;
	}

	float input = (n / epsilon) * (21 / v_max);

	cout << "Input: " << input << endl;

	float min_weight = packing(v, w, 9, input);

	cout << "Min Weight achievable is: " << min_weight << endl;

	return 0;
}


