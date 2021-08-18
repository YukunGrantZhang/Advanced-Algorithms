/*
 * Online Algorithms List Update.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <unistd.h>
using namespace std;

class Generator {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;
public:
    Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max)
	{}

    double operator ()() {
        while (true) {
            int number = int(this->distribution(generator));
            if (number >= int(this->min) && int(number <= this->max))
                return number;
        }
    }
};

class Node
{
public:
	int data;
	int frequency = 0;
	Node* left = NULL;
	Node* right = NULL;
};

class List
{
public:
	Node* starting_node = NULL;
};

void insert(List* list, int value)
{
	Node* node = list->starting_node;

	if (list->starting_node == NULL)
	{
		list->starting_node = new Node();
		list->starting_node->data = value;
		return;
	}

	while (node->right != NULL)
	{
		//cout << "HERE";
		node = node->right;
	}

	Node* current_node = new Node();
	current_node->data = value;

	node->right = current_node;
	current_node->left = node;
}

void Delete(List* list, Node* node)
{
	if (node->left == NULL)
	{
		list->starting_node = node->right;
		node->right->left = NULL;
		node = NULL;
	}

	if (node->right != NULL)
	{
		node->left->right = node->right;
		node->right->left = node->left;
		node = NULL;
	}
	else
	{
		node->left->right = NULL;
		node = NULL;
	}
}

int cost = 0;

void MFaccess(List* list, int value)
{
	Node* node = list->starting_node;

	while(node != NULL)
	{
		//cout << node->data;
		if (node->data == value)
		{
			Node* current_node = new Node();
			current_node->data = value;

			list->starting_node->left = current_node;
			current_node->right = list->starting_node;
			list->starting_node = current_node;

			Delete(list, node);

			return;
		}
		node = node->right;
		cost = cost + 1;
	}

	return;
}

void Transposeaccess(List* list, int value)
{
	Node* node = list->starting_node;

	while(node != NULL)
	{
		//cout << node->data;
		if (node->data == value)
		{
			if (node->left != NULL)
			{
				int temp = node->left->data;
				node->left->data = node->data;
				node->data = temp;
			}

			return;
		}
		node = node->right;
		cost = cost + 1;
	}

	return;
}

void Frequencyaccess(List* list, int value)
{
	Node* node = list->starting_node;

	while(node != NULL)
	{
		//cout << node->data;
		if (node->data == value)
		{
			node->frequency = node->frequency + 1;

			Node* current_node = node;

			while (node->left != NULL)
			{
				if (node->left->frequency >= current_node->frequency)
				{
					break;
				}

				node = node->left;
			}

			int temp = node->data;
			node->data = current_node->data;
			current_node->data = temp;

			return;
		}
		node = node->right;
		cost = cost + 1;
	}

	return;
}

void printlist(List* list)
{
	Node* node = list->starting_node;

	while(node != NULL)
	{
		cout << node->data << endl;

		node = node->right;
	}
}

int main()
{
	List* list = new List();
	int length = 100;
	int array[length];

	//Generator g(50.0, 10.0, 0, 100.0);
	for (int i = 0; i < length; i++)
	{
		array[i] = rand()%100;
		//std::cout << array[i] << std::endl;
	}

	for (int j = 0; j < length; j++)
	{
		insert(list, array[j]);
	}

	Generator h(50.0, 5.0, 40.0, 60.0);
	int sequence_length = 1000;
	int sequence[sequence_length];
	for (int a = 0; a < sequence_length; a++)
	{
		sequence[a] = h();
	}

	for (int b = 0; b < sequence_length; b++)
	{
		Frequencyaccess(list, sequence[b]);
	}

	printlist(list);

	cout << "Total Cost is " << cost << endl;

	return 0;
}


