/*
 * Set Cover MW.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>

using namespace std;

int main()
{
	srand(5);

	int n = 10;

	int number_of_sets = 8;

	int set_covers[number_of_sets][n] = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
									     {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
										 {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
										 {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
										 {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
										 {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
										 {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
										 {1, 1, 1, 0, 0, 0, 0, 1, 1, 1}};

	float w[n + 1][number_of_sets];

	for (int a = 0; a < number_of_sets; a++)
	{
		w[0][a] = 1.0;
	}

	float p[n + 1][number_of_sets];

	for (int b = 0; b < number_of_sets; b++)
	{
		p[0][b] = w[0][b] / number_of_sets;
	}

	float epsilon = 0.1;

	int actual_elements[n];

	for (int i = 0; i < n; i++)
	{
		actual_elements[i] = rand() % 2;
	}

	cout << "Actual Elements" << endl;
	for (int j = 0; j < n; j++)
	{
		cout << actual_elements[j] << " ";
	}
	cout << endl;
	cout << endl;

	for (int k = 0; k < n; k++)
	{
		for (int l = 0; l < number_of_sets; l++)
		{
			if (actual_elements[k] == 1)
			{
				if (set_covers[l][k] == actual_elements[k])
				{
					w[k + 1][l] = w[k][l];
				}
				else
				{
					w[k + 1][l] = (1.0 - epsilon) * w[k][l];
				}
			}
			else
			{
				w[k + 1][l] = w[k][l];
			}
		}

		float summation = 0.0;
		for (int u = 0; u < number_of_sets; u++)
		{
			summation = summation + w[k + 1][u];
		}

		for (int v = 0; v < number_of_sets; v++)
		{
			p[k + 1][v] = w[k + 1][v] / summation;
		}
	}

	cout << "Element Weights for Each Set Cover" << endl;
	for (int r = 0; r < n + 1; r++)
	{
		cout << "Element " << r << ": ";
		for (int s = 0; s < number_of_sets; s++)
		{
			cout << w[r][s] << " ";
		}
		cout << endl;
	}

	cout << endl;

	cout << "Element Probability Distribution for Each Element" << endl;
	for (int r1 = 0; r1 < n + 1; r1++)
	{
		cout << "Element " << r1 << ": ";
		for (int s1 = 0; s1 < number_of_sets; s1++)
		{
			cout << p[r1][s1] << " ";
		}
		cout << endl;
	}

	return 0;
}


