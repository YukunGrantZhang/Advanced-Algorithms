/*
 * Exponential DIvide and Conquer.cpp
 *
 *  Created on: 4 Feb 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define N 6
#define NVERTICES 4

class Node {
public:
	int dest, weight;
	Node* next;
};

class Graph {
public:
	Node* head[N];
};

struct Graph* createGraph(int edges[][3], int n)
{
	unsigned i;

	Graph* graph = new Graph();

	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	for (i = 0; i < n; i++)
	{
		int src = edges[i][0];
		int dest = edges[i][1];
		int weight = edges[i][2];

		Node* newNode = new Node();
		newNode->dest = dest;
		newNode->weight = weight;

		newNode->next = graph->head[src];

		graph->head[src] = newNode;

		newNode = new Node();
		newNode->dest = src;
		newNode->weight = weight;

		newNode->next = graph->head[dest];

		graph->head[dest] = newNode;
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
			printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

int minimum = 100;
int total_minimum = 0;

int current_count = 0;
int actual_nodes_visited[100];

int accumulation_count = 0;
int accumulation_nodes_visited[100];

void bruteforcealgorithm(Graph* graph, int vertex, int sum, int count, int nodes_visited[], int destination, int last_index, int number_of_vertices)
{
	if (count == last_index)
	{
		cout << "CURRENT COUNT " << current_count << endl;

		nodes_visited[current_count] = destination;

		if (sum < minimum)
		{
			minimum = sum;

			for (int a = 0; a < current_count + 1; a++)
			{
				actual_nodes_visited[a] = nodes_visited[a];
				cout << nodes_visited[a] << endl;
			}
			cout << endl;
		}
		/*
		for (int a = 0; a < current_count + 1; a++)
		{
			cout << nodes_visited[a] << endl;
		}
		cout << endl;
		*/
		/*
		for (int a = 0; a < number_of_vertices; a++)
		{
			nodes_visited[a] = 100;
		}
		*/
		return;
	}

	//cout << "Vertex" << vertex << endl;
	//cout << "SUM " << sum << endl;

	Node* ptr = graph->head[vertex];
	//sum += ptr->weight;
	nodes_visited[count] = vertex;
	count += 1;

	int visited[number_of_vertices];

	for (int j = 0; j < number_of_vertices; j++)
	{
		visited[j] = nodes_visited[j];
	}

	//cout << "Vertex" << vertex << endl;
	//cout << "SUM " << sum << endl;
	//cout << "Destination " << ptr->dest << endl;
	//cout << "Weight " << ptr->weight << endl;
	//cout << endl;

	while (ptr != NULL)
	{
		int d = ptr->dest;
		int w = ptr->weight;

		if (count < last_index && d == destination && sum != 0)
		{
			//cout << "Vertex" << vertex << endl;
			//cout << "SUM " << sum << endl;
			//cout << "Destination " << ptr->dest << endl;
			//cout << "Weight " << ptr->weight << endl;
			//cout << endl;


			bool in = false;
			if (ptr->next != NULL)
			{
			int enter = 0;
			for (int a = 0; a < count; a++)
			{
				if (ptr->next->dest == visited[a])
				{
					in = true;
					break;
				}
			}
			}


			if (ptr->next != NULL && in == false)
			{
				//cout << "HERE" << ptr->dest << endl;
				ptr = ptr->next;
				//cout << "HERE" << ptr->dest << endl;
			}
			else
			{
				//cout << "Vertex" << vertex << endl;
				//cout << "SUM " << sum << endl;
				//cout << "Destination " << ptr->dest << endl;
				//cout << "Weight " << ptr->weight << endl;
				//cout << endl;



				sum += w;
				current_count = count;
				count = last_index;
				bruteforcealgorithm(graph, ptr->dest, sum, count, visited, destination, last_index, number_of_vertices);
				sum -= w;
				break;
			}
			continue;
		}

		int enter = 0;
		for (int a = 0; a < count; a++)
		{
			if (d == visited[a])
			{
				enter = 1;
				break;
			}
		}

		if (enter == 0)
		{
			sum += w;
			current_count = count;
			bruteforcealgorithm(graph, ptr->dest, sum, count, visited, destination, last_index, number_of_vertices);
			sum -= w;
		}

		ptr = ptr->next;
	}

}

