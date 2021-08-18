/*
 * Linear Programming Simplex.cpp
 *
 *  Created on: 27 Jan 2021
 *      Author: Grant
 */

#include <iostream>

using namespace std;

float** calculate_simplex(float simplex_tableau[3][7], int rows, int columns)
{
	float** tableau = 0;
	tableau = new float*[rows];

	for (int h = 0; h < rows; h++)
	{
		tableau[h] = new float[columns];

		for (int w = 0; w < columns; w++)
	    {
			tableau[h][w] = simplex_tableau[h][w];
	    }
	}

	bool optimal = false;

	while (optimal == false)
	{
		int bottom_row = rows - 1;

		int pivot_column = 0;
		int value = tableau[bottom_row][0];
		for (int i=0; i < columns; i++)
		{
			if (tableau[bottom_row][i] < value)
			{
				pivot_column = i;
				value = tableau[bottom_row][i];
			}
		}

		if (value >= 0)
		{
			optimal = true;
			continue;
		}

		int indicator = 0;
		float indicator_value;
		if (tableau[0][columns - 1] / tableau[0][pivot_column] > 0)
		{
			indicator_value = tableau[0][columns - 1] / tableau[0][pivot_column];
		}
		else
		{
			indicator_value = 100;
		}

		for (int j = 0; j < rows - 1; j++)
		{
			if (tableau[j][columns - 1] / tableau[j][pivot_column] < indicator_value)
			{
				if (tableau[j][columns - 1] / tableau[j][pivot_column] > 0)
				{
					indicator = j;
					indicator_value = tableau[j][columns - 1] / tableau[j][pivot_column];
				}
			}
		}

		float pivot_variable = tableau[indicator][pivot_column];

		for (int a = 0; a < columns; a++)
		{
			tableau[indicator][a] = tableau[indicator][a] / pivot_variable;
		}

		for (int e = 0; e < rows; e++)
		{
			if (e == indicator)
			{
				continue;
			}
			else
			{
				for (int g = 0; g < columns; g++)
				{
					if (g == pivot_column)
					{
						continue;
					}
					else
					{
						float negative_pivot_column_value = -tableau[e][pivot_column];
						float pivot_row_value = tableau[indicator][g];
						float old_value = tableau[e][g];

						float new_value = negative_pivot_column_value * pivot_row_value + old_value;
						tableau[e][g] = new_value;
					}
				}
			}
		}

		for (int b = 0; b < rows; b++)
		{
			if (b == indicator)
			{
				continue;
			}
			else
			{
				tableau[b][pivot_column] = 0;
			}
		}
	}

	return tableau;
}

int main()
{
	float simplex_tableau[3][7] = {{1, 3, 2, 1, 0, 0, 10}, {1, 5, 1, 0, 1, 0, 8},
				                   {-8, -10, -7, 0, 0, 1, 0}};

	int rows = 3;
	int columns = 7;

	float** result = calculate_simplex(simplex_tableau, rows, columns);

	for (int u = 0; u < rows; u++)
	{
		for (int v = 0; v < columns; v++)
		{
			cout << result[u][v] << " ";
		}
		cout << endl;
	}

	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < columns; b++)
		{
			if (result[a][b] == 1)
			{
				bool basic = true;
				int basic_column = b;
				for (int c = 0; c < rows; c++)
				{
					if (c == a)
					{
						continue;
					}
					else
					{
						if (result[c][b] != 0)
						{
							basic = false;
						}
					}
				}

				if (basic == true)
				{
					cout << "Basic Column for row " << a + 1 << " is column " << basic_column + 1 << endl;
				}
			}
		}
	}

	return 0;
}


