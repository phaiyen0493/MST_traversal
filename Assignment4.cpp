/*Name: Yen Pham
CS3110
Assignment 4
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 

using namespace std;

int min_key(int key[], bool mst_set[], int vertex_count)  
{  
	// Initialize min value  
	int min = INT_MAX, min_index;  
  
	for (int v = 0; v < vertex_count; v++)
	{ 
		if (mst_set[v] == false && key[v] < min)
		{
			min = key[v];
			min_index = v;
		}
	}
  
	return min_index;  
}  


void prim_MST_algorithm(int graph[50][50], int vertex_count)
{
	//array to store parent of each vertex in MST
	int parent[vertex_count];
	
	//array to store key values used to pic minimum weight edge
	int key[vertex_count];

	//array to mark set of vertices included in MST
	bool mst_set[vertex_count];

	//initialize all keys as INF and mstSET false for all vertex in start
	for(int i = 0; i< vertex_count; i++)
	{
		key[i] = INT_MAX;
		mst_set[i] = false;
	}

	//initialize weight key of 0th vertex as 0 and parent as -1
	key[0] = 0;
	parent[0] = -1; //because it is root of MST

	int min_index = 0; 
 
	for (int count = 0; count < vertex_count - 1; count++) 
	{  
		// Pick the minimum key vertex from the set of vertices not yet included in MST  
		min_index = min_key(key, mst_set, vertex_count);

		// Add the picked vertex to the MST Set  
		mst_set[min_index] = true;  
  
		// Update key value and parent index of the adjacent vertices of the picked vertex.  
		// Consider only those vertices which are not yet included in MST  
		for (int v = 0; v < vertex_count; v++)
		{
			// Update the key only if graph[u][v] is smaller than key[v]  
			if (graph[min_index][v] && mst_set[v] == false && graph[min_index][v] < key[v])
			{
				parent[v] = min_index, key[v] = graph[min_index][v];
			}  
		}
	}

	// calculate the minimum cost of spanning tree  
	ofstream fout("output4.txt"); //output file
	int cost = 0;
	for (int i = 1; i < vertex_count; i++)
	{
		cost += graph[i][parent[i]];
	}

	//Print results
	fout << "The minimum spanning tree has total cost " << cost << " and whose edges are ";

	for (int i = 1; i < vertex_count; i++)
	{
        	fout<< "(" << parent[i] + 1 << "," << i+1 << ")";
		if (i == vertex_count - 1)
		{
			fout << endl;
		}
		else
		{
			fout << ", ";
		}
	}
	fout.close();
}

int main()
{
	ifstream fin("data4.txt"); //input file
	if (fin.fail())
	{
		cout << "cannot open file data4.txt\n";
		exit(0);
	}

	string line;
	int row,column;
	int point;

	//define max size for graph as 50
	int graph[50][50];

	//Read line
	row = 0;
	while(getline(fin, line) && line.length() != 0)
	{
		column = 0;
		stringstream is(line);
		while(is >> point)
		{
			graph[row][column] = point;
			column++;
		}
		row++;
	}

	int vertex_count = column;
	
	//call MST function to print minimum spanning tree
	prim_MST_algorithm(graph, vertex_count);
	fin.close();
	return 0;
}