// C++ program to find the shortest path 
// with minimum edges in a graph 
#include <iostream> 
using namespace std; 
#define INFINITY 9999 
#define n 5 
#define s 0 
#define d 3 
#define NILL -1 
int MinDistance(int*, int*); 
void PrintPath(int*, int); 

// Function to find the shortest path 
// with minimum edges in a graph 
void Dijkstra(int Graph[n][n], int _n, int _s, int _d) 
{ 

	int i, u, v, count; 
	int dist[n]; 
	int Blackened[n] = { 0 }; 
	int pathlength[n] = { 0 }; 
	int parent[n]; 

	// The parent Of the source vertex is always equal to nill 
	parent[_s] = NILL; 

	// first, we initialize all distances to infinity. 
	for (i = 0; i < n; i++) 
		dist[i] = INFINITY; 

	dist[_s] = 0; 
	for (count = 0; count < n - 1; count++) { 
		u = MinDistance(dist, Blackened); 

		// if MinDistance() returns INFINITY, then the graph is not 
		// connected and we have traversed all of the vertices in the 
		// connected component of the source vertex, so it can reduce 
		// the time complexity sometimes 
		// In a directed graph, it means that the source vertex 
		// is not a root 
		if (u == INFINITY) 
			break; 
		else { 

			// Mark the vertex as Blackened 
			Blackened[u] = 1; 
			for (v = 0; v < n; v++) { 
				if (!Blackened[v] && Graph[u][v] 
					&& dist[u] + Graph[u][v] < dist[v]) { 
					parent[v] = u; 
					pathlength[v] = pathlength[parent[v]] + 1; 
					dist[v] = dist[u] + Graph[u][v]; 
				} 
				else if (!Blackened[v] && Graph[u][v] 
						&& dist[u] + Graph[u][v] == dist[v] 
						&& pathlength[u] + 1 < pathlength[v]) { 
					parent[v] = u; 
					pathlength[v] = pathlength[u] + 1; 
				} 
			} 
		} 
	} 

	// Printing the path 
	if (dist[_d] != INFINITY) 
		PrintPath(parent, _d); 
	else
		cout << "There is no path between vertex "
			<< _s << "to vertex " << _d; 
} 

int MinDistance(int* dist, int* Blackened) 
{ 
	int min = INFINITY, min_index, v; 
	for (v = 0; v < n; v++) 
		if (!Blackened[v] && dist[v] < min) { 
			min = dist[v]; 
			min_index = v; 
		} 
	return min == INFINITY ? INFINITY : min_index; 
} 

// Function to print the path 
void PrintPath(int* parent, int _d) 
{ 
	if (parent[_d] == NILL) { 
		cout << _d; 
		return; 
	} 
	PrintPath(parent, parent[_d]); 
	cout << "->" << _d; 
} 

// Driver code 
int main() 
{ 
	// INFINITY means that u and v are not neighbors. 
	int Graph[n][n] = { { 0, 1, INFINITY, INFINITY, 10 }, 
						{ 1, 0, 4, INFINITY, INFINITY }, 
						{ INFINITY, 4, 0, 7, INFINITY }, 
						{ INFINITY, INFINITY, 7, 0, 2 }, 
						{ 10, INFINITY, INFINITY, 2, 0 } }; 
	Dijkstra(Graph, n, s, d); 
	return 0; 
} 
