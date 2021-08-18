/*
 * Ford Fulkerson Algorithm.cpp
 *
 *  Created on: 31 Jan 2021
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

void DFS(Graph* graph, int vertex)
{
	//graph->head[vertex]->explored = 1;

	//printf("%d ", vertex);

	Node* temp = graph->head[vertex];

	int destination = 100;
	int current_value = temp->value;

	//printf("HERE");

	while (temp != NULL)
	{
		//printf("HERE");
		if (temp->dest == 5)
		{
			//printf("HERE");
			total_flow = total_flow + lowest_value;
			return;
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



