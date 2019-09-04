// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

//Structures in the application

// A structure to represent a node in adjacency list 
struct AdjListNode 
{ 
	int dest; 
	int weight; 
	struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 
struct AdjList 
{ 
	struct AdjListNode *head; // pointer to head node of list 
}; 

// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
struct Graph 
{ 
	int V; 
	struct AdjList* array; 
}; 

//Functions

// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest, int weight) 
{ 
	struct AdjListNode* newNode = 
			(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = V; 

	// Create an array of adjacency lists. Size of array will be V 
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < V; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest, int weight) 
{ 
	// Add an edge from src to dest. A new node is added to the adjacency 
	// list of src. The node is added at the beginning 
	struct AdjListNode* newNode = newAdjListNode(dest, weight); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 
} 

// Structure to represent a min heap node 
struct MinHeapNode 
{ 
	int v; 
	int dist; 
}; 

// Structure to represent a min heap 
struct MinHeap 
{ 
	int size;	 // Number of heap nodes present currently 
	int capacity; // Capacity of min heap 
	int *pos;	 // This is needed for decreaseKey() 
	struct MinHeapNode **array; 
}; 

// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(int v, int dist) 
{ 
	struct MinHeapNode* minHeapNode = 
		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode; 
} 

// A utility function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity) 
{ 
	struct MinHeap* minHeap = 
		(struct MinHeap*) malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = 
		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && 
		minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	smallest = left; 

	if (right < minHeap->size && 
		minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	smallest = right; 

	if (smallest != idx) 
	{ 
		// The nodes to be swapped in min heap 
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *idxNode = minHeap->array[idx]; 

		// Swap positions 
		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		// Swap nodes 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check if the given minHeap is ampty or not 
int isEmpty(struct MinHeap* minHeap) 
{ 
	return minHeap->size == 0; 
} 

// Standard function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	if (isEmpty(minHeap)) 
		return NULL; 

	// Store the root node 
	struct MinHeapNode* root = minHeap->array[0]; 

	// Replace root node with last node 
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	// Update position of last node 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	// Reduce heap size and heapify root 
	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 

// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, int v, int dist) 
{ 
	// Get the index of v in heap array 
	int i = minHeap->pos[v]; 

	// Get the node and update its dist value 
	minHeap->array[i]->dist = dist; 

	// Travel up while the complete tree is not heapified. 
	// This is a O(Logn) loop 
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		// Swap this node with its parent 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		// move to parent index 
		i = (i - 1) / 2; 
	} 
} 

// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(struct MinHeap *minHeap, int v) 
{ 
if (minHeap->pos[v] < minHeap->size) 
	return true; 
return false; 
} 

// The main function that calulates distances of shortest paths from src to all 
// vertices. It is a O(ELogV) function 
int* dijkstra(struct Graph* graph, int src) 
{ 
	int V = graph->V;// Get the number of vertices in graph 
	
	// dist values used to pick minimum weight edge in cut . 
	// Declared as static because the value is returned 
	static int dist[9];	 


	// minHeap represents set E 
	struct MinHeap* minHeap = createMinHeap(V); 

	// Initialize min heap with all vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v) 
	{ 
		dist[v] = __INT_MAX__/2; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	// Make dist value of src vertex as 0 so that it is extracted first 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
	decreaseKey(minHeap, src, dist[src]); 

	// Initially size of min heap is equal to V 
	minHeap->size = V; 

	// In the followin loop, min heap contains all nodes 
	// whose shortest distance is not yet finalized. 
	while (!isEmpty(minHeap)) 
	{ 
		// Extract the vertex with minimum distance value 
		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		int u = minHeapNode->v; // Store the extracted vertex number 

		// Traverse through all adjacent vertices of u (the extracted 
		// vertex) and update their distance values 
		struct AdjListNode* pCrawl = graph->array[u].head; 
		while (pCrawl != NULL) 
		{ 
			int v = pCrawl->dest; 

			// If shortest distance to v is not finalized yet, and distance to v 
			// through u is less than its previously calculated distance 
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
										pCrawl->weight + dist[u] < dist[v]) 
			{ 
				dist[v] = dist[u] + pCrawl->weight; 

				// update distance value in min heap also 
				decreaseKey(minHeap, v, dist[v]); 
			} 
			pCrawl = pCrawl->next; 
		}
		
	} 

	// print the calculated shortest distances 
	printArr(dist, V);

   //to find the distance from one point to another point
   int smallest=__INT_MAX__/2;
   int dest =0;
   for(int count=0;count <V;count++)
   {
      if(dist[count]!=0 && dist[count]<smallest)
      {
         smallest = dist[count];
		 dest= count;
      }
   }
 return dist; 
} 

//Loop to find the smallest loop
void findloop( int *arr, int V)
{
    int smallest = __INT_MAX__;
    int i,j, dis[V][V];

	//Create the distance matrix
	for (i = 0; i < V; i++) 
    {
		for (j = 0; j < V; j++) 
    	{
			dis[i][j]=*((arr+i*V) + j);
		}
	
	}
	for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
           if(dis[i][j]==0)
           {
               dis[i][j] = __INT_MAX__/2;
           }
            if ((dis[i][j]+dis[j][i])< smallest)
            {
                smallest   =   dis[i][j]+dis[j][i];
			}
        }        
    }
    printf("%d\n",smallest);
}

// Driver program for the algorithm
int main() 
{ 
   // create the graph given in above fugure 
	int V = 9; 
	struct Graph* graph = createGraph(V); 

	int n,m;
    scanf("%d %d", &n, &m);

	int u[m] , v[m] ;
    long int h[m], t[m] ;

    int i;
    for( i = 0; i < m; i +=1 ){
        scanf("%d%d%ld%ld",&u[i],&v[i], &t[i], &h[i]);
    }
	
    // making graph adding edges
	for (int j=0; j<m;j++){
	    addEdge(graph,u[j]-1, v[j]-1, h[j]-t[j]); 
    }

   int *ptr;
   int dis[V][V];
   for(int i=0;i<V;i++)
   {
	   //To get the distances from the source node
	   ptr = dijkstra(graph, i);
	   for(int j=0;j<V;j++)
	   {	
		   //Saving the Value to an array
		   dis[i][j]= *(ptr+j);
	   } 
   }
    findloop((int *)dis,V);	
    return 0; 
} 
