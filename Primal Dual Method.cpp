/*
 * Primal Dual Method.cpp
 *
 *  Created on: 21 Jan 2021
 *      Author: Grant
 */

#include <iostream>
using namespace std;

float B = 18;

int main()
{
	int x = 0;
	int k = 10;
	int z[k];
	float y[k];

	for (int i = 0; i < k; i++)
	{
		z[i] = 0;
		y[i] = 0.0;
	}

	for (int j = 0; j < k; j++)
	{
		if (x + z[j] >= 1)
		{
			//cout << "HERE";
			continue;
		}
		else
		{
			for (float a = 0; a < 100; a++)
			{
				float b = float(a / 100);
				float y_tight_constraint = 0.1;
				float b_tight_constraint = 0.5;

				//cout << b << endl;

				y[j] = b;
				if ((1 - y[j]) <= y_tight_constraint)
				{
					z[j] = 1;
					break;
					//y[j] = b;
				}

				float sum = 0;
				for (int c = 0; c < k; c++)
				{
					sum = sum + y[c];
				}

				if ((B - sum) <= b_tight_constraint)
				{
					x = 1;
					break;
				}

			}
		}
	}

	cout << "The state of x is " << x << endl;
	for (int e = 0; e < k; e++)
	{
		cout << "The state of z" << e + 1 << " is " << z[e] <<endl;
	}

	return 0;
}


