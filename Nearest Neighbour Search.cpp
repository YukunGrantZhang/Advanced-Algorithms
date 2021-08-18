/*
 * Nearest Neighbour Search.cpp
 *
 *  Created on: 26 Jan 2021
 *      Author: Grant
 */

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
};

void hashfunction(int hashing_bits[], int k, Node** hashing_array, int hashing_array_size, int inputs[10][9], int sz)
{
	Node* node;
	for (int a = 0; a < hashing_array_size; a++)
	{
		hashing_array[a] = new Node();
		hashing_array[a]->data = 100;
		hashing_array[a]->next = new Node();

		node = hashing_array[a]->next;
		for (int r = 0; r < 20; r++)
		{
			node->data = 100;
			node->next = new Node();
			node = node->next;
		}
	}

	Node* input_node;
	for (int b = 0; b < sz; b++)
	{
		for (int i = 0; i < k; i++)
		{
		int temp = inputs[b][hashing_bits[i]];

		if (hashing_array[temp]->data == 100)
		{
			hashing_array[temp]->data = b;
			//cout << hashing_array[temp]->data << endl;
		}
		else
		{
			input_node = hashing_array[temp]->next;

			while (input_node->data != 100)
			{
				input_node = input_node->next;
			}

			input_node->data = b;
		}
		}
	}
}

int getPopularElement(int a[], int k)
{
  int count = 1, tempCount;
  int popular = a[0];
  int temp = 0;
  for (int i = 0; i < (k - 1); i++)
  {
    temp = a[i];
    tempCount = 0;
    for (int j = 1; j < k; j++)
    {
      if (temp == a[j])
        tempCount++;
    }
    if (tempCount > count)
    {
      popular = temp;
      count = tempCount;
    }
  }
  return popular;
}

int hashing_bits1[3] = {1, 5, 6};
Node* hashing_array1[100];

int hashing_bits2[3] = {2, 3, 8};
Node* hashing_array2[100];

int hashing_bits3[3] = {4, 7, 8};
Node* hashing_array3[100];

int query(int hashing_bits[], int k, Node** hashing_array, int hashing_array_size, int q[], int p[10][9])
{
	int points[k];
	for (int i = 0; i < k; i++)
	{
	int temp = q[hashing_bits[i]];
	int distance = 100;
	int best_point;

	Node* input_node = hashing_array[temp];

	while (input_node->data != 100)
	{
		if (abs(p[input_node->data][hashing_bits[i]] - q[hashing_bits[i]]) < distance)
		{
			best_point = input_node->data;
		}
		input_node = input_node->next;
	}

	points[i] = best_point;

	cout << best_point << endl;

	}

	int solution = getPopularElement(points, k);

	cout << solution << endl;

	return solution;
}

int main()
{
	int p[10][9] = {{1, 2, 5, 6, 8, 9, 11, 15, 3},
		            {3, 1, 9, 11, 2, 3, 1, 1, 8},
		            {5, 2, 3, 6, 11, 9, 15, 15, 9},
		            {8, 1, 5, 11, 8, 3, 1, 2, 1},
		            {1, 3, 5, 8, 11, 15, 12, 5, 3},
		            {9, 1, 3, 5, 9, 9, 15, 6, 1},
		            {4, 5, 5, 6, 11, 12, 1, 3, 3},
		            {5, 9, 18, 8, 11, 3, 2, 1, 7},
		            {1, 2, 1, 9, 12, 9, 3, 21, 5},
		            {0, 9, 8, 11, 15, 12, 1, 3, 1}};

	int q[9] = {2, 1, 9, 11, 15, 21, 1, 5, 8};

	int k = 3;
	int hashing_array_size = 100;

	//int hashing_bits1[3] = {1, 5, 6};
	//Node* hashing_array1[100];
	hashfunction(hashing_bits1, k, hashing_array1, hashing_array_size, p, 10);

	//int hashing_bits2[3] = {2, 3, 8};
	//Node* hashing_array2[100];
	hashfunction(hashing_bits2, k, hashing_array2, hashing_array_size, p, 10);

	//int hashing_bits3[3] = {4, 7, 9};
	//Node* hashing_array3[100];
	hashfunction(hashing_bits3, k, hashing_array3, hashing_array_size, p, 10);

	int answer[k];
	answer[0] = query(hashing_bits1, k, hashing_array1, hashing_array_size, q, p);
	answer[1] = query(hashing_bits2, k, hashing_array2, hashing_array_size, q, p);
	answer[2] = query(hashing_bits3, k, hashing_array3, hashing_array_size, q, p);

	int closest_point = getPopularElement(answer, k);

	cout << "The closest element is " << closest_point << endl;

	return 0;
}


