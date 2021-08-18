/*
 * Scaling Max Flow Algorithm.cpp
 *
 *  Created on: 1 Feb 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#define N 50

class Node {
public:
	int dest;
	int explored = 0;
	int selected = 0;
	int current = 0;
	int value;
	Node* next;
};

class Graph {
public:
	Node* head[N];
	int nV;
};

int lowest_value = 100;
int total_flow = 0;

//int n = 8;

Graph* createGraph(int edges[][3], int n)
{
	unsigned i;

	Graph* graph = new Graph();

	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	for (i = 0; i < n; i++)
	{
		int src = edges[i][0];
		int dest = edges[i][1];

		Node* newNode = new Node();
		newNode->dest = dest;
		newNode->value = edges[i][2];

		newNode->next = graph->head[src];

		graph->head[src] = newNode;

		//newNode = (struct Node*)malloc(sizeof(struct Node));
		//newNode->dest = src;

		//newNode->next = graph->head[dest];

		//graph->head[dest] = newNode;

	}
	return graph;
}

void printGraph(Graph* graph)
{
	int i;
	for (i = 0; i < N; i++)
	{
		Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("(%d -> %d, %d)\t", i, ptr->dest, ptr->value);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

void update_capacities(Graph* graph)
{
	int i;

	int flow_increase = 0;
	bool found_bottleneck = false;

	while (found_bottleneck == false)
	{
	for (i = 0; i < N; i++)
	{
		Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			if (ptr->selected == 1)
			{
				//cout << "HERE";
				ptr->current = ptr->current + 1;
			}

			if (ptr->current == ptr->value)
			{
				//cout << "HERE";
				found_bottleneck = true;
				if (ptr->value > 0)
				{
					flow_increase = ptr->value;
				}
				//cout << flow_increase << endl;
			}

			ptr = ptr->next;
		}
	}
	if (found_bottleneck == true)
	{
		break;
	}
	}

	total_flow = total_flow + flow_increase;

	for (i = 0; i < N; i++)
	{
		Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			ptr->selected = 0;
			ptr = ptr->next;
		}
	}
}

void DFS(Graph* graph, int vertex)
{
	printf("%d ", vertex);

	if (vertex == 5)
	{
		update_capacities(graph);
		return;
	}

	Node* temp = graph->head[vertex];

	int destination = 100;
	int current_value = temp->value;

	while (temp != NULL)
	{
		//printf("HERE");
		if (temp->dest == 5)
		{
			current_value = temp->value;

			destination = temp->dest;

			break;
		}

		if (graph->head[temp->dest]->explored == 0)
		{
			if (destination == 100)
			{
				current_value = temp->value;

				destination = temp->dest;
			}
			else
			{
				if (temp->value > current_value)
				{
					current_value = temp->value;

					destination = temp->dest;
				}

			}
			//DepthFirstSearch(graph, temp->dest);
		}

		//temp->explored = 1;
		temp = temp->next;
	}

	if (destination != 100)
	{
		if (current_value < lowest_value)
		{
			lowest_value = current_value;
		}

		Node* t = graph->head[vertex];

		while (t != NULL)
		{
			if (t->dest == destination)
			{
				t->explored = 1;
				t->selected = 1;
				break;
			}

			t = t->next;
		}

		DFS(graph, destination);
	}
}

int main(void)
{
	srand ( time(NULL) );

	int n = 8;

	int edges[n][3] = {{ 0, 1, 1 }, { 0, 2, 1 }, { 1, 3, 2 }, { 2, 3, 2 }, { 2, 4, 2 }, { 3, 4, 1 }, { 3, 5, 1 }, { 4, 5, 1 }};

	int end_node = 5;

	Graph *graph = createGraph(edges, n);

	Node* newNode = new Node();
	newNode->dest = 100;
	newNode->value = 0;
	newNode->next = NULL;
	graph->head[end_node] = newNode;

	graph->nV = 6;

	printGraph(graph);

	//DFS(graph, 0);


	bool path_exhausted = false;

	while (path_exhausted == false)
	{
		lowest_value = 100;
		DFS(graph, 0);

		if (lowest_value == 100)
		{
			path_exhausted = true;
		}
	}

	cout << endl;


	cout << "The final maximum flow is " << total_flow << endl;

	return 0;
}


