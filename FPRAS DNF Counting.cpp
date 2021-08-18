/*
 * FPRAS DNF Counting.cpp
 *
 *  Created on: 24 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>

using namespace std;

int n1 = 5;
int n2 = 5;
int n3 = 5;

bool satisfying_clause(bool c[], int n)
{
	int size;

	if (n == 1)
	{
		size = n1;
	}
	else if (n == 2)
	{
		size = n2;
	}
	else
	{
		size = n3;
	}

	bool temp = c[0];
	for (int i = 1; i < size; i++)
	{
		temp = (temp && c[i]);
	}

	return temp;
}

bool DNF_equation(bool c1[], bool c2[], bool c3[])
{
	bool temp1 = c1[0];
	for (int i = 1; i < n1; i++)
	{
		temp1 = (temp1 && c1[i]);
	}

	bool temp2 = c2[0];
	for (int j = 1; j < n2; j++)
	{
		temp2 = (temp2 && c2[j]);
	}

	bool temp3 = c3[0];
	for (int k = 1; k < n3; k++)
	{
		temp3 = (temp3 && c3[k]);
	}

	return temp1 || temp2 || temp3;
}

float p_sum = 0;

int main()
{
	srand(5);

	bool c1[n1] = {true, false, true, false, true};
	bool c2[n2] = {false, false, false, false, true};
	bool c3[n3] = {true, true, true, true, true};

	//bool state = DNF_equation(c1, c2, c3);
	//bool state = satisfying_clause(c3, 3);

	//cout << state;

	int t1 = 10;
	int t2 = 100;

	for (int i = 0; i < t1; i++)
	{
		int chosen_clause = rand() % 3 + 1;

		int size;

		if (chosen_clause == 1)
		{
			size = n1;
		}
		else if (chosen_clause == 2)
		{
			size = n2;
		}
		else
		{
			size = n3;
		}

		for (int a = 0; a < t2; a++)
		{
		for (int j = 0; j < size; j++)
		{
			int state = rand() % 2;

			if (chosen_clause == 1)
			{
				if (state == 1)
				{
					c1[j] = true;
				}
				else
				{
					c1[j] = false;
				}
			}
			else if (chosen_clause == 2)
			{
				if (state == 1)
				{
					c2[j] = true;
				}
				else
				{
					c2[j] = false;
				}
			}
			else
			{
				if (state == 1)
				{
					c3[j] = true;
				}
				else
				{
					c3[j] = false;
				}
			}
		}

		bool result = false;

		if (chosen_clause == 1)
		{
			result = satisfying_clause(c1, 1);
		}
		else if (chosen_clause == 2)
		{
			result = satisfying_clause(c2, 2);
		}
		else
		{
			result = satisfying_clause(c3, 3);
		}

		if (result == true)
		{
			p_sum = p_sum + 1;
		}
		}
	}

	cout << "Number of Satisfying Assignments is " << p_sum << endl;

	float p_star = p_sum / (float(t1) * float(t2));

	float total = pow(2, n1) + pow(2, n2) + pow(2, n3);

	cout << p_star << endl;

	cout << total << endl;

	long satisfying_assignments = p_star * total;

	cout << "Number of satisfying assignments is " << satisfying_assignments << endl;

	return 0;
}


