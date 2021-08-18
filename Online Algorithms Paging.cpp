/*
 * Online Algorithms Paging.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
#include <random>
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

int p = 99;
int k = 5;

int hashing_function(int x)
{
	int sum = 0;
	int i;

	int a[p];
	for (i = 0; i < p; i++)
	{
		a[i] = i;
	}

	for (i = 0; i < k; i++)
	{
		sum = sum + int(a[i] * pow(x, i));
	}
	sum = sum % p;

	return sum;
}

int update(int hashing_array[], int value)
{
	int temp = hashing_function(value);

	if (hashing_array[temp] == 1000)
	{
		hashing_array[temp] = value;
	}
	else
	{
		int u = temp;

		while (hashing_array[u] != 1000)
		{
			u++;
		}

		hashing_array[u] = value;
	}
}

int cost = 0;

int Markingaccess(int hashing_array[][2], int size, int value)
{
	int temp = hashing_function(value);
	int u = temp;

	while(u < size)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = 1;
			return true;
		}

		u++;
	}

	while(u >= 0)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = 1;
			return true;
		}

		u--;
	}

	int least_frequent = 0;
	int random;
	bool set = false;

	while (set == false)
	{
		random = rand() % 100;
		int point = random;

		while(random >= 0)
		{
			if (hashing_array[random][1] == 0)
			{
				hashing_array[random][0] = value;
				hashing_array[random][1] = 1;
				set = true;
				break;
			}
			random--;
		}

		while(point < size)
		{
			if (hashing_array[point][1] == 0)
			{
				hashing_array[point][0] = value;
				hashing_array[point][1] = 1;
				set = true;
				break;
			}
			point++;
		}

		if (set == true)
		{
			break;
		}

		for(int u = 0; u < size; u++)
		{
			hashing_array[u][1] = 0;
		}

	}

	cost = cost + 1;

	return false;
}

int LRUaccess(int hashing_array[][2], int size, int value)
{
	int temp = hashing_function(value);
	int u = temp;

	while(u < size)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = 1;
			return true;
		}

		u++;
	}

	while(u >= 0)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = 1;
			return true;
		}

		u--;
	}

	int least_frequent = 0;
	int random;
	bool set = false;

	while (set == false)
	{
		random = rand() % 100;
		int point = random;

		while(random >= 0)
		{
			if (hashing_array[random][1] == 0)
			{
				hashing_array[random][0] = value;
				hashing_array[random][1] = 0;
				set = true;
				break;
			}
			random--;
		}

		while(point < size)
		{
			if (hashing_array[point][1] == 0)
			{
				hashing_array[point][0] = value;
				hashing_array[point][1] = 0;
				set = true;
				break;
			}
			point++;
		}

		if (set == true)
		{
			break;
		}

		for(int u = 0; u < size; u++)
		{
			hashing_array[u][1] = 0;
		}

	}

	cost = cost + 1;

	return false;
}

int LFUaccess(int hashing_array[][2], int size, int value)
{
	int temp = hashing_function(value);
	int u = temp;

	while(u < size)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = hashing_array[u][1] + 1;
			return true;
		}

		u++;
	}

	while(u >= 0)
	{
		if (hashing_array[u][0] == value)
		{
			hashing_array[u][1] = hashing_array[u][1] + 1;
			return true;
		}

		u--;
	}

	int least_frequent = 0;
	int random;
	bool set = false;

	while (set == false)
	{
		random = rand() % 100;
		int point = random;

		while(random >= 0)
		{
			if (hashing_array[random][1] == least_frequent)
			{
				hashing_array[random][0] = value;
				hashing_array[random][1] = 0;
				set = true;
				break;
			}
			random--;
		}

		while(point < size)
		{
			if (hashing_array[point][1] == least_frequent)
			{
				hashing_array[point][0] = value;
				hashing_array[point][1] = 0;
				set = true;
				break;
			}
			point++;
		}

		least_frequent++;
	}

	cost = cost + 1;

	return false;
}

int most_recent_item[1000];
int most_recent_item_count = 0;

int FIFOaccess(int hashing_array[][2], int size, int value)
{
	int temp = hashing_function(value);
	int u = temp;

	while(u < size)
	{
		if (hashing_array[u][0] == value)
		{
			most_recent_item[most_recent_item_count] = u;
			most_recent_item_count++;
			return true;
		}

		u++;
	}

	while(u >= 0)
	{
		if (hashing_array[u][0] == value)
		{
			most_recent_item[most_recent_item_count] = u;
			most_recent_item_count++;
			return true;
		}

		u--;
	}


	int removal = most_recent_item[most_recent_item_count - 1];
	if (most_recent_item_count - 1 >= 0 && most_recent_item_count - 1 < 1000)
	{
		int removal = most_recent_item[most_recent_item_count - 1];
		hashing_array[removal][0] = value;
		most_recent_item_count--;
	}
	else
	{
		int random = rand()%100;
		hashing_array[random][0] = value;
	}

	cost = cost + 1;

	return false;
}

int main()
{
   int sz = 100;
   int randArray[sz];
   for(int i=0;i<sz;i++)
   {
	   randArray[i] = rand() % 100;
   }

   for(int i=0;i<sz;i++)
   {
	   cout << "Elements no " << i+1 << "::" << randArray[i] << " ";
	   cout << "Hashing Address " << "::" << hashing_function(randArray[i]) << endl;
   }

   int hashing_array_size = 100;
   int hashing_array[hashing_array_size][2];

   for (int j = 0; j < hashing_array_size; j++)
   {
	   hashing_array[j][0] = 1000;
	   hashing_array[j][1] = 0;
   }

   for(int e=0;e<sz;e++)
   {
   	   int temp = hashing_function(randArray[e]);

   	   if (hashing_array[temp][0] == 1000)
   	   {
   		   hashing_array[temp][0] = randArray[e];
   	   }
   	   else
   	   {
   		   int u = temp;

   		   while (hashing_array[u][0] != 1000)
   		   {
   			   u++;

   			   if (u == hashing_array_size)
   			   {
   				   u = u - 1;
   				   break;
   			   }
   		   }

   		   if (hashing_array[u][0] != 1000)
   		   {
   			   while (hashing_array[u][0] != 1000)
   			   {
   				   u--;

   				   if (u == 0)
   				   {
   					   break;
   				   }
   			   }
   		   }

   		   hashing_array[u][0] = randArray[e];
   	   }
   }

   for (int k = 0; k < hashing_array_size; k++)
   {
   	   cout << hashing_array[k][0] << endl;;
   }
   cout << endl;

   //int update_value = 39;
   //update(hashing_array, update_value);

   Generator g(50.0, 10.0, 30.0, 70.0);
   int sequence_length = 200;
   int sequence[sequence_length];
   for (int a = 0; a < sequence_length; a++)
   {
	   sequence[a] = g();
   }

   for (int b = 0; b < sequence_length; b++)
   {
	   bool in_hash = Markingaccess(hashing_array, hashing_array_size, sequence[b]);
   }

   for (int m = 0; m < hashing_array_size; m++)
   {
	   cout << hashing_array[m][0] << endl;;
   }
   cout << endl;






   Generator h(120.0, 20.0, 90.0, 150.0);
   int sequence_length1 = 200;
   int sequence1[sequence_length1];
   for (int c = 0; c < sequence_length1; c++)
   {
	   sequence1[c] = h();
   }

   for (int d = 0; d < sequence_length1; d++)
   {
	   bool in_hash = Markingaccess(hashing_array, hashing_array_size, sequence1[d]);
   }

   for (int n = 0; n < hashing_array_size; n++)
   {
   	   cout << hashing_array[n][0] << endl;
   }
   cout << endl;

   cout << "Total cost is " << cost << endl;

   return 0;
}