void optimise(int n, int vertices, int starting_node, int ending_node, int edges[][3], int tracking[])
{
	Graph *graph = createGraph(edges, n);

	printGraph(graph);

	int e[vertices];
	int ecount = 0;

	if (current_count > 0)
	{
		for (int a = 0; a < vertices; a++)
		{
			for (int b = 0; b < current_count; b++)
			{
				if (tracking[a] == actual_nodes_visited[b])
				{
					bool present = false;
					for(int c = 0; c < ecount; c++)
					{
						e[c] = tracking[a];
						present = true;
					}

					if (present == false)
					{
						e[ecount] = tracking[a];
						ecount++;
					}
				}
			}
		}
	}

	if (accumulation_count > 0)
	{
		for (int a = 0; a < vertices; a++)
		{
			for (int b = 0; b < current_count; b++)
			{
				if (tracking[a] == accumulation_nodes_visited[b])
				{
					bool present = false;
					for(int c = 0; c < ecount; c++)
					{
						e[c] = tracking[a];
						present = true;
					}

					if (present == false)
					{
					e[ecount] = tracking[a];
					ecount++;
					}
				}
			}
		}
	}

	bruteforcealgorithm(graph, starting_node, 0, ecount, e, ending_node, vertices - 1, vertices);

	if (minimum != 100)
	{
		total_minimum = total_minimum + minimum;
	}
	//printf("%d", total_minimum);

	minimum = 100;
}

