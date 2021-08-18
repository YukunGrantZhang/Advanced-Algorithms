/*
 * Multiplicative Weights.cpp
 *
 *  Created on: 30 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>

using namespace std;

int main()
{
	srand(5);

	int n = 10;

	int number_of_experts = 8;

	int experts[number_of_experts][n] = {{1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
										 {0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
										 {1, 1, 0, 0, 1, 1, 1, 1, 0, 0},
										 {0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
										 {1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
										 {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
										 {1, 1, 0, 1, 1, 0, 1, 0, 1, 0},
										 {1, 0, 1, 0, 0, 1, 0, 0, 0, 1}};

	float w[n + 1][number_of_experts];

	for (int a = 0; a < number_of_experts; a++)
	{
		w[0][a] = 1.0;
	}

	float p[n + 1][number_of_experts];

	for (int b = 0; b < number_of_experts; b++)
	{
		p[0][b] = w[0][b] / number_of_experts;
	}

	float epsilon = 0.1;

	int actual_events[n];

	for (int i = 0; i < n; i++)
	{
		actual_events[i] = rand() % 2;
	}

	cout << "Actual Events" << endl;
	for (int j = 0; j < n; j++)
	{
		cout << actual_events[j] << " ";
	}
	cout << endl;
	cout << endl;

	for (int k = 0; k < n; k++)
	{
		for (int l = 0; l < number_of_experts; l++)
		{
			if (experts[l][k] == actual_events[k])
			{
				w[k + 1][l] = w[k][l];
			}
			else
			{
				w[k + 1][l] = (1.0 - epsilon) * w[k][l];
			}
		}

		float summation = 0.0;
		for (int u = 0; u < number_of_experts; u++)
		{
			summation = summation + w[k + 1][u];
		}

		for (int v = 0; v < number_of_experts; v++)
		{
			p[k + 1][v] = w[k + 1][v] / summation;
		}
	}

	cout << "Daily Weights for Each Expert" << endl;
	for (int r = 0; r < n + 1; r++)
	{
		cout << "Day " << r << ": ";
		for (int s = 0; s < number_of_experts; s++)
		{
			cout << w[r][s] << " ";
		}
		cout << endl;
	}

	cout << endl;

	cout << "Daily Probability Distribution for Each Expert" << endl;
	for (int r1 = 0; r1 < n + 1; r1++)
	{
		cout << "Day " << r1 << ": ";
		for (int s1 = 0; s1 < number_of_experts; s1++)
		{
			cout << p[r1][s1] << " ";
		}
		cout << endl;
	}


	return 0;
}

