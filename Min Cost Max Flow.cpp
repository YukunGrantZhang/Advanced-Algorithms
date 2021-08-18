/*
 * Min Cost Max Flow.cpp
 *
 *  Created on: 3 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAX_HEAP_SIZE 50

int heap[MAX_HEAP_SIZE];
int last_heap_element;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define N 6

int dist[N];

class Node {
public:
	int origin, dest, weight, explored, distance;
	Node* next;
};

class Graph {
public:
	Node* head[N];
	int nV;
};

class Edge {
public:
	int src, dest, weight;
};

class MinHeapNode
{
public:
    int vertex;
    int weight;
};

class MinHeap
{
public:
    //int size;
    //int *keys;
    MinHeapNode *nodes[MAX_HEAP_SIZE];
};

MinHeapNode* newMinHeapNode(int v, int w)
{
    MinHeapNode* minHeapNode = new MinHeapNode();
    minHeapNode->vertex = v;
    minHeapNode->weight = w;
    return minHeapNode;
}

MinHeap* createMinHeap()
{
    MinHeap* minHeap = new MinHeap();
    //minHeap->nodes = malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void BubbleUp(MinHeap* heaps, int current_index)
{
	int parent_index = (int)(floor((current_index + 1) / 2)) - 1;
	MinHeapNode* temp;

	if (parent_index < 0)
	{
		parent_index = 0;
	}

	while (heaps->nodes[current_index]->weight < heaps->nodes[parent_index]->weight)
	{
		temp = heaps->nodes[current_index];
		heaps->nodes[current_index] = heaps->nodes[parent_index];
		heaps->nodes[parent_index] = temp;

		current_index = parent_index;
		parent_index = (int)(floor((current_index + 1) / 2)) - 1;

		if (parent_index < 0)
		{
			break;
		}
	}

}

void BubbleDown(MinHeap* heaps, int starting_index)
{
	int current_index = starting_index;
	int left_child_index = (current_index + 1) * 2 - 1;
	int right_child_index = (current_index + 1) * 2;

	int selection_index;

	if (heaps->nodes[left_child_index] == NULL || heaps->nodes[right_child_index] == NULL)
	{
		if (heaps->nodes[left_child_index] != NULL && heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight)
		{
			MinHeapNode* temp = heaps->nodes[current_index];
			heaps->nodes[current_index] = heaps->nodes[left_child_index];
			heaps->nodes[left_child_index] = temp;
		}

		return;
	}

	while (heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight || heaps->nodes[current_index]->weight > heaps->nodes[right_child_index]->weight)
	{
		if (heaps->nodes[left_child_index]->weight < heaps->nodes[right_child_index]->weight)
		{
			selection_index = left_child_index;
		}
		else
		{
			selection_index = right_child_index;
		}

		MinHeapNode* temp2 = heaps->nodes[current_index];
		heaps->nodes[current_index] = heaps->nodes[selection_index];
		heaps->nodes[selection_index] = temp2;

		current_index = selection_index;
		left_child_index = (current_index + 1) * 2 - 1;
		right_child_index = (current_index + 1) * 2;

		if (heaps->nodes[left_child_index] == NULL || heaps->nodes[right_child_index] == NULL)
		{
			if (heaps->nodes[left_child_index] != NULL && heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight)
			{
				MinHeapNode* temp3 = heaps->nodes[current_index];
				heaps->nodes[current_index] = heaps->nodes[left_child_index];
				heaps->nodes[left_child_index] = temp3;
			}

			break;
		}
	}
}

void InsertHeap(MinHeap* heaps, MinHeapNode* temp_node)
{
	heaps->nodes[last_heap_element] = temp_node;
	int current_element_index = last_heap_element;
	last_heap_element++;

	BubbleUp(heaps, current_element_index);
}

int ExtractMin(MinHeap* heaps)
{
	int last_index = last_heap_element - 1;
	int min = heaps->nodes[0]->vertex;

	heaps->nodes[0] = heaps->nodes[last_index];
	heaps->nodes[last_index] = NULL;
	last_heap_element--;

	BubbleDown(heaps, 0);

	return min;
}

void DeleteKey(MinHeap* heaps, int vertex)
{
	int location = 50;

	for (int i = 0; i < last_heap_element; i++)
	{
		if (heaps->nodes[i]->vertex == vertex)
		{
			location = i;
		}
	}

	if (location == 50)
	{
		return;
	}

	int last_index = last_heap_element - 1;

	heaps->nodes[location] = heaps->nodes[last_index];
	heaps->nodes[last_index] = NULL;
	last_heap_element--;

	BubbleDown(heaps, location);
}

void ReduceKey(MinHeap* heaps, int vertex, int new_reduction_weight)
{
	int location = 50;

	for (int i = 0; i < last_heap_element; i++)
	{
		if (heaps->nodes[i]->vertex == vertex)
		{
			location = i;
		}
	}

	if (location == 50)
	{
		return;
	}

	heaps->nodes[location]->weight = new_reduction_weight;

	BubbleUp(heaps, location);
}

Graph* createGraph(int edges[][4], int n)
{
	unsigned i;

	struct Graph* graph = new Graph();

	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	for (i = 0; i < n; i++)
	{
		int src = edges[i][0];
		int dest = edges[i][1];
		int weight = edges[i][2];

		Node* newNode = new Node();
		newNode->origin = src;
		newNode->dest = dest;
		newNode->weight = weight;

		newNode->next = graph->head[src];

		graph->head[src] = newNode;

		if (i == n - 1)
		{
			graph->head[src]->next = graph->head[dest];

			Node* newNode = new Node();

			newNode->origin = dest;

			newNode->dest = 100;

			newNode->next = NULL;

			graph->head[dest] = newNode;
		}
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
			printf("%d -> %d (%d)\t", ptr->origin, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

int edges[8][4] = {{ 0, 1, 1, 1 }, { 0, 2, 2, 1 }, { 1, 3, 1, 2 }, { 2, 3, 2, 2 }, { 2, 4, 2, 2 }, { 3, 4, 3, 1 }, { 3, 5, 1, 1 }, { 4, 5, 3, 1 }};


int max_path = 10;
int path[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int count = 1;

void BinaryHeapDijkstra(Graph* graph, int starting_vertex, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph->head[i]->explored = 0;
	}

	graph->head[starting_vertex]->explored = 1;

	for (int i = 0; i < n; i++)
	{
		graph->head[i]->distance = 0;
	}

	MinHeap* heaps = createMinHeap();

	last_heap_element = 0;

	for (int i = 0; i < 50; i++)
	{
		heaps->nodes[i] = NULL;
	}

	for (int i = 0; i < 9; i++)
	{
		MinHeapNode* new_node = newMinHeapNode(i, 100);
		InsertHeap(heaps, new_node);
	}

	for (int i = 0; i < n; i++)
	{
		dist[i] = 100;
	}

	int vertices_processed = 0;

	while(vertices_processed < n - 1)
	{
		for (int i = 0; i < n; i++)
		{
			if (graph->head[i]->explored == 1)
			{
				Node* temp = graph->head[i];

				//cout << i;

				if (temp->dest > n - 1)
				{
					break;
				}

				//cout << i;

				int final_destination = 100;

				while (temp != NULL)
				{
					//cout << temp->dest;

					if (graph->head[temp->dest]->explored == 1)
					{
						temp = temp->next;
						continue;
					}

					//cout << i;

					if (temp->distance + temp->weight < dist[temp->dest])
					{
						bool in_origin = false;
						for (int i = 0; i < max_path; i++)
						{
							if (path[i] == temp->origin)
							{
								in_origin = true;
							}
						}

						if (in_origin == true)
						{
							cout << temp->dest;
							if (final_destination == 100)
							{
								final_destination = temp->dest;
							}
							else
							{
								int origin = temp->origin;
								int current_destination = final_destination;
								int new_destination = temp->dest;
								int current_distance = 100;
								int new_distance = 100;

								for (int y = 0; y < 8; y++)
								{
									if (edges[y][0] == origin && edges[y][1] == current_destination)
									{
										current_distance = edges[y][2];
									}

									if (edges[y][0] == current_destination && edges[y][1] == origin)
									{
										current_distance = edges[y][2];
									}

									if (edges[y][0] == origin && edges[y][1] == new_destination)
									{
										new_distance = edges[y][2];
									}

									if (edges[y][0] == new_destination && edges[y][1] == origin)
									{
										new_distance = edges[y][2];
									}
								}

								if (new_distance < current_distance)
								{
									final_destination = temp->dest;
								}

							}
						}

						if (temp->dest == 5)
						{
							final_destination = temp->dest;
						}

						//cout << temp->origin;
						//final_destination = temp->dest;
						dist[temp->dest] = temp->distance + temp->weight;
						ReduceKey(heaps, temp->dest, dist[temp->dest]);

						Node* new_temp = graph->head[temp->dest];
						while (new_temp != NULL)
						{
							new_temp->distance = dist[temp->dest];
							//cout << new_temp->dest;
							new_temp = new_temp->next;
						}
					}

					temp = temp->next;
				}

				if (final_destination == 100)
				{
					continue;
				}

				bool exist = false;
				for (int i = 0; i < max_path; i++)
				{
					if (path[i] == final_destination)
					{
						exist = true;
					}
				}

				if (exist == false)
				{
					path[count] = final_destination;
					count++;
				}

				//cout << final_destination;

				cout << endl;
				cout << endl;
			}
		}

		int extracted_vertex = ExtractMin(heaps);
		graph->head[extracted_vertex]->explored = 1;
		vertices_processed++;
		//cout << endl;
		//cout << endl;
	}
}

//int edges[8][4] = {{ 0, 1, 1, 1 }, { 0, 2, 2, 1 }, { 1, 3, 1, 2 }, { 2, 3, 2, 2 }, { 2, 4, 2, 2 }, { 3, 4, 3, 1 }, { 3, 5, 1, 1 }, { 4, 5, 3, 1 }};

int total_flow = 0;

void maxflow(Graph* graph, int nv, int n)
{
	max_path = 10;
	for (int u = 0; u < 10; u++)
	{
		path[u] = 0;
	}
	count = 1;

	BinaryHeapDijkstra(graph, 0, graph->nV);

	for (int i = 0; i < graph->nV; i++)
	{
		printf("%d ", graph->head[i]->distance);
	}
	/*
	if (graph->head[graph->nV - 1]->distance == 0)
	{
		cout << "No more valid paths!";
		return;
	}
	*/

	cout << endl;

	cout << "Shortest path is ";

	for (int j = 0; j < count; j++)
	{
		cout << path[j];
	}
	/*
	if (path[count - 1] != 5)
	{
		cout << "No more valid paths!";
		return;
	}
	*/

	cout << endl;

	int capacity = 1;
	bool capacity_reached = false;
	int number1 = 100;
	int number2 = 100;
	int prev = 2;

	while (capacity_reached == false)
	{
	for (int k = 0; k < count; k++)
	{
		if (prev == 2)
		{
			number1 = path[k];
			prev = 1;
		}
		else
		{
			number2 = path[k];
			prev = 2;
		}

		if (number1 != 100 && number2 != 100)
		{
			for(int l = 0 ; l < n; l++)
			{
				if (edges[l][0] == number1 && edges[l][1] == number2)
				{
					if (edges[l][3] == capacity)
					{
						edges[l][2] = 100;
						capacity_reached = true;
					}
				}

				if (edges[l][0] == number2 && edges[l][1] == number1)
				{
					if (edges[l][3] == capacity)
					{
						edges[l][2] = 100;
						capacity_reached = true;
					}
				}
			}
		}

	}
	if (capacity_reached == true)
	{
		total_flow = total_flow + capacity;
	}

	capacity++;
	}

	//cout << "Total flow is " << total_flow << endl;

}