void exponential_divide_and_conquer(int n, int vertices, int starting_node, int ending_node, int edges[][3])
{
	int n1 = int(n / 2);
	int n2 = n - n1;

	int edges1[n1][3];
	for (int a = 0; a < n1; a++)
	{
		edges1[a][0] = edges[a][0];
		edges1[a][1] = edges[a][1];
		edges1[a][2] = edges[a][2];

		//cout << edges1[a][0] << endl;
		//cout << edges1[a][1] << endl;
	}

	//cout << endl;

	int edges2[n2][3];
	for (int b = 0; b < n2; b++)
	{
		edges2[b][0] = edges[b + n1][0];
		edges2[b][1] = edges[b + n1][1];
		edges2[b][2] = edges[b + n1][2];

		//cout << edges2[b][0] << endl;
		//cout << edges2[b][1] << endl;
	}

	int vertices1 = 0;
	int tracking1[vertices];
	int count1 = 0;
	for (int c = 0; c < n1; c++)
	{
		if (vertices1 == 0)
		{
			tracking1[vertices1] = edges1[c][0];
			vertices1++;
			tracking1[vertices1] = edges1[c][1];
			vertices1++;
		}
		else
		{
			int first_coordinate = edges1[c][0];
			int second_coordinate = edges1[c][1];

			bool first_in = false;
			bool second_in = false;
			for (int i = 0; i < vertices1; i++)
			{
				if (tracking1[i] == first_coordinate)
				{
					first_in = true;
				}

				if (tracking1[i] == second_coordinate)
				{
					second_in = true;
				}
			}

			if (first_in == false)
			{
				tracking1[vertices1] = first_coordinate;
				vertices1++;
			}

			if (second_in == false)
			{
				tracking1[vertices1] = second_coordinate;
				vertices1++;
			}
		}
	}

	/*
	cout << "N1 " << n1 << endl;
	cout << "VERTICES" << vertices1 << endl;
	for (int i = 0; i < vertices1; i++)
	{
		cout << tracking1[i];
	}
	cout << endl;
	*/

	int vertices2 = 0;
	int tracking2[vertices];
	int count2 = 0;
	for (int d = 0; d < n2; d++)
	{
		if (vertices2 == 0)
		{
			tracking2[vertices2] = edges2[d][0];
			vertices2++;
			tracking2[vertices2] = edges2[d][1];
			vertices2++;
		}
		else
		{
			int first_coordinate = edges2[d][0];
			int second_coordinate = edges2[d][1];

			bool first_in = false;
			bool second_in = false;
			for (int i = 0; i < vertices2; i++)
			{
				if (tracking2[i] == first_coordinate)
				{
					first_in = true;
				}

				if (tracking2[i] == second_coordinate)
				{
					second_in = true;
				}
			}

			if (first_in == false)
			{
				tracking2[vertices2] = first_coordinate;
				vertices2++;
			}

			if (second_in == false)
			{
				tracking2[vertices2] = second_coordinate;
				vertices2++;
			}
		}
	}

	/*
	cout << "N2 " << n2 << endl;
	cout << "VERTICES" << vertices2 << endl;
	for (int i = 0; i < vertices2; i++)
	{
		cout << tracking2[i];
	}
	cout << endl;
	*/

	int starting_vertex = starting_node;
	int ending_vertex = ending_node;
	int middle_vertex;

	bool found = false;

	for (int u = 0; u < vertices1; u++)
	{
		for (int v = 0; v < vertices2; v++)
		{
			if (tracking1[u] == tracking2[v])
			{
				if (tracking1[u] != starting_vertex && tracking2[v] != ending_vertex)
				{
					middle_vertex = tracking1[u];
					found = true;
					break;
				}
			}
		}
		if (found == true)
		{
			break;
		}
	}

	cout << "Middle Vertex" << middle_vertex << endl;

	if (n1 <= 3 || n2 <= 3)
	{
	optimise(n1, vertices1, starting_vertex, middle_vertex, edges1, tracking1);
	optimise(n2, vertices2, middle_vertex, ending_vertex, edges2, tracking2);

	current_count = 0;

	for (int x = 0; x < 100; x++)
	{
		actual_nodes_visited[x] = 100;
	}

	for (int r = 0; r < vertices1; r++)
	{
		accumulation_nodes_visited[accumulation_count] = tracking1[r];
		accumulation_count++;
	}

	for (int s = 0; s < vertices2; s++)
	{
		accumulation_nodes_visited[accumulation_count] = tracking2[s];
		accumulation_count++;
	}
	}
	else
	{
		exponential_divide_and_conquer(n1, vertices1, starting_vertex, middle_vertex, edges1);
		exponential_divide_and_conquer(n2, vertices2, middle_vertex, ending_vertex, edges2);
	}
}

int main(void)
{
	int n = 11;
	int vertices = 6;

	int starting_node = 0;
	int ending_node = 5;

	int edges[n][3] =
	{
		{ 0, 1, 2 }, { 0, 2, 1 }, { 0, 3, 4 },
		{ 1, 2, 3 }, { 1, 3, 5 }, { 1, 4, 3 },
		{ 2, 3, 6 }, { 2, 5, 5 },
		{ 3, 4, 1 }, { 3, 5, 2 },
		{ 4, 5, 1 }
	};

	for (int x = 0; x < 100; x++)
	{
		actual_nodes_visited[x] = 100;
	}

	exponential_divide_and_conquer(n, vertices, starting_node, ending_node, edges);

	//optimise(n, vertices, starting_node, ending_node, edges);

	/*
	Graph *graph = createGraph(edges, n);

	printGraph(graph);

	int e[vertices];

	bruteforcealgorithm(graph, starting_node, 0, 0, e, ending_node, vertices - 1, vertices);

	printf("%d", minimum);
	*/

	cout << "The minimum distance is " << total_minimum << endl;

	return 0;
}


