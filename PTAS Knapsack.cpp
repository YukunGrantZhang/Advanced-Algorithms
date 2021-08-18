/*
 * PTAS Knapsack.cpp
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
	srand(5);

	int n = 10;

	int x[n];
	float v[n] = {1.0, 5.0, 3.0, 1.0, 2.0, 8.0, 9.0, 8.0, 3.0, 1.0};
	float w[n] = {1.0, 9.0, 1.0, 5.0, 2.0, 6.0, 3.0, 6.0, 1.0, 2.0};
	float wb[n] = {1.0, 9.0, 1.0, 5.0, 2.0, 6.0, 3.0, 6.0, 1.0, 2.0};
	int W = 15;

	float epsilon = 0.1;
	int number_of_elements = int(1 / epsilon);

	int guess[number_of_elements];
	int random_guess;
	for (int p = 0; p < number_of_elements; p++)
	{
		guess[p] = 0;
	}

	int most_valuable = 0;
	for (int q = 0; q < number_of_elements; q++)
	{
		random_guess = rand() % 10;

		while (guess[random_guess] == 1)
		{
			random_guess = rand() % 10;
		}

		guess[random_guess] = 1;

		if (v[random_guess] > most_valuable)
		{
			most_valuable = v[random_guess];
		}
	}

	for (int e = 0; e < n; e++)
	{
		if (v[e] > most_valuable)
		{
			v[e] = 0;
		}
	}

	float w_sum = 0;

	for (int i = 0; i < n; i++)
	{
		x[i] = 0;
	}

	while (w_sum <= W)
	{
		float highest_value = 0.0;
		int chosen_value = 0;

		for (int a = 0; a < n; a++)
		{
			if (x[a] == 1)
			{
				continue;
			}
			else
			{
				if (v[a] / w[a] > highest_value)
				{
					highest_value = v[a] / w[a];
					chosen_value = a;
				}
			}
		}

		if (highest_value == 0.0)
		{
			break;
		}

		int largest_value = 0;
		int chosen_value_1 = 0;

		for (int b = 0; b < n; b++)
		{
			if (x[b] == 1)
			{
				continue;
			}
			else
			{
				if (v[b] > largest_value)
				{
					largest_value = v[b];
					chosen_value_1 = b;
				}
			}
		}

		w_sum = 0;

		for (int b = 0; b < n; b++)
		{
			if (x[b] == 1)
			{
				w_sum = w_sum + w[b];
			}
		}

		if ((v[chosen_value_1] > v[chosen_value]) && (w_sum + w[chosen_value_1] < W))
		{
			chosen_value = chosen_value_1;
		}

		w_sum = 0;

		for (int c = 0; c < n; c++)
		{
			if (x[c] == 1)
			{
				w_sum = w_sum + w[c];
			}
		}

		if (w[chosen_value] < 1)
		{
			w[chosen_value] = wb[chosen_value];
		}

		//cout << chosen_value << endl;
		//cout << w_sum << endl;
		//cout << w[chosen_value] << endl;
		//cout << w_sum + w[chosen_value] << endl;
		//cout << endl;

		if (w_sum + w[chosen_value] > W)
		{
			v[chosen_value] = 0;
		}
		else
		{
			x[chosen_value] = 1;
		}

		/*
		x[chosen_value] = 1;

		w_sum = 0;

		for (int c = 0; c < n; c++)
		{
			if (x[c] == 1)
			{
				w_sum = w_sum + w[c];
			}
		}

		if (w_sum > W)
		{
			x[chosen_value] = 0;
			break;
		}
		*/
	}

	for (int r = 0; r < n; r++)
	{
		cout << "The value of x" << r << " is " << x[r] << endl;
	}

	return 0;
}