int main(void)
{

	int n = 8;

	//int edges[n][4] = {{ 0, 1, 1, 1 }, { 0, 2, 2, 1 }, { 1, 3, 1, 2 }, { 2, 3, 2, 2 }, { 2, 4, 2, 2 }, { 3, 4, 3, 1 }, { 3, 5, 1, 1 }, { 4, 5, 3, 1 }};

	Graph *graph = createGraph(edges, n);
	graph->nV = 6;
	printGraph(graph);
	maxflow(graph, graph->nV, n);

	graph = NULL;
	graph = createGraph(edges, n);
	graph->nV = 6;
	printGraph(graph);
	maxflow(graph, graph->nV, n);

	cout << "Total flow is " << total_flow << endl;

	/*
	BinaryHeapDijkstra(graph, 0, graph->nV);

	for (int i = 0; i < graph->nV; i++)
	{
		printf("%d ", graph->head[i]->distance);
	}

	cout << endl;

	cout << "Shortest path is ";

	for (int j = 0; j < count; j++)
	{
		cout << path[j];
	}

	cout << endl;

	int capacity = 1;
	bool capacity_reached = false;
	int number1 = 100;
	int number2 = 100;
	int prev = 2;

	while (capacity_reached == false)
	{
	for (int k = 0; k < count; k++)
	{
		if (prev == 2)
		{
			number1 = path[k];
			prev = 1;
		}
		else
		{
			number2 = path[k];
			prev = 2;
		}

		if (number1 != 100 && number2 != 100)
		{
			for(int l = 0 ; l < n; l++)
			{
				if (edges[l][0] == number1 && edges[l][1] == number2)
				{
				if (edges[l][3] == capacity)
				{
					edges[l][2] = 100;
					capacity_reached = true;
				}
				}

				if (edges[l][0] == number2 && edges[l][1] == number1)
				{
				if (edges[l][3] == capacity)
				{
					edges[l][2] = 100;
					capacity_reached = true;
				}
				}
			}
		}

	}
	if (capacity_reached == true)
	{
		total_flow = total_flow + capacity;
	}

	capacity++;
	}

	cout << "Total flow is " << total_flow << endl;
	*/

	return 0;
}


