/*
 * StreamingAlgorithm.cpp
 *
 *  Created on: 6 Feb 2021
 *      Author: Grant
 */

#include <bitset>
#include <string>
#include <sstream>
#include <climits>
#include <iostream>
#include <math.h>

using namespace std;

int size = 10;
int n = 10;
int array_size[10];
int stream[10][10];

void integertobinary(int n, int position)
{
	int i;
	for(i=0; n>0; i++)
	{
		stream[position][i]=n%2;
		n= n/2;
	}

	array_size[position] = i;
}

int least_significant_bit(int position)
{
	int least_position;

	for (int a = 0; a < array_size[position]; a++)
	{
		if (stream[position][a] == 1)
		{
			least_position = a;
			break;
		}
	}

	return least_position;
}

int main()
{
	int original_stream[10] = {1, 5, 6, 8, 11, 21, 25, 31, 35, 38};
	int bitmap[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (int p = 0; p < 10; p++)
	{
	integertobinary(original_stream[p], p);

	for (int a = 0; a < array_size[p]; a++)
	{
		cout << stream[p][a] << endl;
	}

	int lsb = least_significant_bit(p);

	cout << "Least Significant Bit " << lsb << endl;

	bitmap[lsb] = 1;

	cout << endl;
	}

	int R;
	for (int b = 0; b < 10; b++)
	{
		if (bitmap[b] == 0)
		{
			R = b;
			break;
		}
	}

	cout << "R " << R << endl;

	float cardinality = (pow(2, R)) / 0.77351;

	cout << "Cardinality is " << cardinality << endl;
	return 0;
}

